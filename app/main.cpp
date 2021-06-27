// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "../inc/Vector3d.hh"
#include "../inc/matrix3d.hh"
#include "../inc/lacze_do_gnuplota.hh"
#include "../inc/Scena.hh"


int main(){
  {
    PzG::LaczeDoGNUPlota Lacze;
    Scena Scena;
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(0, 140);
    Lacze.UstawZakresY(0, 140);
    Lacze.UstawZakresZ(0, 120);

    Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok
    bool ok;
    do
    {
        ok =Scena.wybierz_drona(Scena.Menu(Lacze), Lacze);
    }
    while ( ok != false);
  }
    std::cout << "Aktywne wektory: " << vector3d::daj_aktywne() << std::endl;
    std::cout << "Powstałe wektory: " << vector3d::daj_powstale() << std::endl;
  return 0;
}

