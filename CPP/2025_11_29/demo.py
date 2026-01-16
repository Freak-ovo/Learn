import cvxpy as cp
import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import eigh


# ======================================================
# 【全局唯一函数定义】避免重复声明
# ======================================================
def steering_vector(N, d, fc, rho, theta):
    """
    计算近场球面波导向向量 a(ρ,θ) ∈ C^(N×1)
    参数：
        N: 天线数
        d: 天线间距 (m)
        fc: 载波频率 (Hz)
        rho: 目标/用户到基站的距离 (m)
        theta: 目标/用户相对于基站的角度 (rad)
    返回：
        近场导向向量（列向量）
    """
    a = np.zeros(N, dtype=np.complex128)
    for n in range(N):
        # 第n个天线的坐标：(0, (n - (N+1)/2)*d)（ULA沿y轴排列）
        antenna_y = (n - (N + 1) / 2) * d
        # 目标/用户的坐标：(ρ sinθ, ρ cosθ)
        target_x = rho * np.sin(theta)
        target_y = rho * np.cos(theta)
        # 天线到目标的实际距离（球面波路径）
        d_nk = np.sqrt((target_x - 0)**2 + (target_y - antenna_y)**2)
        # 导向向量相位：e^(-j2πfc(d_nk - ρ)/c)（补偿参考距离ρ的相位）
        phase = -2 * np.pi * fc * (d_nk - rho) / c
        a[n] = np.exp(1j * phase)
    return a.reshape(-1, 1)  # 转为列向量


def channel_matrix(N, d, fc, rho, theta):
    """计算近场信道矩阵 H = h*h^H（h为导向向量）"""
    h = steering_vector(N, d, fc, rho, theta)
    return h @ h.conj().T


# ======================================================
# 1. 系统参数配置（近场ISAC场景定义）
# ======================================================
# 天线阵列参数（超大阵列是近场场景的前提）
N = 64  # 天线数（ULA）
fc = 2.4e9  # 载波频率 (Hz)
d = 0.5 * 3e8 / fc  # 天线间距（λ/2，λ为波长）
c = 3e8  # 光速 (m/s)
lambda_ = c / fc  # 波长 (m)
D = (N - 1) * d  # 阵列孔径 (m)
dF = 2 * D**2 / lambda_  # Fraunhofer距离（近场/远场分界）
print(f"【场景基础】Fraunhofer距离: {dF:.1f} m（用户/目标均在该距离内，属于近场）")

# 功率与噪声参数
Pt_dBm = 30  # 总发射功率上限 (dBm)
Pt = 10 ** (Pt_dBm / 10) / 1000  # 转换为瓦特 (W)
sigma2_dBm = -95  # 噪声功率 (dBm)
sigma2 = 10 ** (sigma2_dBm / 10) / 1000  # 转换为瓦特 (W)

# 通信用户参数
K = 1  # 单用户场景
user_rho = 35  # 用户距离基站的距离 (m)
user_theta = np.pi / 4  # 用户角度（45°，弧度）
gamma_k = 10  # 用户目标SINR (dB)
gamma = 10 ** (gamma_k / 10)  # 转换为线性值

# 雷达目标与区域参数（同角度多目标）
T_rho = 50  # 距离采样点数
T_theta_new = 20  # 角度采样点数（体现球面波的角度维度）
rho_range = np.linspace(13, 62, T_rho)  # 距离范围 (m)
theta_range_new = np.linspace(-np.pi/6, np.pi/6, T_theta_new)  # 角度范围（-30°~30°，弧度）
tau0 = 1e-3  # 非感兴趣区域（SO）的波束增益阈值 (W)

