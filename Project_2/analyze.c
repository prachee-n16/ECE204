#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "analyze.h"

// You can add other functions if you want to perform
// other calculations independent of these functions.

void data_init( data_t *p_this, double step_size ) {
  //Initialize dynamic array 
  p_this = malloc (sizeof (int) * CAPACITY);
  front = 0;
}

// You may not need this if you do not have a dynamically
// allocated array.
void data_destroy( data_t *p_this ) {
  // Free data
  free(p_this);
}

void data_append( data_t *p_this, double new_value ) {
  // Efficient solution would use mod(n) something  

  //Possible solution:
    // keep track of where front is in array 
    // mod capacity each time 1 mod 10 = 1 and keep going on
    // that's the index!
  p_this->entries_[front % CAPACITY] = new_value;
  front = front + 1;
}

double data_current( data_t *p_this ) {
  // Your implementation here...
  return 0.0;
}

double data_next( data_t *p_this ) {
  // Your implementation here...
  return 0.0;
}