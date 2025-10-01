#include <iostream>
using namespace std;

class Person
{

public:

    void ShowClassName()
    {
        cout << "this is Person class" << endl;
    }

    void ShowPersonAge()
    {
        if (this == NULL)
        {
            return;
        }
        
        cout << "Age = " << Age<< endl;
    }
    int Age;


};

void Test()
{
    Person *P = NULL;
    P->ShowClassName();
    P->ShowPersonAge();
    
}

int main()
{
    Test();
}