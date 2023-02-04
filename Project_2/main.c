#include <stdio.h>
#include <math.h>
#include "analyze.h"
#include "box_muller.h"

/* Global variables: sometimes necessary in C */
double const AMPLITUDE = 15.2;  /* 15.2 m */
double const PHASE_SHIFT = 0.3; /* 0.3 s */
double const PERIOD = 13.4;     /* 13.4 s */
// Had to change amplitude and period with actual literal
double const ERROR = AMPLITUDE * 0.05;  /* 5% of the amplitude */
double const STEP_SIZE = PERIOD / 32.0; /*  0.2 s */

int main();
double f(double x);

/* You will implement the functions in the 'analyze.c' file,
   all function declarations as well as 'struct' declarations
   and 'struct' definitions are in the 'analyze.h' file. */

int main()
{
 data_t record;

  data_init( &record, STEP_SIZE );

  unsigned int k;

  for ( k = 0; k < 32; ++k ) {
    double exact = f( STEP_SIZE*k );
    double approx = exact + ERROR*box_muller(); 
    data_append( &record, approx );
    printf( "Data %d: %f\n", k, approx );
  }

  for ( k = 32; k < 100; ++k ) {
    double exact = f( STEP_SIZE*k );
    double approx = exact + ERROR*box_muller(); 
    data_append( &record, approx );

    printf( "Data %d: %f\n", k, approx );
    printf( "  Ideal current value:   %f\n", exact );
    printf( "  Approximation:         %f\n\n", data_current( &record ) );
    printf( "  Ideal next value:      %f\n", f( STEP_SIZE*(k + 1.0) ) );
    printf( "  Approximation:         %f\n\n", data_next( &record ) );
  }

  return 0;
}

/* Do not change these */

double f(double x)
{
  return AMPLITUDE * cos(2 * M_PI * x / PERIOD + PHASE_SHIFT);
}