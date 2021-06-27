#include "../inc/dron.hh"

#define FOLDER_WLASCIWY "../BrylyWzorcowe/"
#define FOLDER_ROBOCZY "../datasets/"
#define WZORZEC_SZESCIAN "../BrylyWzorcowe/szescian.dat"
#define WZORZEC_ROTOR "../BrylyWzorcowe/graniastoslup6.dat"
#define TRASA_PRZELOTU "../datasets/trasa_przelotu.dat"

bool Dron::ZbudujDrona()
{

  static double KatObrotuRotora_st = 0;
  vector3d VekTrans[4];
  vector3d Pocz_Podniesienie;

  VekTrans[0][0] = 5;
  VekTrans[0][1] = 4;
  VekTrans[0][2] = 5;

  VekTrans[1][0] = 5;
  VekTrans[1][1] = -4;
  VekTrans[1][2] = 5;

  VekTrans[2][0] = -5;
  VekTrans[2][1] = 4;
  VekTrans[2][2] = 5;

  VekTrans[3][0] = -5;
  VekTrans[3][1] = -4;
  VekTrans[3][2] = 5;

  Pocz_Podniesienie[0] = 0;
  Pocz_Podniesienie[1] = 0;
  Pocz_Podniesienie[2] = 2;

  if (czy_aktywny == false)
  {
    if (!Korpus.ZbudujKorpus(Orientacja_drona, Pocz_Podniesienie))
      return false;
  }
  for (int Numer_rot = 0; Numer_rot < 4; ++Numer_rot)
  {
    if (!Rotor[Numer_rot].ZbudujRotor(Numer_rot, KatObrotuRotora_st, VekTrans[Numer_rot]))
      return false;
  }

  czy_aktywny = true;
  KatObrotuRotora_st += 15;

  return true;
}

bool Dron::owektor(unsigned int numer_drona)
{
  if (!ZbudujDrona())
    return false;

  std::string wzorzec_folder = FOLDER_WLASCIWY;
  std::string sciezka_korpusu = wzorzec_folder + "Dron_" + std::to_string(numer_drona) + "_Korpus_.dat";

  Korpus.ustaw_kat(Orientacja_drona);
  Korpus.ustaw_trans(PolozenieD);
  Korpus.pobierz_nazwe_final(sciezka_korpusu);
  if (!Korpus.zapiszbryle())
    return false;

  for (int numer_rotora = 0; numer_rotora < 4; ++numer_rotora)
  {
    Rotor[numer_rotora].ustaw_kat(Orientacja_drona);
    Rotor[numer_rotora].ustaw_trans(PolozenieD);
    std::string sciezka_rotora = wzorzec_folder + "Dron_" + std::to_string(numer_drona) + "_Rotor_" + std::to_string(numer_rotora) + ".dat";
    Rotor[numer_rotora].pobierz_nazwe_final(sciezka_rotora);
    if (!Rotor[numer_rotora].zapiszbryle())
      return false;
  }
  return true;
}

bool Dron::ZapiszTrase(int wysokosc, unsigned int odleglosc, double kat, PzG::LaczeDoGNUPlota &Lacze)
{
  std::ofstream out(TRASA_PRZELOTU);
  if (!out.is_open())
  {
    std::cerr << std::endl
              << " Nie mozna otworzyc do zapisu pliku: " << TRASA_PRZELOTU << std::endl
              << std::endl;
    return false;
  }

  vector3d end_Polozenie;
  vector3d Polozenie_kon;
  Polozenie_kon = PolozenieD;
  double Kat_rad;
  Kat_rad = kat * M_PI / 180;
  end_Polozenie[0] += cos(Kat_rad) * odleglosc;
  end_Polozenie[1] += sin(Kat_rad) * odleglosc;
  end_Polozenie[2] = wysokosc;
  end_Polozenie = end_Polozenie + Polozenie_kon;

  out << Polozenie_kon << std::endl;
  Polozenie_kon[2] = wysokosc;
  out << Polozenie_kon << std::endl
      << end_Polozenie << std::endl;
  end_Polozenie[2] = 0;
  out << end_Polozenie << std::endl;

  Lacze.DodajNazwePliku(TRASA_PRZELOTU);
  return !out.fail();
}

bool Dron::LotDrona(double kat, int Wysokosc, int odleglosc, unsigned int numer_drona, PzG::LaczeDoGNUPlota &Lacze)
{
  ZapiszTrase(Wysokosc, odleglosc, kat, Lacze);
  double pochylenie = 0;

  std::cout << std::endl
            << "Wznoszenie Trwa... " << std::endl;

  Lacze.Rysuj();
  usleep(1000000);
  for (; PolozenieD[2] <= Wysokosc; PolozenieD[2] += 2)
  {
    if (!owektor(numer_drona))
      return false;
    usleep(80000);
    Lacze.Rysuj();
  }
  PolozenieD[2] -= 2;

  std::cout << "Zmiana orientacji Trwa... " << std::endl;
  for (; Orientacja_drona < kat; Orientacja_drona += 5)
  {
    if (!owektor(numer_drona))
      return false;
    usleep(80000);
    Lacze.Rysuj();
  }

  std::cout << "Lot do przodu Trwa... " << std::endl;
  double OdlegloscPrzebyta = 0;
  vector3d KorekcjaPolozenia = PolozenieD;
  double KorekcjaKata = kat;
  for (; OdlegloscPrzebyta <= odleglosc; OdlegloscPrzebyta += odleglosc / 20)
  {
    LotDoPrzodu(kat, odleglosc / 20);
    if (!owektor(numer_drona))
      return false;
    pochylenie += 4;
    if (pochylenie == 50)
      pochylenie -= 4;
    if (OdlegloscPrzebyta > 15 * odleglosc / 20)
      pochylenie -= 4;
    usleep(80000);
    Lacze.Rysuj();
  }
  Popraw_Pozycje(KorekcjaPolozenia, KorekcjaKata, odleglosc);

  std::cout << "Opadanie trwa... " << std::endl;
  for (; PolozenieD[2] >= 0; PolozenieD[2] -= 2)
  {
    if (!owektor(numer_drona))
      return false;
    usleep(50000);
    Lacze.Rysuj();
  }
  PolozenieD[2] = 0;
  Lacze.Rysuj();
  Ustaw_kat(kat);

  return true;
}

void Dron::LotDoPrzodu(double kat, double odleglosc)
{
  double kat_rad;
  kat_rad = kat * M_PI / 180;
  PolozenieD[0] += cos(kat_rad) * odleglosc;
  PolozenieD[1] += sin(kat_rad) * odleglosc;
}

void Dron::Popraw_Pozycje(vector3d VekTrans, double kat, double odleglosc)
{
  double kat_rad;
  PolozenieD = VekTrans;
  kat_rad = kat * M_PI / 180;
  PolozenieD[0] += cos(kat_rad) * odleglosc;
  PolozenieD[1] += sin(kat_rad) * odleglosc;
}