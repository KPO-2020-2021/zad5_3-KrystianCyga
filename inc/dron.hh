#pragma once

#include "../inc/graniastoslup.hh"
#include "../inc/prostopadloscian.hh"
#include "../inc/lacze_do_gnuplota.hh"
#include "../inc/Obiekt.hh"
#include "../inc/brylageo.hh"
#include <string>
#include <list>
#include <vector>
#include <iostream>

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Dron
 */

class Dron: public Obiekt
{
protected:
  vector3d PolozenieD;
  double Orientacja_drona;
  bool czy_aktywny = false;
  double promien=10;

  Prostopadloscian Korpus;
  graniastoslup Rotor[4];

public:
  /*!
 * \brief Buduje drona zapisujac wierzcholki odpowiednich figur
 * 
 *  \retval true - gdy operacja sie powiedzie
 *  \retval false - gdy operacja sie nie powiedzie
 */
  bool ZbudujDrona();

  Dron(): Obiekt(){};
  bool czy_kolioduje(std::list<std::shared_ptr<Obiekt>> &tmpPrzeszkody);
  void ustaw_wielkosc(vector3d &tmp);
  vector3d daj_wielkosc(int index){return wielkosc[index];};
  vector3d daj_polozenie() { return PolozenieD; };
  double daj_kat() { return Orientacja_drona; };
  void Ustaw_polozenie(vector3d VekTrans) { PolozenieD = VekTrans; };
  void Ustaw_kat(double kat) { Orientacja_drona = kat; };
  /*!
 * \brief Zapisuje trase przelotu drona do pliku a takze dodaje go do lacza gnuplota
 *
 *
 * \param[in] wysokosc - wysokosc lotu drona
 * \param[in] odleglosc - dlugosc lotu drona
 * \param[in] kat - kat lotu w stopniach 
 * \param[in] Lacze - Lacze do GNUplota
 * 
 * 
 *   \retval true - gdy operacja sie powiedzie
 *   \retval false - gdy operacja sie nie powiedzie
 */
  bool ZapiszTrase(int wysokosc, unsigned int odleglosc, double kat, PzG::LaczeDoGNUPlota &Lacze);
  /*!
 * \brief Przemieszcza i odpowiednio obraca drona
 *
 *
 * \param[in] numer_drona - nr drona
 *
 *  \retval true - gdy operacja sie powiedzie
 *  \retval false - gdy operacja sie nie powiedzie
 */
  bool owektor(unsigned int numer_drona);
  /*!
 * \brief Lot drona animacja
 *
 *
 * \param[in] kat - kat lotu w stopniach
 * \param[in] Wysokosc - wysokosc lotu
 * \param[in] odleglosc - dlugosc lotu
 * \param[in] numer_drona - numer drona
 * \param[in] Lacze - Lacze do GNUplota
 * 
 *  \retval true - gdy operacja sie powiedzie
 *  \retval false - gdy operacja sie nie powiedzie
 * 
 */
  bool LotDrona(double kat, int Wysokosc, int odleglosc, unsigned int numer_drona, PzG::LaczeDoGNUPlota &Lacze);
  /*!
  * \brief oblicza glugosc lotu
  *
  *
  * \param[in] kat - kat obrotu drona
  * \param[in] odleglosc - dlugosc lotu drona
  * 
  */
  void LotDoPrzodu(double kat, double odleglosc);
  /*!
  * \brief Poprawia koncowa pozycje drona
  * 
  * \param[in] VekTrans - pozycja drona przed lotem do przodu
  * \param[in] kat - aktualna wartość kąta obrotu drona
  * \param[in] odleglosc - dlugosc lotu
  * 
  */
  void Popraw_Pozycje(vector3d VekTrans, double kat, double odleglosc);
};