# 感兴趣区域（SI）：两个目标周围3m范围
target_rhos = np.array([18.6, 39.6])  # 目标距离 (m)
target_thetas = np.array([np.pi/12, np.pi/12])  # 目标角度（15°，同角度）- 核心修改1
SI_radius = 3  # SI区域半径 (m)
SI_indices = []  # SI区域的距离索引
for idx, rho in enumerate(rho_range):
    if any(np.abs(rho - tr) <= SI_radius for tr in target_rhos):
        SI_indices.append(idx)
SO_indices = [idx for idx in range(T_rho) if idx not in SI_indices]  # 非感兴趣区域索引


# ======================================================
# 2. 预计算信道与导向向量
# ======================================================
# 计算用户信道矩阵（用于通信SINR约束）
hk = steering_vector(N, d, fc, user_rho, user_theta)
Hk = hk @ hk.conj().T

# 预计算所有（距离-角度）采样点的导向向量（用于后续波束增益计算）
a_list_2d = []
for rho in rho_range:
    for theta in theta_range_new:
        a = steering_vector(N, d, fc, rho, theta)
        a_list_2d.append(a)
a_list_2d = np.array(a_list_2d)  # 形状：(T_rho*T_theta_new, N, 1)


# ======================================================
# 3. SDR优化问题构建（半定松弛）
# ======================================================
# 优化变量定义
Wk = cp.Variable((N, N), symmetric=True, complex=True)  # 用户波束外积矩阵（K=1）
R = cp.Variable((N, N), symmetric=True, complex=True)   # 雷达协方差矩阵
tau = cp.Variable(nonneg=True)                          # SI区域的最小波束增益（优化目标）

# 优化目标：最大化SI区域的最小波束增益
objective = cp.Maximize(tau)

# 约束条件集合
constraints = []
# 约束1：SI区域的波束增益 ≥ τ - 核心修改2：将theta=0改为theta=np.pi/12
for idx in SI_indices:
    a = steering_vector(N, d, fc, rho_range[idx], np.pi/12)
    beam_gain = cp.real(cp.trace(a.conj().T @ (Wk + R) @ a))
    constraints.append(beam_gain >= tau)
# 约束2：SO区域的波束增益 ≤ τ0 - 核心修改3：将theta=0改为theta=np.pi/12
for idx in SO_indices:
    a = steering_vector(N, d, fc, rho_range[idx], np.pi/12)
    beam_gain = cp.real(cp.trace(a.conj().T @ (Wk + R) @ a))
    constraints.append(beam_gain <= tau0)
# 约束3：用户SINR ≥ 目标值γ
numerator = cp.real(cp.trace(Wk @ Hk))          # 信号功率：Tr(Wk Hk)
denominator_interf = cp.real(cp.trace(R @ Hk))  # 干扰功率：Tr(R Hk)
constraints.append(numerator >= gamma * (denominator_interf + sigma2))
# 约束4：总发射功率 ≤ 上限Pt
total_power = cp.real(cp.trace(Wk) + cp.trace(R))
constraints.append(total_power <= Pt)
# 约束5：矩阵半正定（SDR松弛的核心约束）
constraints.append(Wk >> 0)
constraints.append(R >> 0)


# ======================================================
# 4. 求解SDP问题 & 严格结果校验
# ======================================================
# 构建并求解问题（使用SCS求解器，支持复数半定规划）
problem = cp.Problem(objective, constraints)
problem.solve(solver=cp.SCS, verbose=False)

# 1. 校验求解状态
if problem.status not in [cp.OPTIMAL, cp.OPTIMAL_INACCURATE]:
    raise RuntimeError(f"SDP求解失败！状态: {problem.status}")
# 2. 校验核心变量非None
if Wk.value is None or R.value is None or tau.value is None:
    raise ValueError("求解器未返回有效结果（Wk/R/tau值为None）")
# 3. 校验通信相关变量非None
if numerator.value is None or denominator_interf.value is None or total_power.value is None:
    raise ValueError("通信/功率相关变量值为None")


