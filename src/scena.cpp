#include "../inc/Scena.hh"

#include <algorithm>
#include <vector>
#include <memory>

#define FOLDER_WLASCIWY "../BrylyWzorcowe/"
#define FOLDER_ROBOCZY "../datasets/"
#define TRASA_PRZELOTU "../datasets/trasa_przelotu.dat"

bool Scena::wybierz_drona(int numer_drona, PzG::LaczeDoGNUPlota &Lacze)
{
  if (numer_drona < 0) return false;

  double Kat;
  int odleglosc;

  std::cout << "Podaj kat lotu drona: ";
  std::cin >> Kat;
  std::cout << std::endl
            << "Podaj odleglosc lotu drona: ";
  std::cin >> odleglosc;
  std::cout << std::endl;


if (!Uzyj_drona(numer_drona, Kat, odleglosc, Lacze))
    return false;
  return true;
}

bool Scena::Zapis_drona(unsigned int numer_drona, vector3d &polozenie)
{
  Dron newDron;
  std::shared_ptr<Dron> ptrDron = std::make_shared<Dron>();

  ptrDron->Ustaw_polozenie(polozenie);
  newDron.Ustaw_polozenie(polozenie);
  ptrDron->Ustaw_kat(0);
  newDron.Ustaw_kat(0);
  Drony.push_back(newDron);
  Drony[numer_drona].ZbudujDrona();
  Przeszkody.push_back(ptrDron);

  if (!Drony[numer_drona].owektor(numer_drona))
    return false;
  return true;
}

bool Scena::Uzyj_drona(int numer_drona, double kat, unsigned int odleglosc, PzG::LaczeDoGNUPlota &Lacze)
{
  
    std::string wlasciwy = FOLDER_WLASCIWY;
    std::string roboczy = FOLDER_ROBOCZY;
    for (unsigned int index = 0; index < liczba_dronow; ++index)
    {
      std::string sciezka_korpusu = wlasciwy + "Dron_" + std::to_string(index) + "_Korpus_.dat";
      const char *ptr_sciezka_korpusu = sciezka_korpusu.c_str();
      Lacze.DodajNazwePliku(ptr_sciezka_korpusu);
      for (unsigned int numer_rotora = 0; numer_rotora < 4; ++numer_rotora)
      {
        std::string sciezka_rotora = wlasciwy + "Dron_" + std::to_string(index) + "_Rotor_" + std::to_string(numer_drona) + ".dat";
        const char *ptr_sciezka_rotora = sciezka_rotora.c_str();
        Lacze.DodajNazwePliku(ptr_sciezka_rotora);
      }
    }

    if (!Drony[numer_drona].owektor(numer_drona))
      return false;
    Lacze.Rysuj();

    if (!Drony[numer_drona].LotDrona(kat, 50, odleglosc, numer_drona, Lacze))
      return false;
    return true;
  
}

void Scena::Dodaj_Przeszkody(PzG::LaczeDoGNUPlota &Lacze)
{

  int wybor;
  vector3d pozycja, skala;
  double kat = 0;
  std::shared_ptr<brylageo> ptr_bryla;

  std::cout << "Jaka przeszkode chcialbys dodac?" << std::endl;
  std::cout << "1. Gora z ostrym szczytem" << std::endl;
  std::cout << "2. Gora z grania" << std::endl;
  std::cout << "3. Wyzyna ze stokiem" << std::endl
            << std::endl;
  std::cin >> wybor;
  std::cout << "Podaj wspolrzedne OX, OY, OZ przeszkody:" << std::endl
            << std::endl;
  std::cin >> pozycja;
  std::cout << "Podaj skale przeszkody OX, OY, OZ :" << std::endl
            << std::endl;
  std::cin >> skala;

  switch (wybor)
  {
  case 1:
    ptr_bryla = std::make_shared<stozek>(Lacze, pozycja, kat, skala);
    break;
  case 2:
    ptr_bryla = std::make_shared<gran_bryla>(Lacze, pozycja, kat, skala);
    break;
  case 3:
    ptr_bryla = std::make_shared<wyzyna>(Lacze, pozycja, kat, skala);
    break;

  default:
    std::cout << "Wybrales bledna opcje - sprobuj jeszcze raz" << std::endl;
    break;
  }
 
  Przeszkody.push_front(ptr_bryla);
  std::string nazwa = ptr_bryla.get()->daj_wyjsciowego();
  const char *sciezka= nazwa.c_str();
  Lacze.DodajNazwePliku(sciezka);
  Lacze.Rysuj();
}

void Scena::Usun_Przeszkody(PzG::LaczeDoGNUPlota &Lacze)
{

  std::list<std::shared_ptr<Obiekt>> ptr_przeszkody;
  std::shared_ptr<Obiekt> ptrBryla = std::make_shared<Obiekt>();
  ptr_przeszkody = Przeszkody;
  long unsigned int wybor;
  std::cout << "Wybierz figure do usuniecia : " << std::endl;
  for (int i = 0; i < (int)Przeszkody.size(); i++)
  {
    std::cout << i + 1 << ". ";
    ptrBryla = ptr_przeszkody.front();
    ptrBryla.get()->InfoObiektu();
    ptr_przeszkody.pop_front();
  }
  ptr_przeszkody = Przeszkody;
  std::cout << std::endl;
  std::cin >> wybor;
  if (wybor <= Przeszkody.size())
  {
    std::cerr << "Zly wybor";
  }
  for (long unsigned int index = 1; index < wybor; index++)
  {
    ptr_przeszkody.pop_front();
  }
  Przeszkody.remove(ptr_przeszkody.front());
  Lacze.UsunNazwePliku(ptr_przeszkody.front().get()->dajNazweWyjsciowego());
  Lacze.Rysuj();
}

