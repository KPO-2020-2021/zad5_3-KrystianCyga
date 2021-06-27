#pragma once

#include "../inc/brylageo.hh"

/*!
 * \file
 * \brief Plik zawiera definicję klasy wyzyna
 */

class wyzyna : public brylageo
{
public:
    /*!
     * \brief Wczytuje i zapisuje figure postaci wyzyny
     *
     * Przeksztalca i odpowiednio transformuje bryle 
     *
     * \retval true - Operacja sie powiodla
     * \retval false - Operacja sie nie powiodla    
     */
    bool ZbudujWyzyne();

    wyzyna(){};

    wyzyna(PzG::LaczeDoGNUPlota &Lacze, vector3d polozenie, double kat_orien, vector3d Skala) : brylageo(polozenie, kat_orien, Skala)
    {
        ZbudujWyzyne();
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