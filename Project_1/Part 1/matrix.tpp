#include <stdexcept>
#include <cmath>
#include <cassert>
#include "tools.hpp"

template <unsigned int m, unsigned int n>
matrix<m, n>::matrix( double constant ) {
  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] = constant;
    }
  }
}

template <unsigned int m, unsigned int n>
matrix<m, n>::matrix( std::initializer_list<std::initializer_list<double>> init ) {
  unsigned int i{ 0 };

  for ( std::initializer_list<std::initializer_list<double>>::iterator itr1{ init.begin() };
        (itr1 != init.end()) && (i < m);
        ++itr1, ++i
  ) {
    unsigned int j{ 0 };

    for ( std::initializer_list<double>::iterator itr2{ itr1->begin() };
          (itr2 != itr1->end()) && (j < n);
          ++itr2, ++j
    ) {
      entries_[i][j] = *itr2;
    }

    for ( ; j < n; ++j ) {
      entries_[i][j] = 0.0;
    }
  }

  for ( ; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] = 0.0;
    }
  }
}

template <unsigned int m, unsigned int n>
matrix<m, n>::matrix( std::initializer_list<vec<m>> init ) {
  unsigned int j{ 0 };

  for ( typename std::initializer_list<vec<m>>::iterator itr{ init.begin() };
        (itr != init.end()) && (j < n);
        ++itr, ++j
  ) {
    for ( unsigned int i{ 0 }; i < m; ++i ) {
      entries_[i][j] = (*itr)( i );
    }
  }

  for ( ; j < n; ++j ) {
    for ( unsigned int i{ 0 }; i < m; ++i ) {
      entries_[i][j] = 0.0;
    }
  }
}

// Construct a diagonal matrix with the entries of
// the initializer list on the diagonal.
template <unsigned int m, unsigned int n>
matrix<m, n>::matrix( std::initializer_list<double> init ) {
  unsigned int i{ 0 };

  for ( std::initializer_list<double>::iterator itr{ init.begin() };
        (itr != init.end()) && (i < std::min( m, n ));
        ++itr, ++i
  ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] = 0.0;
    }

    entries_[i][i] = *itr;
  }

  for ( ; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] = 0.0;
    }
  }
}

template <unsigned int m, unsigned int n>
double &matrix<m, n>::operator()( unsigned int i, unsigned int j ) {
  if ( (i >= m) || (j >= n) ) {
    throw_matrix_exception( i, j );
  }

  return entries_[i][j];
}

template <unsigned int m, unsigned int n>
double const &matrix<m, n>::operator()( unsigned int i, unsigned int j ) const {
  if ( (i >= m) || (j >= n) ) {
    throw_matrix_exception( i, j );
  }

  return entries_[i][j];
}

template <unsigned int m, unsigned int n>
void matrix<m, n>::throw_matrix_exception(
  unsigned int i, unsigned int j
) const {
    std::string article{ "a " };

    unsigned int em{ m };

    while ( em >= 1000 ) {
      em /= 1000;
    }

    if ( (em == 8) || (em == 18)
          || ((em >= 80) && (em <= 89))
          || ((em >= 800) && (em <= 899))
    ) {
      article = "an ";
    }

    throw std::out_of_range{
      "The index ("
      + std::to_string( i )
      + ", "
      + std::to_string( j )
      + ") is beyond the dimensions of "
      + article
      + std::to_string( m )
      + " x "
      + std::to_string( n )
      + " matrix" };
}

