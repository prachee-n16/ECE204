#include <stdexcept>
#include <cmath>
#include <cassert>

template <unsigned int n>
vec<n>::vec( double constant ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] = constant;
  }
}

template <unsigned int n>
vec<n>::vec( std::initializer_list<double> init ) {
  unsigned int k{0};

  for ( std::initializer_list<double>::iterator itr{ init.begin() };
        (itr != init.end()) && (k < n);
        ++itr, ++k
  ) {
    entries_[k] = *itr;
  }

  for ( ; k < n; ++k ) {
      entries_[k] = 0.0;
  }
}

template <unsigned int n>
double &vec<n>::operator()( unsigned int k ) {
  if ( k >= n ) {
    throw_vector_exception( k );
  }

  return entries_[k];
}

template <unsigned int n>
double const &vec<n>::operator()( unsigned int k ) const {
  if ( k >= n ) {
    throw_vector_exception( k );
  }

  return entries_[k];
}

template <unsigned int n>
void vec<n>::throw_vector_exception( unsigned int k ) const {
    std::string article{ "a " };

    unsigned int en{ n };

    while ( en >= 1000 ) {
      en /= 1000;
    }

    if ( (en == 8) || (en == 18)
          || ((en >= 80)  && (en <= 89))
          || ((en >= 800) && (en <= 899))
    ) {
      article = "an ";
    }

    throw std::out_of_range{
      "The index "
      + std::to_string( k )
      + " is beyond the dimension of "
      + article
      + std::to_string( n )
      + "-dimensional vector" };
}

template <unsigned int n>
double vec<n>::norm() const {
  double sum{ 0.0 };

  for ( unsigned int k{0}; k < n; ++k ) {
    sum += entries_[k]*entries_[k];
  }

  return std::sqrt( sum );
}

template <unsigned int n>
double vec<n>::norm( NORM flavor ) const {
  switch ( flavor ) {
    case infinity: {
      double max{ 0.0 };

      for ( unsigned int k{0}; k < n; ++k ) {
        if ( std::abs( entries_[k] ) > max ) {
          max = std::abs( entries_[k] );
        }
      }

      return max;
    } case one: {
      double sum{ 0.0 };

      for ( unsigned int k{0}; k < n; ++k ) {
        sum += std::abs( entries_[k] );
      }

      return sum;
    } case two: {
      double sum{ 0.0 };

      for ( unsigned int k{0}; k < n; ++k ) {
        sum += entries_[k]*entries_[k];
      }

      return std::sqrt( sum );
    }
  }

  assert( false );
}

/***************************************************************
 * Scalar multiplication
 ***************************************************************/

template <unsigned int n>
vec<n> vec<n>::operator*( double s ) const {
  vec<n> product;

  for ( unsigned int k{0}; k < n; ++k ) {
    product.entries_[k] = s*entries_[k];
  }

  return product;
}

template <unsigned int n>
vec<n> &vec<n>::operator*=( double s ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] *= s;
  }

  return *this;
}

template <unsigned int n>
vec<n> vec<n>::operator/( double s ) const {
  vec<n> product;

  for ( unsigned int k{0}; k < n; ++k ) {
    product.entries_[k] = entries_[k]/s;
  }

  return product;
}

template <unsigned int n>
vec<n> &vec<n>::operator/=( double s ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] /= s;
  }

  return *this;
}

/***************************************************************
 * Vector addition
 ***************************************************************/

template <unsigned int n>
vec<n> vec<n>::operator+( vec const &v ) const {
  vec<n> sum;

  for ( unsigned int k{0}; k < n; ++k ) {
    sum.entries_[k] = entries_[k] + v.entries_[k];
  }

  return sum;
}

template <unsigned int n>
vec<n> &vec<n>::operator+=( vec const &v ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] += v.entries_[k];
  }

  return *this;
}

template <unsigned int n>
vec<n> vec<n>::operator-( vec const &v ) const {
  vec<n> sum;

  for ( unsigned int k{0}; k < n; ++k ) {
    sum.entries_[k] = entries_[k] - v.entries_[k];
  }

  return sum;
}

template <unsigned int n>
vec<n> &vec<n>::operator-=( vec const &v ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] -= v.entries_[k];
  }

  return *this;
}

/***************************************************************
 * Scalar addition
 ***************************************************************/

template <unsigned int n>
vec<n> vec<n>::operator+( double s ) const {
  vec<n> sum;

  for ( unsigned int k{0}; k < n; ++k ) {
    sum.entries_[k] = entries_[k] + s;
  }

  return sum;
}

template <unsigned int n>
vec<n> &vec<n>::operator+=( double s ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] += s;
  }

  return *this;
}

template <unsigned int n>
vec<n> vec<n>::operator-( double s ) const {
  vec<n> sum;

  for ( unsigned int k{0}; k < n; ++k ) {
    sum.entries_[k] = entries_[k] - s;
  }

  return sum;
}

template <unsigned int n>
vec<n> &vec<n>::operator-=( double s ) {
  for ( unsigned int k{0}; k < n; ++k ) {
    entries_[k] -= s;
  }

  return *this;
}

/***************************************************************
 * Unary operators
 ***************************************************************/

template <unsigned int n>
vec<n> vec<n>::operator +() const {
  return *this;
}

template <unsigned int n>
vec<n> vec<n>::operator -() const {
  return *this * (-1.0);
}

/***************************************************************
 * Inner product
 ***************************************************************/

template <unsigned int n>
double vec<n>::operator *( vec const &v ) const {
  double sum{ 0 };

  for ( unsigned int k{ 0 }; k < n; ++k ) {
    sum += entries_[k]*v.entries_[k];
  }

  return sum;
}

/***************************************************************
 * Project this vector onto the vector 'v'
 ***************************************************************/
template <unsigned int n>
vec<n> &vec<n>::project( vec const &v ) {
  *this -= *this*v;

  return *this;
}

template <unsigned int n>
vec<n> operator *( double s, vec<n> const &v ) {
  return v*s;
}

template <unsigned int n>
vec<n> operator /( double s, vec<n> const &v ) {
  vec<n> product{ 0.0 };

  for ( unsigned int k{0}; k < n; ++k ) {
    product( k ) = 1.0/product( k );
  }

  return product;
}

template <unsigned int n>
std::string vec<n>::to_string() const {
  if ( n == 0 ) {
    return std::string{ "[]" };
  } else {
    std::string str{ "[" + std::to_string( entries_[0] ) };

    for ( unsigned int k{1}; k < n; ++k ) {
      str += " " + std::to_string( entries_[k] );
    }

    return str + "]'";
  }
}

template <unsigned int n>
double norm( vec<n> const &v ) {
  return v.norm();
}

template <unsigned int n>
std::ostream &operator<<( std::ostream &out, vec<n> const &rhs ) {
  return out << rhs.to_string();
}