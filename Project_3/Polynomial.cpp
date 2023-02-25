#include <cassert>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "Polynomial.hpp"

// Create a polynomial of degree 'N - 1' where 'N' is
// the number of objects in the initializer list.
//
// The 'N' coefficients are stored in an array of that
// capacity
//  - The capacity of the array must be at least one
Polynomial::Polynomial(
  std::initializer_list<std::complex<double>> init
):
degree_{ (init.size() == 0) ? 0 : init.size() - 1 },
coeffs_{ new std::complex<double>[degree_ + 1] } {
  // If the user creates a polynomial with no arguments,
  // we will create the zero polynomial.
  if ( init.size() == 0 ) {
    coeffs_[0] = 0.0;

  // Otherwise, the first argument is the constant
  // coefficient, the second is the coefficient of
  // 'x', and so on, until the last is the
  //                 N-1
  // coefficient of x   .
  } else {
    std::size_t k{ 0 };

    for ( auto itr{ init.begin() };
      itr != init.end();
      ++k, ++itr
    ) {
      coeffs_[k] = *itr;
      std::cout << coeffs_[k] << std::endl;
    }

    if ( (degree_ >= 1) && (coeffs_[degree_] == 0.0) ) {
      delete[] coeffs_;
      coeffs_ = nullptr;
      throw std::invalid_argument{ "The leading coefficient must be non-zero" };
    }
  }
}

Polynomial::~Polynomial() {
  delete[] coeffs_;
  coeffs_ = nullptr;
  degree_ = 0;
}

std::complex<double> Polynomial::operator()( std::complex<double> z ) const {
  return evaluate( coeffs_, degree_, z );
}

// This function is writen for you, but you can change it if
// you wish. It is only necessary that it return a std::vector
// instance with the roots. It must be 'const'.
std::vector<std::complex<double>> Polynomial::roots() const {
  // The vector of roots to be returned by this function
  //   - The argument is the number of entries in the std::vector
  std::vector<std::complex<double>> roots_vec( degree_ );

  // An array of the coefficients
  //  - This will be manipulated by you as you find the roots
  std::complex<double> coeffs[degree_ + 1];

  // The polynomial may have a leading coefficient that is not
  // equal to '1'. It will be easier if the leading coefficient
  // is '1', so the coeffs array will store the coefficients 
  // divided by the leadning coefficient, which makes the
  // leading coefficient '1'.

  assert( std::abs( coeffs_[degree_] ) > 1e-16 );
  coeffs[degree_] = 1.0;
  
  for ( unsigned int k{ 0 }; k < degree_; ++k ) {
    coeffs[k] = coeffs_[k]/coeffs_[degree_];
  }

  // In general, methods like Newton's method and the secant
  // may require a complex initial value. If you implement
  // Muller's method, you do not need this special case and
  // your algorithm can use either real or complex initial 
  // values. You could, if you wanted, always use a complex
  // initial value; but this has the nasty side-effect that
  // if you have a polynomial with real coefficients, then the
  // roots, if they are real, will be approximated with values
  // like 1.414213562373095 + 0.3957188605e-53j

  for ( unsigned int k{ 0 }; k < degree_; ++k ) {
    roots_vec[k] = find_root( coeffs, degree_ - k );
    divide( coeffs, degree_ - k, roots_vec[k] );
  }

  return roots_vec;
}

// Evaluate the polynomial at the point 'x'
std::complex<double> Polynomial::evaluate(
  std::complex<double> const *const coeffs,
  unsigned int         const  degree,
  std::complex<double> const  z
) {
  std::complex<double> result = coeffs[degree];
  
  for (int i = degree - 1; i >= 0; i--) { 
    result = coeffs[i] + (z * result);
  }

  return result;
}

// Given the polynomial of degree 'degree', the coefficients
// of which are given in the array 'coeffs', find an approximation
// of a root.
// If your algorithm requires you to start with a non-real 
// complex root, you can generate use the following:
//  std::complex<double> x0 {
//      (rand() + 1.0)/(RAND_MAX + 2.0)*20.0 - 10.0,
//      (rand() + 1.0)/(RAND_MAX + 2.0)*20.0 - 10.0
//  };
//

std::complex<double> Polynomial::find_root(
  std::complex<double> const *const coeffs,
  unsigned int                const degree
) {
  // Stores next approximation
  std::complex<double> x_k{
    (rand() + 1.0)/(RAND_MAX + 2.0)*20.0 - 10.0,
    (rand() + 1.0)/(RAND_MAX + 2.0)*20.0 - 10.0
  };
  
  // Stores current approximation
  //std::complex<double> x_k{0};

  double eps_step = 1e-10;

  // Calculate the derivative coeff array
  std::complex<double> der_coeffs[degree];
  
  for (int i = 1; i <= degree; i++) {
    der_coeffs[i - 1] = coeffs[i] * double(i);
  };

  std::complex<double> f_x = evaluate(coeffs, degree, x_k);
  std::complex<double> der_f_x  = evaluate(der_coeffs, degree-1, x_k);
  std::complex<double> x_k_next = x_k - ((f_x)/(der_f_x));

//(std::abs(std::real(x_k) - std::real(x_k_next)) > eps_step) && (std::abs(std::imag(x_k) - std::imag(x_k_next)) > eps_step)
  while (std::abs(x_k - x_k_next) > eps_step) {
    
    x_k = x_k_next;

    std::complex<double> f_x = evaluate(coeffs, degree, x_k);
    std::complex<double> der_f_x  = evaluate(der_coeffs, degree-1, x_k);

    x_k_next = x_k - ((f_x)/(der_f_x));
  }

  return x_k_next;
}

