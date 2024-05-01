#include "Polinom.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

//Polinom valtozok inicializalasa konstruktorokkal
Polinom::Polinom(vector<double>egyhk): egyutthatok(egyhk) {}
Polinom::Polinom() {}

//A belolvasas muvelete
istream& operator>>(istream& in, Polinom& poli)
{
    poli.egyutthatok.clear(); //Kitorli az eddig beolvasott adatokat

    int fok;

    //Kepernyorol beolvasas elvegzese
    cout << "Add meg a polinom fokszamat: ";
    while (!(in >> fok)) {
        //ha nem szamot adtunk meg adjon hibauzenetet
        cout << "Ervenytelen bemenet, kerjuk adjon meg egy szamot: ";
        in.clear();
        in.ignore( numeric_limits< streamsize>::max()); // ervenytelen bemenetetet dobja ki
        }

    poli.egyutthatok.resize(fok+1); //Megfelelo meretuve alakitjuk az egyutthatovektort
    for (int i=fok; i>=0; --i)
    {
        cout<<"Add meg az x^"<<i<<" egyutthatojat (valos szam): ";
        while (!(in >> poli.egyutthatok[i])) {
            //ervenytelen bemenet ha nem szam
            cout << "Ervenytelen bemenet, kerjuk adjon meg egy szamot: ";
            in.clear();
            in.ignore( numeric_limits< streamsize>::max());
        }
    }
    return in;
}

//A kiiratas muvelete
ostream& operator<<(ostream& out, const Polinom& poli)
{
    bool elsotag=true; //Segedvaltozo, ami meggatolja, hogy az elso tag ele "+" jelet irjunk
    for (int i=poli.egyutthatok.size()-1; i>=0; --i)
    {
        if (poli.egyutthatok[i] !=0)
        {
            if(!elsotag)
            {
                out << "+";
            }
            else{ elsotag=false;}

            //A "egyutthato * x^n" szerkezet kiirasa, es annak kulonbozo esetei
            if(i==0 || poli.egyutthatok[i] !=1)
            {
                out<< poli.egyutthatok[i];
            }
            if(i>0)
            {
                out<<"x";
                if(i>1)
                {
                    out<<"^"<<i;
                }
            }
        }
    }
    return out;
}

//Az osszeadas muvelete
Polinom Polinom::operator+(const Polinom & other) const
{
    //Egy megfelelo meretu eredmenypolinom letrehozasa
    Polinom eredm;
    size_t meret = max(egyutthatok.size(), other.egyutthatok.size()); //A ketto osszeadando tag fokszama kozul a nagyobb lesz az eredmeny fokszama
    eredm.egyutthatok.resize(meret);

    //Az osszeadas muveletenek elvegzese
    for(size_t i=0; i<meret; i++)
    {
        double egyh1 = (i < egyutthatok.size()) ? egyutthatok[i] : 0.0;
        double egyh2 = (i < other.egyutthatok.size()) ? other.egyutthatok[i] : 0.0;
        eredm.egyutthatok[i] = egyh1 + egyh2; //fokszamonkent osszeadjuk az egyutthatokat
    }
    return eredm;
}

//A kivonas muvelete
Polinom Polinom::operator-(const Polinom& other) const
{
    //Megfelelo meretu polinom letrehozasa
    Polinom eredm;
    size_t meret = max(egyutthatok.size(), other.egyutthatok.size());
    eredm.egyutthatok.resize(meret, 0.0); //Nullakkal toltjuk fel az eredmeny vektorat

    //A nullakhoz a kissebitedot hozzaadjuk, a kivonandot meg levonjuk belole
    for (size_t i=0; i<egyutthatok.size(); i++)
    {
        eredm.egyutthatok[i] += egyutthatok[i];
    }
    for (size_t i=0; i<other.egyutthatok.size(); i++)
    {
        eredm.egyutthatok[i] -= other.egyutthatok[i];
    }
    return eredm;

}

//A szorzas muvelete
Polinom Polinom::operator*(const Polinom& other) const
{
    //Letrehozzuk a megfelelo meretu szorzatvektort
    size_t fok = egyutthatok.size() + other.egyutthatok.size() - 2;
    size_t meret = fok+1;
    vector <double> szorzategyh(meret, 0.0);

    //A szorzas muveletenek elvegzese
    for (size_t i=0; i<egyutthatok.size(); i++)
    {
        for (size_t j=0; j<other.egyutthatok.size(); j++)
        {
            szorzategyh[i+j] += egyutthatok[i] * other.egyutthatok[j]; //pl. 6*x^(4+2) = 3*x^4 * 2*x^2
        }
    }
    return Polinom(szorzategyh);
}

//A derivalas muvelete
Polinom Polinom::deriv() const
{
    //Ha ures a vektor vagy csak egy konstans tag van benne, akkor a derivalt nulla.
    if (egyutthatok.empty() || egyutthatok.size()==1)
    {
        return Polinom({0.0});
    }

    //A derivaltvektor fokszama eggyel kisebb, mint az eredetié
    vector <double> derivalt_egyutthatok(egyutthatok.size() - 1);
    for (size_t i=1; i<egyutthatok.size(); i++)
    {
        derivalt_egyutthatok[i-1] = egyutthatok[i]*i; // pl. 6*x^2 = deriv(2*x^3)
    }
    return Polinom(derivalt_egyutthatok);
}

//Az integralas muvelete
Polinom Polinom::integral() const
{
    //Ha ures a vektor, akkor nulla az integral
    if(egyutthatok.empty())
    {
        return Polinom({0.0});
    }
    //A polinom integraltjanak a fokszama eggyel nagyobb, mint az eredetie
    vector <double> integral_egyutthatok(egyutthatok.size()+1);
    //Az integralas elvegzese
    for (size_t i=0; i<egyutthatok.size(); i++)
    {
        //A kontans tag integralasa
        if (i==0)
        {
            integral_egyutthatok[i+1] = egyutthatok[i];
        }
        //A tobbi tag integralasa
        else
        {
            if(egyutthatok[i] != 0)
            {
                integral_egyutthatok[i+1] = egyutthatok[i]/(i+1); //pl. (2/3)*x^3 = integral (2*x^2)
            }
            else {integral_egyutthatok[i+1] = 0.0;}
        }
    }
    return Polinom(integral_egyutthatok);
}