/***************************************************************
 * Scalar multiplication
 ***************************************************************/

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator*( double s ) const {
  matrix<m, n> product;

  for ( unsigned int i{0}; i < m; ++i ) {
    for ( unsigned int j{0}; i < n; ++j ) {
      product.entries_[i][j] = s*entries_[i][j];
    }
  }

  return product;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator*=( double s ) {
  for ( unsigned int i{0}; i < m; ++i ) {
    for ( unsigned int j{0}; i < n; ++j ) {
      entries_[i][j] *= s;
    }
  }

  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator/( double s ) const {
  matrix<m, n> product;

  for ( unsigned int i{0}; i < m; ++i ) {
    for ( unsigned int j{0}; i < n; ++j ) {
      product.entries_[i][j] = entries_[i][j]/s;
    }
  }

  return product;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator/=( double s ) {
  for ( unsigned int i{0}; i < m; ++i ) {
    for ( unsigned int j{0}; i < n; ++j ) {
      entries_[i][j] /= s;
    }
  }

  return *this;
}

/***************************************************************
 * Matrix addition
 ***************************************************************/

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator+( matrix const &A ) const {
  matrix<m, n> sum;

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      sum.entries_[i][j] = entries_[i][j] + A.entries_[i][j];
    }
  }

  return sum;
}

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator-( matrix const &A ) const {
  matrix<m, n> sum;

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      sum.entries_[i][j] = entries_[i][j] - A.entries_[i][j];
    }
  }

  return sum;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator+=( matrix const &A ) {
  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] += A.entries_[i][j];
    }
  }

  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator-=( matrix const &A ) {
  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      entries_[i][j] -= A.entries_[i][j];
    }
  }

  return *this;
}

/***************************************************************
 * Scalar addition
 ***************************************************************/

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator+( double s ) const {
  matrix<m, n> sum{ *this };

  for ( int k{ 0 }; k < std::min( m, n ); ++k ) {
    sum.entries_[k][k] += s;
  }

  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator+=( double s ) {
  for ( int k{ 0 }; k < std::min( m, n ); ++k ) {
    entries_[k][k] += s;
  }

  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator-( double s ) const {
  matrix<m, n> sum{ *this };

  for ( int k{ 0 }; k < std::min( m, n ); ++k ) {
    sum.entries_[k][k] -= s;
  }

  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> &matrix<m, n>::operator-=( double s ) {
  for ( int k{ 0 }; k < std::min( m, n ); ++k ) {
    entries_[k][k] -= s;
  }

  return *this;
}

/***************************************************************
 * Unary operators
 ***************************************************************/

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator +() const {
  return *this;
}

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator -() const {
  return *this * (-1.0);
}


/*************************
 * Matrix-vector product *
 *************************/
template <unsigned int m, unsigned int n>
vec<m> matrix<m, n>::operator*( vec<n> const &v ) const {
  vec<m> product{};

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      product( i ) += entries_[i][j]*v( j );
    }
  }

  return product;
}

template <unsigned int m, unsigned int n>
std::string matrix<m, n>::to_string() const {
  if ( (m == 0) || (n == 0) ) {
    return std::string{ "[]" };
  } else {
    std::string str{ "[" + std::to_string( entries_[0][0] ) };

    for ( unsigned int j{ 1 }; j < n; ++j ) {
      str += " " + std::to_string( entries_[0][j] );
    }


    for ( unsigned int i{ 1 }; i < m; ++i ) {
      str += "; " + std::to_string( entries_[i][0] );

      for ( unsigned int j{ 1 }; j < n; ++j ) {
        str += " " + std::to_string( entries_[i][j] );
      }
    }

    return str + "]";
  }
}

template <unsigned int m, unsigned int n>
matrix<m, n> matrix<m, n>::operator*=( matrix<n, n> const &A ) const {
  for ( unsigned int i{ 0 }; i < m; ++i ) {
    double result[n];

    for ( unsigned int k{ 0 }; k < n; ++k ) {
      result[k] = 0.0;

      for ( unsigned int j{ 0 }; j < n; ++j ) {
        result[k] += entries_[i][j]*A.entries_[j][k]; 
      }
    }

    for ( unsigned int k{ 0 }; k < n; ++k ) {
      entries_[i][k] = result[k];
    }
  }

  return *this;
}

template <unsigned int ell, unsigned int m, unsigned int n>
matrix<ell, n> operator*( matrix<ell, m> const &B, matrix<m, n> const &A ) {
  matrix<ell, n> result{ 0.0 };

  for ( unsigned int i{ 0 }; i < ell; ++i ) {
    for ( unsigned int k{ 0 }; k < n; ++k ) {
      for ( unsigned int j{ 0 }; j < m; ++j ) {
        result.entries_[i][k] += B.entries_[i][j]*A.entries_[j][k]; 
      }
    }
  }

  return result;
}

//                                    *
// The adjoint is usually written as A  and as the transpose is
// the manifestation of the adjoint for finite-dimensional real
// matrices, it makes sense to override the *A operator to return
// the transpose of A.

template <unsigned int m, unsigned int n>
matrix<n, m> matrix<m, n>::operator*() const {
  matrix<n, m> adjoint;

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      adjoint(j, i) = (*this)(i, j);
      //adjoint.entries_[j][i] = entries_[i][j];
    }
  }

  return adjoint;
}

