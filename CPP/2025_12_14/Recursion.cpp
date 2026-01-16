#include <iostream>
using namespace std;

long long Fact(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * Fact(n - 1);
    }
}
long long Fib(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return Fib(n - 1) + Fib(n - 2);
    }
}
int main() {
    int num;
    cout << "请输入一个非负整数: ";
    cin >> num;

    if (num < 0) {
        cout << "输入错误，请输入非负整数。" << endl;
        return 1;
    }

    long long result = Fact(num);
    cout << num << " 的阶乘是: " << result << endl;

    result = Fib(num);
    cout << num << " 的斐波那契数是: " << result << endl;
    
    return 0;


}