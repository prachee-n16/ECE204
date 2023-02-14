#pragma once
#include <vector>
#include <complex>
#include <limits>
#include <cassert>

// YOU CAN IGNORE THIS FUNCTION
//  - It is implemented for you to use

// Function declarations
bool compare(
  std::vector<std::complex<double>> a1,
  std::vector<std::complex<double>> a2,
  double eps
);

// Compare two vectors by determining if each entry in
// the first appears in the second, by finding the
// entry in the second that has the smallest error,
// and then ensure the absolute error is sufficiently
// small.
bool compare( std::vector<std::complex<double>> a1,
              std::vector<std::complex<double>> a2,
              double eps ) {
  std::size_t const N{ a1.size() };
  double max_abs_err{ 0.0 };
  
  if ( a2.size() != N ) {
    return false;
  }

  for ( std::size_t i{ 0 }; i < N; ++i ) {
    double min_abs_err{ std::numeric_limits<double>::infinity() };
    std::size_t min_index{ N };

    for ( std::size_t j{ i }; j < N; ++j ) {
      if ( std::abs( a1[i] - a2[j] ) < min_abs_err ) {
        min_abs_err  = std::abs( (a1[i] - a2[j])/a2[j] );
        min_index = j;
      }
    }

    assert( min_index != N );

    // The error depends on the degree of the polynomial:
    //   - The more roots, the larger the error.
    if ( min_abs_err >= N*eps ) {
      return false;
    }

    max_abs_err = std::max( max_abs_err, min_abs_err );

    std::swap( a2[i], a2[min_index] );
  }

  std::cout << "Maximum absolute error: " << max_abs_err << "  ";
  return true;
}