#ifndef POLINOM_H

#define POLINOM_H

#include<iostream>
#include<vector>

using namespace std;

//A polinom struktúrájának definiálása
struct Polinom
{
    vector <double> egyutthatok;

    //Egy kezdőértékekkel ellátott, és egy üres konstruktor definiálása
    Polinom (vector <double> egyhk);
    Polinom ();

    //Műveletek inicializálása
    Polinom operator+ (const Polinom& other) const;
    Polinom operator- (const Polinom& other) const;
    Polinom operator* (const Polinom& other) const;
    Polinom deriv() const;
    Polinom integral() const;

};

//A kiíratás és a beolvasás műveletének definiálása
ostream& operator<<(ostream& out, const Polinom& poli);
istream& operator>>(istream& in, Polinom& poli);



#endif // POLINOM_H_INCLUDED
