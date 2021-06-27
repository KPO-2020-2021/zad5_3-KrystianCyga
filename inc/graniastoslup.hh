#pragma once

#include "../inc/brylageo.hh"

/*!
 * \file
 * \brief Plik zawiera definicję klasy graniastoslupa
 */

class graniastoslup : public brylageo
{
public:
/*!
 * \brief Zapisuje wierzcholki rotora do listy
 *
 * Dokonuje niezbednej translacji, obrotu i skalowania.
 *
 * \param[in] Numer_Rotora - numer rotora
 * \param[in] Kat_Obrotu - kat obrotu rotora
 * \param[in] VekTrans - wektor translacji.
 *
 * \retval true - gdy operacja sie powiedzie
 * \retval false - gdy operacja sie nie powiedzie 
 */
  bool ZbudujRotor(unsigned int Numer_Rotora, double Kat_Obrotu, vector3d VekTrans);
  /*!
 * \brief Obraca rotory drona 
 *
 * Modyfikujepodany rotor obracajac go o zadany kat
 *
 * \param[in] Numer_Rotora - numer rotora
 * \param[in] Kat_Obrotu - kat obrotu rotora
 *
 * \retval true - gdy operacja sie powiedzie
 * \retval false - gdy operacja sie nie powiedzie 
 *
 */
  void ObrocRotor(unsigned int Numer_Rotora, double Kat_Obrotu);
};