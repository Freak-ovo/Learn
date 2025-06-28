import numpy as np

#初始化数据
x = np.array([[10, 2, 1],
              [2, 7, 1],
              [1, 5, 1],
              [4, 1, 1]])#(4,3)
#初始化期望
y = np.array([[0, 1, 1, 0]]).T #(4,1)

#初始化权重
w01 = np.random.random((3,4))#(3,4)
w12 = np.random.random((4,2)) #(4,2)
w23 = np.random.random((2,1)) #(4,1)

#初始化偏移
bias01 = np.random.random((1,4))
bias12 = np.random.random((1,2))
bias23 = np.random.random((1,1))

# sigmoid 函数
def sigmoid(x,d = False):
    if d == False:
        return 1 / (1 + np.exp(-x))
    else:
        return x * (1-x)
    
#开始训练
for _ in range(1000):
    in_0 = x    #(4,3)
    out_0 = in_0#(4,3)

    in_1 = np.dot(out_0,w01) + bias01 #(4,3)*(3,4) + (4,4)
    out_1 = sigmoid(in_1)

    in_2 = np.dot(out_1,w12) + bias12 #(4,4)*(4,2) + (4,2)
    out_2 = sigmoid(in_2)

    in_3 = np.dot(out_2,w23) + bias23 #(4,2)*(2,1) + (4,1)
    out_3 = sigmoid(in_3)
    
    e3 = y - out_3
    delta3 = e3 * sigmoid(out_3, d = True) #(4,1) * (4,1) = (4,1)

    e2 = delta3 @ w23.T #(4,1)@(2,1) = (4,2)
    delta2 = e2 * sigmoid(out_2, d = True)

    e1 = delta2 @ w12.T  #(4,2) @ (2,4) = (4,4)
    delta1 = e1 * sigmoid(out_1, d = True)
    """ 
        out_0 (4,3)    delta1 (4,4)    e1 (4,4)
        out_1 (4,4)    delta2 (4,2)    e2 (4,2)
        out_2 (4,2)    delta3 (4,1)    e3 (4,1)

    """

    #更新权重
    w23 += out_2.T @ delta3 #(2,4) @ (4,1) = (2,1)
    w12 += out_1.T @ delta2 #(4,4) @ (4,2) = (4,2)
    w01 += out_0.T @ delta1 #(3,4) @ (4,4) = (3,4)

    #更新偏置
    bias23 += np.sum(delta3, axis=0)
    bias12 += np.sum(delta2, axis=0)
    bias01 += np.sum(delta1, axis=0) 

print(out_3)
