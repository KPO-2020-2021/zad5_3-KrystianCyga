#pragma once

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "../inc/brylageo.hh"

/*!
 * \file
 * \brief Plik zawiera definicję klasy Prostopadloscian
 */
class Prostopadloscian : public brylageo
{

public:
  /*!
  * \brief Buduje korpus drona zapisujac jego wierzcholki na liscie
  *
  * Dokonuje również potrzebnych transformacji i skalowania
  *
  * \param[in] Kat_Obrotu - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
  * \param[in] VekTrans - wektor translacji.
  *
  * \retval true - gdy operacja sie powiedzie
   * \retval false - gdy operacja sie nie powiedzie
   */
  bool ZbudujKorpus(double Kat_Obrotu, vector3d VekTrans);
};