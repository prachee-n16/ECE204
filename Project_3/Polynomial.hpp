#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <string>

// Class declarations
class Polynomial;

class Polynomial {
  public:
    Polynomial( std::initializer_list<std::complex<double>> init );
   ~Polynomial();
    std::complex<double> operator()( std::complex<double> z ) const;
    std::vector<std::complex<double>> roots() const;
    std::string to_string() const;

  private:
    unsigned int          degree_;
    std::complex<double> *coeffs_;

    static std::complex<double> evaluate(
      std::complex<double> const *const coeffs,
      unsigned int                const  degree,
      std::complex<double>        const  z
    );

    static std::complex<double> find_root(
      std::complex<double> const *const coeffs,
      unsigned int                const degree
    );

    static std::complex<double> divide(
      std::complex<double>      *coeffs,
      unsigned int         const degree,
      std::complex<double> const z
    );
};

std::ostream &operator<<( std::ostream &out, Polynomial const &p );