// You can also call the transpose function.

template <unsigned int m, unsigned int n>
matrix<n, m> transpose( matrix<m, n> const &A ) {
  return *A;
}

template <unsigned int m, unsigned int n>
std::ostream &operator<<( std::ostream &out, matrix<m, n> const &rhs ) {
  return out << rhs.to_string();
}

// If there are no solutions, then an empty std::vector is returned.
// If there is exactly one solution,
//    then a std::vector with size '1' is returned, and
//    that one entry is the unique solution.
// If there are infinitely many solutions,
//    and there are 'N' free variables (the dimension of the null
//    space is 'N'), then a std::vector with size 'N + 1' is 
//    returned, entry '0' is a particular solution, and
//    entries '1' through 'N' are a basis for the null space;
//    thus, the first vector plus any linear combination of 
//    the subsequent vectors are all solutions.
template <unsigned int m, unsigned int n>
std::vector<vec<n>> matrix<m, n>::solve( vec<m> const &v,
                                         double tolerance ) const {
  // Create the augmented matrix
  double memory[m*(n + 1)];
  double *Aaug[m];

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    Aaug[i] = memory + i*(n + 1);

    for ( unsigned int j{ 0 }; j < n; ++j ) {
      Aaug[i][j] = entries_[i][j];
    }

    Aaug[i][n] = v( i );
  }

  gaussian_elimination( Aaug, m, n + 1, tolerance );

  bool         no_solutions{ false };
  bool         free_list[n + 1];
  unsigned int index_list[n + 1];

  for ( unsigned int k{ 0 }; k < n; ++k ) {
    free_list[k] = false;
    index_list[k] = 0;
  }

  unsigned int rank{ analize_row_echelon_form( Aaug, free_list, index_list, m, n + 1, tolerance ) };

  if ( !free_list[n] ) {
    // There are no solutions
    return std::vector<vec<n>>( 0 );
  } else if ( rank == n ) {
    std::vector<vec<n>> u( 1 );

    for ( unsigned int i{ m - 1 }; i < m; --i ) {
      u[0]( i ) = Aaug[i][n];

      for ( unsigned int j{ i + 1 }; j < n; ++j ) {
        u[0]( i ) -= Aaug[i][j]*u[0]( j );
      }

      u[0]( i ) /= Aaug[i][i];
    }

    return u;
  } else {
    std::vector<vec<n>> u( n - rank + 1 );
    
    for ( unsigned int j{ n - 1 }; j < n; --j ) {
      if ( free_list[j] ) {
        u[index_list[j] + 1]( j ) = 1.0;
      } else {
        u[0]( j ) = Aaug[index_list[j]][n];

        for ( unsigned int k{ j + 1 }; k < n; ++k ) {
          if ( free_list[k] ) {
            u[index_list[k] + 1]( j )
                -= Aaug[index_list[j]][k]/Aaug[index_list[j]][j];
          } else {
            u[0]( j ) -= Aaug[index_list[j]][k]*u[0]( k );

            for ( unsigned int ell{ k + 1 }; ell < n; ++ell ) {
              if ( free_list[ell] ) {
                u[index_list[ell] + 1]( j ) 
                  -=  Aaug[index_list[j]][k]*u[index_list[ell] + 1]( k )
                    / Aaug[index_list[j]][j];
              }
            }
          }
        }

        u[0]( j ) /= Aaug[index_list[j]][j];
      }
    }

    return u;
  }
}

