#pragma once

#include <iostream>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include <cassert>
#include <initializer_list>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <list>

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Vektor
 *
 */

/*!
 *  \brief Szablon klasy wektor.
 * 
 *  Jest on tablicą wspolrzednych.
 *
 */
template <int SIZE>
class Vector {

private:

    double wspolrzedne[SIZE];     //Tablica wektora

public:

    static unsigned int AktywneWektory;
    static unsigned int PowstaleWektory;

    Vector();

    ~Vector();

    Vector(double [SIZE]);

    Vector<SIZE> operator + (const Vector<SIZE> &v);

    Vector<SIZE> operator - (const Vector<SIZE> &v);

    Vector<SIZE> operator * (const double &tmp);

    Vector<SIZE> operator / (const double &tmp);

    const double &operator [] (int index) const;

    void zapeln(double argu[SIZE]);

    double modul();

    double &operator [] (int index);

  static int daj_aktywne() { return AktywneWektory; };
  static int daj_powstale() { return PowstaleWektory; };
  static void zwieksz_aktywne() { ++AktywneWektory; };
  static void zmniejsz_aktywne() { --AktywneWektory; };
  static void zwieksz_powstale() { ++PowstaleWektory; };

};
/*!
 * \brief Przeciazenie operatora <<                                                  
 *                                                                 
 *      \param[in] out  strumien wejsciowy                                             
 *      \param[in] tmp  wektor
 */
template <int SIZE>
std::ostream &operator << (std::ostream &out, Vector<SIZE> const &tmp);

template <int SIZE>
unsigned int Vector<SIZE>::AktywneWektory = 0;

template <int SIZE>
unsigned int Vector<SIZE>::PowstaleWektory = 0;
/*!
 * \brief Przeciazenie operatora >>
 *                                                                               
 *      \param[in] in strumien wyjsciowy                                              
 *      \param[in] tmp  wektor  
 */
template <int SIZE>
std::istream &operator >> (std::istream &in, Vector<SIZE> &tmp);

/*!
 | \brief Konstruktor klasy Vector.      
 */
template <int SIZE>
Vector<SIZE>::Vector() {
    zwieksz_aktywne();
    zwieksz_powstale();
    for (int i = 0; i < SIZE; ++i) {
        wspolrzedne[i] = 0;
    }
}
/*!
 | \brief Destruktor klasy Vector.         
*/
template <int SIZE>
Vector<SIZE>::~Vector() {
    zmniejsz_aktywne();
}


/******************************************************************************
    \brief Konstruktor klasy Vector.                              
                                                   
    \param[in] tmp - Jednowymiarowa tablica typu double.               
                                                            
    \return Vektor wypelniony wartosciami podanymi w argumencie.     
 */
template <int SIZE>
Vector<SIZE>::Vector(double tmp[SIZE]) {
    zwieksz_aktywne();
    zwieksz_powstale();
    for (int i = 0; i < SIZE; ++i) {
        wspolrzedne[i] = tmp[i];
    }
}




/*!
 * \brief Oblicza sume wektorow
 *                                                                  
 *     \param[in] this Wektor 
 *     \param[in] v Wektor                                                               
 *                                                                     
 *     \return Sume wektorow                                                                  
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator + (const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = wspolrzedne[i] += v[i];
    }
    return result;
}


/*!
 * \brief Oblicza roznice wektorow
 *                                                                  
 *     \param[in] this Wektor 
 *     \param[in] v Wektor                                                               
 *     \return Roznice wektorow                                                                  
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator - (const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = wspolrzedne[i] -= v[i];
    }
    return result;
}


/*!
 * \brief Oblicza iloczyn wektorow
 *                                                                  
 *     \param[in] this Wektor 
 *     \param[in] tmp Wektor                                                               
 *                                                                     
 *     \return iloczyn wektorow                                                                  
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator * (const double &tmp) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = wspolrzedne[i] *= tmp;
    }
    return result;
}


/*!
 * \brief Oblicza iloczyn wektorow
 *                                                                  
 *     \param[in] Wektor                                                              
 *     \param[in] tmp                                                               
 *     \return Iloczyn wektora przez stala                                                                 
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator / (const double &tmp) {
    Vector<SIZE> result;

    for (int i = 0; i < SIZE; ++i) {
        result[i] = wspolrzedne[i] / tmp;
    }

    return result;
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy jako stala.                   |
 */
template <int SIZE>
const double &Vector<SIZE>::operator [] (int index) const {
    
        assert(index >= 0 && index < SIZE);
    
    return wspolrzedne[index];
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy.                              |
 */
template <int SIZE>
double &Vector<SIZE>::operator[](int index) {
    return const_cast<double &>(const_cast<const Vector<SIZE> *>(this)->operator[](index));
}


template <int SIZE>
std::ostream &operator << (std::ostream &out, Vector<SIZE> const &tmp) {
  for (int index = 0; index < SIZE; index++)
  {
    out << tmp[index] << " ";
    if (index == SIZE)
    {
      out << tmp[index] << std::endl;
      return out;
    }
  }
  return out;
}


template <int SIZE>
std::istream &operator >> (std::istream &in, Vector<SIZE> &tmp) {
    tmp.zwieksz_aktywne();
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

/*!
 * \brief Zapelnia wektor tablica typu T
 *                                                                                                                                   
 */
template <int SIZE>
void Vector<SIZE>::zapeln(double argu[SIZE])
{
    for (unsigned int i = 0; i < SIZE; i++)
    {
       wspolrzedne[i]=argu[i]; 
    }
}
/*!
 * \brief Oblicza modul
 *                                                                  
 *     \param[in] Wektor                                                               
 *                                                                     
 *     \return modul                                                                  
 */
template <int SIZE>
double Vector<SIZE>::modul()
{   
    double tmp;
    for(unsigned int i=0;i<SIZE;i++)
    {
        tmp+=(wspolrzedne[i] * wspolrzedne[i]);
    }
    return std::sqrt(tmp);
}
