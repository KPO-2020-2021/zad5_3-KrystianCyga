#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <memory>
#include <unistd.h>
#include "../inc/Vector3d.hh"
#include "../inc/matrix.hh"
#include "../inc/lacze_do_gnuplota.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Obiekt
 */

class Obiekt
{
protected:
    std::string NazwaWzorcowego;
    std::string NazwaWyjsciowego;
    vector3d wielkosc[2];

public:
    
    virtual void InfoObiektu(){};

    virtual std::string dajNazweWyjsciowego() { return NazwaWzorcowego; };
    virtual std::string dajNazweWzorcowego() { return NazwaWyjsciowego; };

    virtual void ustaw_wielkosc();
    virtual vector3d daj_wielkosc();
    virtual bool czy_koliduje(std::list<std::shared_ptr<Obiekt>> Przeszkody);
    
};