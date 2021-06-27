#include "../inc/brylageo.hh"

#define FOLDER_WLASCIWY "../BrylyWzorcowe/"
#define FOLDER_ROBOCZY "../datasets/"
#define WZORZEC_SZESCIAN "../BrylyWzorcowe/szescian.dat"
#define WZORZEC_ROTOR "../BrylyWzorcowe/graniastoslup6.dat"

#include <fstream>

brylageo::brylageo()
{
    skala[0] = 1;
    skala[1] = 1;
    skala[2] = 2;
}

brylageo::brylageo(vector3d polozenie, double kat, const vector3d skala2)
{
    skala = skala2;
    trans = polozenie;
    Orientacji_stopnie = kat;
}

void brylageo::pobierz_nazwe_wzorca(const std::string nazwa1){
    NazwaWzorcowego=nazwa1;
}

void brylageo::pobierz_nazwe_final(const std::string nazwa2){
    NazwaWyjsciowego=nazwa2;
}


void brylageo::skaluj(vector3d &skala2)
{
    skala2[0] *= skala[0];
    skala2[1] *= skala[1];
    skala2[2] *= skala[2];
}

void brylageo::ObrocWzgledemOsiOZ(double kat, vector3d &Polozenie)
{
    vector3d wynik;
    double rad = kat * M_PI / 180;
    wynik[0] = Polozenie[0] * cos(rad) - Polozenie[1] * sin(rad);
    wynik[1] = Polozenie[0] * sin(rad) + Polozenie[1] * cos(rad);
    Polozenie[0] = wynik[0];
    Polozenie[1] = wynik[1];
}

void brylageo::TransformujWspolrzednePunktu(vector3d &Polozenie)
{
    vector3d wynik;
    ObrocWzgledemOsiOZ(Orientacji_stopnie, Polozenie);
    skaluj(Polozenie);
    wynik = Polozenie + trans;
    Polozenie = wynik;
}

bool brylageo::wczytajbryle()
{

    std::ifstream Plik_BrylaWzorcowa(NazwaWzorcowego);

    if (!Plik_BrylaWzorcowa.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: " << NazwaWzorcowego << std::endl
                  << std::endl;
        return false;
    }
    vector3d PoTrans;
    long unsigned int index = 0;
    wierzcholki.reserve(17);

    for (unsigned int nrWierz = 0; nrWierz < NumerWierzcholka;++nrWierz)
    {
        Plik_BrylaWzorcowa >> PoTrans;

        TransformujWspolrzednePunktu(PoTrans);
        ++index;
        if (wierzcholki.size() < index)
            wierzcholki.push_back(PoTrans);
        else
            wierzcholki[index] = PoTrans;
    }
    index = 0;
    return true;
}

void brylageo::ustaw_wielkosc(vector3d &tmp){
  if (wierzcholki.size() == 0)
  {
    wielkosc[0][0] = 1000;
    wielkosc[0][1] = 1000;
  }
  if (tmp[0] < wielkosc[0][0])
    wielkosc[0][0] = tmp[0];
  if (tmp[0] > wielkosc[1][0])
    wielkosc[1][0] = tmp[0];
  if (tmp[1] < wielkosc[0][1])
    wielkosc[0][1] = tmp[1];
  if (tmp[1] > wielkosc[1][1])
    wielkosc[1][1] = tmp[1];
}

bool brylageo::zapiszbryle()
{
    skala[0] = 1;
    skala[1] = 1;
    skala[2] = 1;
    std::ofstream PLIK(NazwaWyjsciowego);

    if (!PLIK.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: " << NazwaWyjsciowego << std::endl
                  << std::endl;
        return false;
    }

    vector3d PoTrans;
    int index = 0;
    {

        for (unsigned int nrWierz = 0; nrWierz < NumerWierzcholka;
             ++nrWierz)
        {
            PoTrans = wierzcholki[nrWierz];
            TransformujWspolrzednePunktu(PoTrans);
            ustaw_wielkosc(PoTrans);
            PLIK << std::fixed << PoTrans << std::endl;
            ++index;
            if (index == 4)
            {
                index = 0;
                PLIK << std::endl;
            }
        }
        PLIK << std::endl;
    }
    return !PLIK.fail();
}