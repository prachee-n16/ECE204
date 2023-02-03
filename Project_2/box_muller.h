#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/********************************************************
 * This implementation of the Box-Muller method uses
 * static variables to minimize the number of calls
 * to the various functions.
 *
 *    Given two random variables u1 and u2 chosen
 *    from the interval (0, 1], we first calculate:
 *                  _____________
 *           c <- \/ -2 ln( u1 )
 *
 *    Next, there are two independent random normal
 *    numbers by calculating both
 *           c cos( 2 pi u2 )
 *           c sin( 2 pi u2 )
 *
 * As this function only returns one random normal,
 * we will use static variables to allow a quick
 * return of the second:
 *  - There is a static (shared) Boolean variable 'parity'
 *    that is initially true.
 *
 *  - With each call, 'parity' is switched between 'true'
 *    and 'false'.
 *   
 *  - If parity is now 'false' (the first, third, and all
 *    subsequent odd calls), then we calculate both
 *           c cos( 2 pi u2 )
 *           c sin( 2 pi u2 )
 *    We return the first and store the second in a 
 *    another static variable 'second'.
 *  - If parity is now 'true', that means we've already
 *    calculated 'c sin( 2 pi u2 )', which is stored in 
 *    the static variable 'second', so we just
 *    immediately return that value.
 *
 * See:
 *    https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
 ********************************************************/

double box_muller() {
  // Static local variables are shared between calls
  // to the function. 
  static bool parity = true;
  static double second;

  parity = !parity;

  if ( parity ) {
		return second;
	}

  // rand() returns an integer between 0 and
  // RAND_MAX inclusive, so this calculates a
  // random real in (0, 1]
  double u1 = (rand() + 1.0)/(RAND_MAX + 1.0);
  double u2 = (rand() + 1.0)/(RAND_MAX + 1.0);
  
	double c = sqrt( -2.0*log( u1 ) );

	// If the math.h library does not have M_PI,
  // use this statement:
  //    	double two_pi = 8.0*std::atan( 1.0 );
	// as atan(1) == pi/4
	double two_pi = 2.0*M_PI;

  // Store the second value in the static variable
  // 'second', and on the next call, that is the 
  // value that will be returned.
	second = c*sin( two_pi*u2 );

	return c*cos( two_pi*u2 );
}