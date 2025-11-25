# 字符串 相关模块


def str_reverse(s):
    '''
    功能是将字符串完成反转
    :param s: 待反转的字符串
    :return: 反转后的字符串
    '''
    return(s[::-1])


def str_substr(s, x, y):
    '''
    
    :param s: 待反转的字符串
    :param x: 开始下表
    :param y: 结束下标
    :return:  切片完成后的字符串
    '''
    return(s[x:y:])

if __name__ == '__main__':
    print(str_reverse("春风若有怜花意"))
    print(str_reverse("可否许我在少年"))