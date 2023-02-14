#include <iostream>
#include <vector>
#include <complex>

#include "Compare.hpp"
#include "Polynomial.hpp"


void print_vector( std::vector<std::complex<double>> vec );

// Function definitions
int main() {
  std::cout.precision( 16 );

  Polynomial p{
    -0.209 - 0.614j, -0.955 + 0.600j,
    -0.145 + 0.685j, -0.175 + 0.993j,
    -0.227 + 0.389j,  0.546 + 0.461j,
    -0.787 - 0.207j,  0.890 - 0.578j,
     0.500 - 0.0905j, 0.473 - 0.340j
  };

  std::cout << p << std::endl;

  std::vector<std::complex<double>> s{
    -0.9852978835355780 + 0.98504720237219057375j,
    -0.9237720183259430 + 0.18023271286497825840j,
    -0.5960858052388558 - 1.7474774343724058837j,
    -0.4074346760674325 - 0.61884031232762062849j,
    -0.1814669556972790 + 1.0702581397314111283j,
     0.1577334896947644 - 0.78671798533279997987j,
     0.4466956464257077 - 0.35064425488461539668j,
     0.6345910143933426 + 0.98456634748762175629j,
     1.067394517079440  - 0.091262699328238475575j
  };

  std::cout << p << std::endl;
  // This shoul print '1' (true)
  std::cout << compare( p.roots(), s, 1e-10 ) << std::endl;  
  print_vector( p.roots() );
  print_vector( s );

  return 0;
}

// Print the entries of a std::vector of std::complex
// with each entry appearing on a separate line, and
// followed by an additional blank line.
void print_vector( std::vector<std::complex<double>> vec ) {
  for ( auto itr{ vec.begin() }; itr != vec.end(); ++itr ) {
    std::cout << *itr << std::endl;
  }

  std::cout << std::endl;
}