int Scena::Menu(PzG::LaczeDoGNUPlota &Lacze)
{
  unsigned int numer_drona = 0;
  vector3d PolozenieStart;
  PolozenieStart[0] = 20;
  PolozenieStart[1] = 20;
  char wybor = 'o';
  if (liczba_dronow == 0)
  {
    Zapis_drona(numer_drona, PolozenieStart);
    ++liczba_dronow;
    Lacze.DodajNazwePliku("../BrylyWzorcowe/plaszczyzna.dat");
  }

  std::shared_ptr<brylageo> ptrBryla;
  vector3d Pozycja, Skala;
  Pozycja[0] = 40;
  Pozycja[1] = 60;
  Pozycja[2] = 0;
  Skala[0] = 4;
  Skala[1] = 5;
  Skala[2] = 8;
  ptrBryla = std::make_shared<stozek>(Lacze, Pozycja, 0, Skala);
  Przeszkody.push_front(ptrBryla);
  Pozycja[0] = 80;
  Pozycja[1] = 100;
  Skala[0] = 4;
  Skala[1] = 9;
  Skala[2] = 8;
  ptrBryla = std::make_shared<gran_bryla>(Lacze, Pozycja, 0, Skala);
  Przeszkody.push_front(ptrBryla);
  Pozycja[0] = 20;
  Pozycja[1] = 20;
  Skala[0] = 7;
  Skala[1] = 5;
  Skala[2] = 2;
  ptrBryla = std::make_shared<wyzyna>(Lacze, Pozycja, 0, Skala);
  Przeszkody.push_front(ptrBryla);

  while (wybor != 3)
  {

    if (wybor == 'o')
    {
      std::cout << std::endl
                << std::endl
                << "Dron 1 na pozycji: \n"
                << Drony[0].daj_polozenie() << std::endl
                << std::endl;
      std::cout << "Wybierz opcje:" << std::endl
                << "1. Dodaj drona" << std::endl
                << "2. Wyswietl liste dostepnych dronow" << std::endl
                << "3. Przejdz do ustawienia trasy" << std::endl
                << "4. Dodaj przeszkode w postaci figury" << std::endl
                << "5. Usuń przeszkode" << std::endl
                << "6. Menu programu" << std::endl
                << "7. Zakoncz program" << std::endl<< std::endl;
    }
    std::cin >> wybor;
    switch (wybor)
    {
    case ('1'):
      std::cout << std::endl
                << "Podaj wspolrzedne startowe drona:" << std::endl
                << std::endl;std::cin >> PolozenieStart;std::cout << std::endl;
      Zapis_drona(numer_drona, PolozenieStart);
      ++liczba_dronow;
      numer_drona = liczba_dronow;
      break;
    case ('2'):
      std::cout << std::endl
                << std::endl
                << "Lista dostępnych dronow:" << std::endl;
      for (unsigned int index = 0; index < liczba_dronow; ++index)
      {
        std::cout << "Dron " << index + 1 << " na pozycji: \n"
                  << Drony[index].daj_polozenie() << std::endl;
      }
      break;
    case ('3'):
      std::cout << "Ktorego wybierasz?" << std::endl;
      for (unsigned int index = 0; index < liczba_dronow; ++index)
      {
        std::cout << "Dron " << index + 1 << " na pozycji: \n"
                  << Drony[index].daj_polozenie() << std::endl;
      }
      std::cout << std::endl
                << "Podaj numer drona:";
      std::cin >> numer_drona;
      if (numer_drona == 0 || numer_drona > liczba_dronow)
      {
        std::cout << "Zly nr drona. Poleci dron nr 1." << std::endl;
        return 0;
      }

      return (numer_drona - 1);
      break;
    case ('4'):
      Dodaj_Przeszkody(Lacze);
      break;
    case ('5'):
      Usun_Przeszkody(Lacze);
      break;
    case ('6'):
       std::cout << "Wybierz opcje:" << std::endl
                << "1. Dodaj drona" << std::endl
                << "2. Wyswietl liste dostepnych dronow" << std::endl
                << "3. Przejdz do ustawienia trasy" << std::endl
                << "4. Dodaj przeszkode w postaci figury" << std::endl
                << "5. Usuń przeszkode" << std::endl
                << "6. Menu programu" << std::endl
                << "7. Zakoncz program" << std::endl<< std::endl;
      break;
    case ('7'):
        std::cout << "Zakonczono dzialanie programu." << std::endl;
      

      return -1;
      break;
    default:
      std::cout << "Wybrales bledna opcje - sprobuj jeszcze raz" << std::endl;
      break;
    }
    std::cout << std::endl<< "Wcisnij 6 aby wyświetlic menu."<< std::endl;
  }
  return -1;
}
