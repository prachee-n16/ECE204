#include "tools.hpp"
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

unsigned int gaussian_elimination( double **array, unsigned int m, unsigned int n, double tolerance ) {
  unsigned int i{ 0 };
  unsigned int j{ 0 };

  while ( (i < m) && (j < n) ) {
    unsigned int k{ max_abs_index( array, i, j, m ) };

    if ( std::abs( array[k][j] ) < tolerance ) {
      // Set it to zero--not necessary
      array[k][j] = 0.0;
      ++j;
      continue;
    }

    if ( i != k ) {
      std::swap( array[i], array[k] );
    }

    for ( unsigned int k{ i + 1 }; k < m; ++k ) {
        double c{ array[k][j]/array[i][j] };
        assert( std::abs( c ) <= 1.0 );

        array[k][j] = 0.0;

        for ( unsigned int ell{ j + 1 }; ell < n; ++ell ) {
          array[k][ell] -= c*array[i][ell];
        }
    }

    ++i;
    ++j;
  }

  return i;
}

unsigned int max_abs_index( double **array,
                            unsigned int i,
                            unsigned int j,
                            unsigned int m ) {
  for ( unsigned int k{ i + 1 }; k < m; ++k ) {
    if ( std::abs( array[k][j] ) > std::abs( array[i][j] ) ) {
      i = k;
    }
  }

  return i;
}

unsigned int leading_zeros( double **array,
                            unsigned int i,
                            unsigned int n,
                            double tolerance ) {
  for ( unsigned int j{ 0 }; j < n; ++j ) {
    if ( std::abs( array[i][j] ) < tolerance ) {
      array[i][j] = 0.0;
    } else {
      return j;
    }
  }

  return n + 1;
}

void print_array( double    **array,
                 unsigned int m,
                 unsigned int n,
                 unsigned int bar ) {
  std::cout << std::endl;
  if ( (m == 0) || (n == 0) ) {
    // This is an odd case, but I'll leave it in just in case
    std::cout << "()" << std::endl;
  } else if ( m == 1 ) {
    // If there is only one row, this is easy:
    //  - just print the one row between parentheses ( ... )
    std::cout << "( " << array[0];

    for ( unsigned int j{1}; j < n; ++j ) {
      std::cout << " " << array[0][j]; 
    } 

    std::cout << " )" << std::endl;
  } else {
    // Otherwise this gets interesting...

    // First we must determine the largest width that any object will
    // be printed in each of the columns. We do this by using an 'ostringstream'
    // object and then converting the result to a string and measuring the length
    // of that stirng. Now we know the most number of characters one entry in
    // a column will use.
    //  - This appears to be repetative and time-consuming, but if you're
    //    printing something to the screen anyway, the miniscule time required
    //    is probably insignificant.

    // If your compiler does not allow run-time sized local arrays,
    // use the following:
    //   unsigned int *width = new unsigned int[n];
    // and uncomment the delete[] statement below.
    unsigned int width[n];

    for ( unsigned int j{ 0 }; j < n; ++j ) {
      std::ostringstream oss;
      oss << array[0][j];
      width[j] = oss.str().length();

      for ( unsigned int i{1}; i < m; ++i ) {
        std::ostringstream oss;
        oss << array[i][j];
        width[j] = std::max<unsigned int>( width[j], oss.str().length() );
      }
    }

    // Print the opening parenthesis for the row,
    // depending on which row we are on.
    for ( unsigned int i{ 0 }; i < m; ++i ) {
      if ( i == 0 ) {
        std::cout << " / ";
      } else if ( i == m - 1 ) {
        std::cout << " \\ ";
      } else if ( m == 3 ) {
        std::cout << "(  ";
      } else {
        std::cout << "|  ";
      }

      // Print the first entry in the row--we are guarenteed
      // each row has at least one entry.
      std::cout << std::setw( width[0] ) << array[i][0];

      // Print the remaining entries separated by spaces
      //  - Each item is to be printed using the maximum number
      //    of characters that will be used by any value in that 
      //    column. That is what the 'std::setw' does.
      //  - The 'w' in 'std::setw' is for 'width'.
      for ( unsigned int j{1}; j < n; ++j ) {
        if ( j == bar ) {
          std::cout << " |";
        }

        std::cout << " " << std::setw( width[j] ) << array[i][j];
      }

    // Print the closing parenthesis for the row,
    // depending on which row we are on.
      if ( i == 0 ) {
        std::cout << " \\ " << std::endl;
      } else if ( i == m - 1 ) {
        std::cout << " / " << std::endl;
      } else if ( m == 3 ) {
        std::cout << "  )" << std::endl;
      } else {
        std::cout << "  |" << std::endl;
      }

      // Uncomment this if you allocate 'width' with 'new'
      // above.
      // delete[] width;
    }
  }
}

// The array 'is_free_variable_array' stores whehter each column is
// associated with a free or constrained variable.
//
// If a column is associated with a free variable, the corresponding
// entry of the 'index_array' indicates the number of the free variable,
// starting at 0.
// Otherwise, the corresponding index indicates which row that constrained
// variable has a leading non-zero entry.

unsigned int analize_row_echelon_form( double      **array,
                                       bool         *is_free_variable_array,
                                       unsigned int *index_array,
                                       unsigned int m,
                                       unsigned int n,
                                       double       tolerance ) {
  unsigned int expected_leading_zeros{ 0 };
  unsigned int free_variables{ 0 };

  for ( unsigned int k{ 0 }; k < n; ++k ) {
    is_free_variable_array[k] = false;
  }

  unsigned int free_index{ 0 };
  unsigned int constrained_index{ 0 };

  for ( unsigned int i{ 0 }; i < m; ++i ) {
    unsigned int actual_leading_zeros{ leading_zeros( array, i, n, tolerance ) };

    if ( actual_leading_zeros == n ) {
      free_variables += actual_leading_zeros - expected_leading_zeros - 1;

      for ( unsigned int k{ expected_leading_zeros }; k < n; ++k ) {
        is_free_variable_array[k]  = true;
        index_array[k] = free_index;
        ++free_index;
      }

      break;
    }

    free_variables += actual_leading_zeros - expected_leading_zeros;

    for ( unsigned int k{ expected_leading_zeros };
          k < actual_leading_zeros; ++k ) {
      is_free_variable_array[k]  = true;
      index_array[k] = free_index;
      ++free_index;
    }

    index_array[actual_leading_zeros] = constrained_index;
    ++constrained_index;

    if ( i == (m - 1) ) {
      free_variables += n - actual_leading_zeros - 1;

      for ( unsigned int k{ actual_leading_zeros + 1 }; k < n; ++k ) {
        is_free_variable_array[k]  = true;
        index_array[k] = free_index;
        ++free_index;
      }
    } else {
      expected_leading_zeros = actual_leading_zeros + 1;
    }
  }

  return n - free_variables;
}