#pragma once

#include "stozek.hh"
#include "wyzyna.hh"
#include "gran_bryla.hh"
#include "dron.hh"
#include "Obiekt.hh"
#include "brylageo.hh"

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <memory>

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Scena
 */

class Scena
{
  std::vector<Dron> Drony;
  std::list<std::shared_ptr<Obiekt>> Przeszkody;

  unsigned int liczba_dronow = 0;

  int kolizja;

public:
/*!
 * \brief Pobiera od uzytkownika trase lotu
 *
 *
 * \param[in] numer_drona - numer drona
 * \param[in] Lacze - Lacze do GNUplota
 * \retval true - gdy operacja powiedzie sie
 * \retval false - gdy operacja nie powiedzie sie
 */
  bool wybierz_drona(int numer_drona, PzG::LaczeDoGNUPlota &Lacze);
  /*!
 * \brief Zapisuje drona
 *
 *
 * \param[in] numer_drona - numer drona
 * \param[in] polozenie - polozenie startu drona
 * \retval true - gdy operacja powiedzie sie
 * \retval false - gdy operacja nie powiedzie sie
 */
  bool Zapis_drona(unsigned int numer_drona, vector3d &polozenie);
  /*!
 * \brief Uruchamia lot danego drona
 *
 * \param[in] numer_drona - numer drona
 * \param[in] kat - kat lotu
 * \param[in] odleglosc - dlugosc lotu
 * \param[in] Lacze - Lacze do GNUplota
 * \retval true - gdy operacja powiedzie sie
 * \retval false - gdy operacja nie powiedzie sie
 */
  bool Uzyj_drona( int numer_drona, double kat, unsigned int odleglosc, PzG::LaczeDoGNUPlota &Lacze);
  /*!
 * \brief Menu Programu
 *
 * \retval int numer drona
 * \retval  -1 - koniec programu
 */
  int  Menu(PzG::LaczeDoGNUPlota &Lacze);
  /*!
 * \brief Pozwala na dodanie przeszkody
 *
 *
 * \param[in] Lacze - Lacze do GNUplota
 */
  void Dodaj_Przeszkody(PzG::LaczeDoGNUPlota &Lacze);
  /*!
 * \brief Pozwala na usuniecie przeszkody
 *
 *
 * \param[in] Lacze - Lacze do GNUplota
 */
  void Usun_Przeszkody(PzG::LaczeDoGNUPlota &Lacze);

  std::list<std::shared_ptr<Obiekt>> DajPrzeszkody() {return Przeszkody;}
};