# ======================================================
# 5. 构造秩1最优解（文章定理1：松弛后的解可恢复为秩1）
# ======================================================
# 从Wk构造用户波束向量wk（秩1）
trace_expr = cp.trace(Wk @ Hk)
trace_val = trace_expr.value
if trace_val is None or trace_val <= 0:
    raise ValueError("Tr(Wk Hk)无效，无法构造秩1波束")
wk = (Wk.value @ hk) / np.sqrt(trace_val)  # 归一化
Wk_rank1 = wk @ wk.conj().T  # 秩1用户波束矩阵

# 雷达协方差矩阵直接取最优解
R_opt = R.value


# ======================================================
# 6. 近场球面波特性可视化（距离-角度二维热力图）
# ======================================================
# 计算所有（距离-角度）采样点的波束增益
beam_gains_2d = []
for a in a_list_2d:
    combined_matrix = Wk_rank1 + R_opt
    gain = np.real(np.trace(a.conj().T @ combined_matrix @ a))
    beam_gains_2d.append(gain)
# 重塑为（距离数×角度数）的二维数组
beam_gains_2d = np.array(beam_gains_2d).reshape(T_rho, T_theta_new)
# 转换为dBm（参考功率1mW）
beam_gains_2d_dB = 10 * np.log10(beam_gains_2d / 1e-3)

# 绘图配置（解决中文显示）
plt.rcParams['font.sans-serif'] = ['SimHei', 'DejaVu Sans']
plt.rcParams['axes.unicode_minus'] = False

# 绘制距离-角度热力图
plt.figure(figsize=(12, 6))
im = plt.pcolormesh(
    rho_range, 
    np.rad2deg(theta_range_new),  # 弧度转角度
    beam_gains_2d_dB.T,  # 转置以匹配坐标轴（角度×距离）
    cmap='jet', 
    shading='gouraud'  # 平滑着色
)
# 标记目标位置 - 核心修改4：角度显示改为15°
for tr, ttheta in zip(target_rhos, target_thetas):
    plt.scatter(
        tr, np.rad2deg(ttheta), 
        color='white', s=50, marker='*', 
        label=f'目标 ({tr}m, {np.rad2deg(ttheta):.0f}°)'
    )

# 图表装饰
plt.colorbar(im, label='波束增益 (dBm)')
plt.xlabel('距离 (m)', fontsize=12)
plt.ylabel('角度 (°)', fontsize=12)
plt.title('近场球面波波束增益（距离-角度二维图）', fontsize=14)
plt.legend(fontsize=10)
plt.tight_layout()  # 调整布局避免重叠
plt.show()


# ======================================================
# 7. 结果细节输出（验证约束与性能）
# ======================================================
print("\n" + "="*50)
print("【1. 优化目标结果】")
print(f"SI区域最小波束增益 τ*: {tau.value:.4f} W ({10*np.log10(tau.value/1e-3):.1f} dBm)")

print("\n【2. 通信性能】")
# 确保numerator/denominator_interf的value非None后再运算
actual_sinr = 10 * np.log10(numerator.value / (denominator_interf.value + sigma2))
print(f"用户目标SINR: {gamma_k:.1f} dB，实际SINR: {actual_sinr:.1f} dB")

print("\n【3. 功率约束】")
print(f"总功率上限: {Pt_dBm:.1f} dBm，实际总功率: {10*np.log10(total_power.value/1e-3):.1f} dBm")

print("\n【4. 目标区域增益】")
# 核心修改5：角度索引改为15°对应的索引
for i, tr in enumerate(target_rhos):
    tr_idx = np.argmin(np.abs(rho_range - tr))
    theta_idx = np.argmin(np.abs(theta_range_new - np.pi/12))  # 找到15°对应的索引
    gain_tr = beam_gains_2d[tr_idx, theta_idx]
    print(f"目标{i+1} ({tr}m, 15°) 波束增益: {10*np.log10(gain_tr/1e-3):.1f} dBm")
print("="*50)