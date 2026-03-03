#include <iostream>
using namespace std;

int main()
{
    int inicial = 123;

    cout << "Valor inicial:" << inicial << endl;
    cout << "Valor Inverso:";
    cout << inicial % 100 % 10 / 1;
    cout << inicial % 100 / 10;
    cout << inicial / 100 << endl;

    int final = (inicial / 100) + (((inicial / 10) % 10) * 10) + (((inicial % 100) % 10) * 100);

    cout << "Valor final Variavel:" << final << endl; 

    return 0;

}
