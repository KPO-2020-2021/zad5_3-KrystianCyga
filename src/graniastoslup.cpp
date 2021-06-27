#include "../inc/graniastoslup.hh"

#define WZORZEC_ROTOR "../BrylyWzorcowe/graniastoslup6.dat"
#define FOLDER_ROBOCZY "../datasets/"

bool graniastoslup::ZbudujRotor(unsigned int Numer_Rotora, double Kat_Obrotu, vector3d VekTrans)
{
    NumerWierzcholka = 28;
    Orientacji_stopnie = Kat_Obrotu;
    trans = VekTrans;
    skala[0] = 8;
    skala[1] = 8;
    skala[2] = 2;
    std::string plik_wzorcowy = WZORZEC_ROTOR;
    NazwaWzorcowego = WZORZEC_ROTOR;

    if (Numer_Rotora == 2 || Numer_Rotora == 3)
    {
        Orientacji_stopnie = -Orientacji_stopnie;
    }
    return wczytajbryle();
}

void graniastoslup::ObrocRotor(unsigned int Numer_Rotora, double Kat_Obrotu)
{
    NumerWierzcholka = 28;
    Orientacji_stopnie = Kat_Obrotu;
    vector3d VekTrans;

    if (Numer_Rotora == 2 || Numer_Rotora == 3)
    {
        Orientacji_stopnie = -Orientacji_stopnie;
    }

    for (unsigned int akt_wierz = 0; akt_wierz < NumerWierzcholka; ++akt_wierz)
    {
        VekTrans = wierzcholki[akt_wierz];
        TransformujWspolrzednePunktu(VekTrans);
        wierzcholki[akt_wierz] = VekTrans;
    }
}