// Polynomial division
//
// In place, update the entries in the coefficient array to
// give the quotient when the polynomial defined by
//                                                    degree
//    coeffs[0] + coeffs[1] x + ... + coeffs[degree] x
// is divided by x - r

std::complex<double> Polynomial::divide(
  std::complex<double>      *coeffs,
  unsigned int         const degree,
  std::complex<double> const r
) {

  //stores the degree of quotient
  int quotient_degree = 0; 

  //stores coefficients for quotient
  std::complex<double> *res = new std::complex<double>[degree]{0.0};

  //if degree = 0 - polynomial is constant
  if(degree == 0){
    quotient_degree = 0;
    //return the first element in the coeffs array
    return coeffs[0];
  } else {
    //if degree is not 0 - perform division
    quotient_degree = degree - 1;

    //storing the remaineder result for division
    std::complex<double> rem_result{coeffs[degree]};

    for (int k{quotient_degree}; k >= 0; k--){
      res[k] = rem_result;
      rem_result = coeffs[k] + (rem_result * r);

      //since rem_result stores the value of the coeffs array
      //coeffs array at index k is set to the value of res array at index k
      coeffs[k] = res[k];
    }

    return rem_result;

  }

  // for (int i = 0; i < degree; i++) { 
  //   if (i == 0) {
  //     res[degree - 1 - i] = coeffs[degree - i];
  //   } 
  //   else {
  //     res[degree - i - 1] = coeffs[degree - i] + r*res[degree - i];
  //   }
  // }

  // std::complex<double> result = res[0];
  // delete[] res;
  // return result;
 
}

std::string to_string_term( unsigned int n ) {
  if ( n == 0 ) {
    return "";
  } else if ( n == 1 ) {
    return "z";
  } else {
    return "z^" + std::to_string( n );
  }
}

std::string to_string_complex( std::complex<double> z, bool is_leading, unsigned int n ) {
  if ( z.imag() == 0.0 ) {
    // The coefficient is real (possibly zero)
    if ( z.real() == 0.0 ) {
      if ( is_leading && (n == 0) ) {
        return "0";
      } else {
        return "";
      }
    } else {
      if ( is_leading ) {
        return std::to_string( z.real() ) + to_string_term( n );
      } else {
        if ( z.real() < 0.0 ) {
          return " - " + std::to_string( -z.real() ) + to_string_term( n );
        } else {
          return " + " + std::to_string(  z.real() ) + to_string_term( n );
        }
      }
    }
  } else if ( z.real() == 0.0 ) {
    // The coefficient is a non-zero imaginary number
    if ( is_leading ) {
      return std::to_string( z.imag() ) + "j" + to_string_term( n );
    } else {
      if ( z.imag() < 0.0 ) {
        return " - " + std::to_string( -z.imag() ) + "j" + to_string_term( n );
      } else {
        return " + " + std::to_string(  z.imag() ) + "j" + to_string_term( n );
      }
    }
  } else {
    // Both real and imaginary parts are non-zero
    if ( is_leading && (n == 0) ) {
      if ( z.imag() < 0.0 ) {
        return std::to_string( z.real() ) + " - " + std::to_string( -z.imag() ) + "j";
      } else {
        return std::to_string( z.real() ) + " + " + std::to_string(  z.imag() ) + "j";
      }
    } else {
      bool is_negative{ false };
      std::string out{ "" };

      if ( z.real() < 0.0 ) {
        z = -z;
        is_negative = true;
      }

      if ( z.imag() < 0.0 ) {
        out = out + std::to_string( z.real() ) + " - " + std::to_string( -z.imag() ) + "j";
      } else {
        out = out + std::to_string( z.real() ) + " + " + std::to_string(  z.imag() ) + "j";
      }

      if ( is_negative ) {
        if ( is_leading ) {
          out = "-(" + out + ")";
        } else {
          out = " - (" + out + ")";
        }
      } else if ( n > 0 ) {
        out = "(" + out + ")";

        if ( !is_leading ) {
          out = " + " + out;
        }
      } else {
        out = " + " + out;
      }

      return out + to_string_term( n );
    }
  }
}

std::string Polynomial::to_string() const {
  std::string out{ to_string_complex( coeffs_[degree_], true, degree_ ) };

  for ( unsigned int n{ degree_ - 1 }; n < degree_; --n ) {
    out += to_string_complex( coeffs_[n], false, n );
  }

  return out;
}

std::ostream &operator<<( std::ostream &out, Polynomial const &p ) {
  return out << p.to_string();  
}