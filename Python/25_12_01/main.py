import cvxpy as cp
import numpy as np
from scipy.linalg import eigh


def sdr_max_cut(W):
    """
    用SDR求解最大割问题

    参数：
        W: 图的权重矩阵（n×n对称矩阵）

    返回：
        cut_value: 割边权重
        partition: 顶点划分（S和V\S）
    """
    n = W.shape[0]

    # 步骤1：定义SDP变量
    X = cp.Variable((n, n), symmetric=True)

    # 步骤2：定义目标函数
    sum_W = np.sum(W)
    objective = cp.Maximize(0.25 * (sum_W - cp.trace(W @ X)))

    # 步骤3：定义约束
    constraints = [X >> 0]  # X半正定
    constraints += [X[i, i] == 1 for i in range(n)]  # 对角元为1

    # 步骤4：求解SDP
    problem = cp.Problem(objective, constraints)
    problem.solve(solver=cp.SCS, verbose=False)  # 用SCS求解

    # 步骤5：特征分解（取主特征向量）
    eigenvalues, eigenvectors = eigh(X.value)
    max_eig_idx = np.argmax(eigenvalues)
    v = eigenvectors[:, max_eig_idx]  # v是n维特征向量

    # 步骤6：修正随机舍入（生成n维离散变量）
    r = np.random.randn(n)  # n维随机向量
    r = r / np.linalg.norm(r)  # 归一化
    x = np.sign(v * r)  # 元素-wise乘积后取符号 → n维数组（关键修正！）

    # 步骤7：计算割边权重
    S = np.where(x == 1)[0]
    not_S = np.where(x == -1)[0]
    cut_value = 0
    for i in S:
        for j in not_S:
            cut_value += W[i, j]

    partition = (S, not_S)
    return cut_value, partition


# 测试：三角形图（3个节点，权重均为1）
if __name__ == "__main__":
    # 权重矩阵（无向图，对称）
    W = np.array([
        [0, 1, 1],
        [1, 0, 1],
        [1, 1, 0]
    ])

    # 多次运行取最优（随机舍入可能有波动）
    max_cut = -1  # 初始化为负数，确保首次结果能更新
    best_partition = None
    for _ in range(10):
        cut_val, part = sdr_max_cut(W)
        if cut_val > max_cut:
            max_cut = cut_val
            best_partition = part

    # 确保best_partition非空
    if best_partition is None:
        best_partition = (np.array([]), np.arange(3))

    print(f"最大割权重: {max_cut}")
    print(f"顶点划分: S={best_partition[0]}, V\\S={best_partition[1]}")