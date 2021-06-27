#pragma once

#include "../inc/brylageo.hh"

/*!
 * \file
 * \brief Plik zawiera definicje klasy gran_bryla
 */

class gran_bryla : public brylageo
{
public:
  /*!
     * \brief Wczytuje i zapisuje figure postaci graniastoslupa
     *
     * Przeksztalca i odpowiednio transformuje bryle 
     *
     * \retval true - Operacja sie powiodla
     * \retval false - Operacja sie nie powiodla    
     */
  bool Tworz_gran_bryla();

  gran_bryla(){};

  gran_bryla(PzG::LaczeDoGNUPlota &Lacze, vector3d polozenie, double kat_orien, vector3d Skala) : brylageo(polozenie, kat_orien, Skala)
  {
        Tworz_gran_bryla();
        NazwaWyjsciowego = dajNazweWyjsciowego();
        const char *ptrNazwa = NazwaWyjsciowego.c_str();
        Lacze.DodajNazwePliku(ptrNazwa);
        ++NumerBryly;
  }

  /*!
  * \brief Wyswietla pozycję przeszkody
  */
  void InfoObiektu();
};