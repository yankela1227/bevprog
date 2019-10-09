#include <iostream>

using namespace std;

int main()
{
    int a,b;
    cout <<"Kerem az elso szamot: ";
    cin >> a;
    cout <<"Kerem a masodik szamot: ";
    cin >> b;
    cout <<"Eredeti a: "<<a<<endl;
    cout <<"Eredeti b: "<<b<<endl;
    //csere
    a=a*b;
    b=a/b;
    a=a/b;
    cout << "Uj a: "<<a<< endl;
    cout << "Uj b: "<<b<< endl;
    return 0;
}
