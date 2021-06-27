#include "../inc/gran_bryla.hh"

#define WZORZEC_STOZEK "../BrylyWzorcowe/szescianUP.dat"
#define WZORZEC_SZESCIAN "../BrylyWzorcowe/szescian.dat"
#define FOLDER_ROBOCZY "../datasets/"


void gran_bryla::InfoObiektu()
{
  std::cout << "Pozycja Graniastoslupa ze szczytem:" << daj_trans() << std::endl;
}

bool gran_bryla::Tworz_gran_bryla(){

  std::string PlikWyjsciowy;
  PlikWyjsciowy = "../BrylyWzorcowe/gran_bryla_" + std::to_string(NumerBryly) + ".dat";
  pobierz_nazwe_final(PlikWyjsciowy);
  pobierz_nazwe_wzorca(WZORZEC_STOZEK);
  std::ifstream IN(daj_wzorcowego());
  std::ofstream OUT(daj_wyjsciowego());
  vector3d PomVek;

  if (!IN.is_open())
  {
    std::cerr << std::endl
         << " Blad otwarcia do odczytu pliku: " << daj_wzorcowego() << std::endl
         << std::endl;
    return false;
  }

  if (!OUT.is_open())
  {
    std::cerr << std::endl
         << " Blad otwarcia do odczytu pliku: " << daj_wyjsciowego() << std::endl
         << std::endl;
    return false;
  }

  for (int index_up = 0; index_up < 5; ++index_up)
  {
    for (int index = 0; index < 4; ++index)
    {
      if (PomVek[2] > 0.5)
      {
        if (PomVek[0] < 0)
        {
          PomVek[0] = fabs(PomVek[0]);
        }
      }
      skaluj(PomVek);
      TransformujWspolrzednePunktu(PomVek);
      OUT << PomVek;
      IN >> PomVek;
      OUT << std::endl;
    }
    OUT << std::endl;
  }
  return !OUT.fail();
}