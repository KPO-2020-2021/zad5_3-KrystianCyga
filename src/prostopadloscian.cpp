#include "../inc/prostopadloscian.hh"

#define FOLDER_ROBOCZY "../datasets/"
#define WZORZEC_SZESCIAN "../BrylyWzorcowe/szescian.dat"

bool Prostopadloscian::ZbudujKorpus(double Kat_Obrotu, vector3d VekTrans)
{
    NumerWierzcholka = 20;
    Orientacji_stopnie = Kat_Obrotu;
    trans = VekTrans;
    std::string plik_wzorcowy = WZORZEC_SZESCIAN;

    NazwaWzorcowego = WZORZEC_SZESCIAN;
    skala[0] = 10;
    skala[1] = 8;
    skala[2] = 4;
    return wczytajbryle();
}