template <unsigned int m, unsigned int n>
unsigned int matrix<m, n>::rank( double tolerance ) const {
  // Create a copy to modify
  double memory[m*n];
  double *A[m];

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    A[i] = memory + i*n;

    for ( unsigned int j{ 0 }; j < n; ++j ) {
      A[i][j] = entries_[i][j];
    }
  }

  return gaussian_elimination( A, n, n, tolerance );
}

template <unsigned int m, unsigned int n>
double matrix<m, n>::det( double tolerance ) const {
  if ( m != n ) {
    return 0.0;
  }

  // Create a copy to modify
  double memory[n*n];
  double *A[n];

  for ( unsigned int i{ 0 }; i < n; ++i ) {
    A[i] = memory + i*n;

    for ( unsigned int j{ 0 }; j < n; ++j ) {
      A[i][j] = entries_[i][j];
    }
  }

  gaussian_elimination( A, n, n, tolerance );

  double product{ 1.0 };

  for ( unsigned int k{ 0 }; k < n; ++k ) {
    product *= A[k][k];
  }

  return product;
}

template <unsigned int m, unsigned int n>
double matrix<m, n>::tr() const {
  double sum{ 0.0 };

  for ( unsigned int k{ 0 }; k < std::min( m, n ); ++k ) {
    sum += entries_[k][k];
  }

  return sum;
}

template <unsigned int m, unsigned int n>
matrix<n, m> matrix<m, n>::inv( double tolerance ) const {
  if ( m != n ) {
    // Need to calculate the Moore-Penrose pseudo-inverse
    return matrix<n, m>{};
  }

  // Create the matrix ( A | I ) where we will perform
  //                          n
  // row operations to convert the matrix to the form
  //            -1
  //    ( I  | A  ) and then extract the inverse.
  //       n

  double memory[n*2*n];
  double *A[n];

  for ( unsigned int i{ 0 }; i < n; ++i ) {
    A[i] = memory + i*2*n;

    for ( unsigned int j{ 0 }; j < n; ++j ) {
      A[i][j] = entries_[i][j];
      A[i][n + j] = 0.0;
    }

    A[i][n + i] = 1.0;
  }

  // First apply Gaussian elimination 
  gaussian_elimination( A, n, 2*n, tolerance );

  if ( A[n - 1][n - 1] == 0.0 ) {
    std::clog << "The matrix is not invertible..." << std::endl;
  }

  // The diagonal entries of the left-hand matrix are 
  // still not 1, so divide Row i by entry (i,i)

  for ( unsigned int i{ 0 }; i < n; ++i ) {
    std::clog << "Multiplying Row " << i
              << " by " << 1.0/A[i][i] << std::endl;
    for ( unsigned int j{ i + 1 }; j < 2*n; ++j ) {
      A[i][j] /= A[i][i];
    }

    A[i][i] = 1.0;   // Technically not necessary
  }

  // The upper triangular component of the left-hand
  // matrix is still not all zeros, so perform row
  // operations to eliminate these.

  for ( unsigned int j{ n - 1 }; j > 0; --j ) {
    for ( unsigned int i{ 0 }; i < j; ++i ) {
      std::clog << "Adding " << (-A[i][j]/A[i][i]) 
                << " times Row " << j << " onto Row "
                << i << std::endl;

      for ( unsigned int k{ j + 1 }; k < 2*n; ++k ) {
        A[i][k] -= A[i][j]/A[i][i] * A[j][k];
      }

      A[i][j] = 0.0;
    }
  }

  // Create an n x n matrix that will store the entries
  // of the inverse of the matrix and copy them over
  matrix<n, n> InvA{};

  for ( unsigned int i{ 0 }; i < n; ++i ) {
    for ( unsigned int j{ 0 }; j < n; ++j ) {
      InvA.entries_[i][j] = A[i][n + j];
    }
  }

  return InvA;
}

template <unsigned int m, unsigned int n>
unsigned int rank( matrix<m, n> const &A ) {
  return A.rank();
}

template <unsigned int m, unsigned int n>
double det( matrix<m, n> const & A ) {
  return A.det();
}

template <unsigned int m, unsigned int n>
double tr( matrix<m, n> const & A ) {
  return A.tr();
}

template <unsigned int m, unsigned int n>
matrix<n, m> inv( matrix<m, n> const & A ) {
  return A.inv();
}