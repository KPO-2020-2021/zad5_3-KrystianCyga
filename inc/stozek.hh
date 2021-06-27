#pragma once

#include "brylageo.hh"

/*!
 * \file
 * \brief Plik zawiera definicję klasy stozek
 */

class stozek : public brylageo
{
public:
    /*!
     * \brief Wczytuje i zapisuje figure postaci stozka
     *
     * Przeksztalca i odpowiednio transformuje bryle 
     *
     * \retval true - Operacja sie powiodla
     * \retval false - Operacja sie nie powiodla    
     */
    bool Zbudujstozek();

    stozek(){};

    stozek(PzG::LaczeDoGNUPlota &Lacze, vector3d polozenie, double kat_orien, vector3d Skala) : brylageo(polozenie, kat_orien, Skala)
    {
        Zbudujstozek();
        NazwaWyjsciowego = dajNazweWyjsciowego();
        const char *ptrNazwa = NazwaWyjsciowego.c_str();
        Lacze.DodajNazwePliku(ptrNazwa);
        ++NumerBryly;
    }

    /*!
     * \brief Wyswietla pozycję figury
     */
    void InfoObiektu();
};