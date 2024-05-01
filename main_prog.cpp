#include <iostream>
#include "Polinom.h"
#include "Polinom.cpp"

using namespace std;

int main()
{
    //Az objektumok konstruálása
    Polinom P1, P2;
    cout << "Elso polinom:\n";
    cin>>P1;

    cout << "Masodik polinom:\n";
    cin>>P2;

    //A műveletek tesztelése

    cout<<endl<<"A beolvasott elso polinom:"<<endl<<P1<<endl;
    cout<<"A beolvasott masodik polinom:"<<endl<<P2<<endl;
    cout<<endl<<"A muveletek tesztelese."<<endl<<endl;
    cout<< "Osszeg:"<<endl<<P1+P2<<endl<<endl;
    cout<<"Kulonbseg:"<<endl<<P1-P2<<endl<<endl;
    cout<<"Szorzat:"<<endl<<P1*P2<<endl<<endl;
    cout<<"Az elso polinom derivaltja:"<<endl<<P1.deriv()<<endl;
    cout<<"A masodik polinom derivaltja:"<<endl<<P2.deriv()<<endl;
    cout<<endl<<"Az elso polinom integralja:"<<endl<<P1.integral()<<endl;
    cout<<"A masodik polinom integralja:"<<endl<<P2.integral()<<endl;
    return 0;
}
