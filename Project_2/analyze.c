#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "analyze.h"

// You can add other functions if you want to perform
// other calculations independent of these functions.

void data_init(data_t *p_this, double step_size)
{
  // Initialize dynamic array
  p_this = malloc(sizeof(int) * CAPACITY);
  p_this->front = 0;
}

// You may not need this if you do not have a dynamically
// allocated array.
void data_destroy(data_t *p_this)
{
  // Free data
  free(p_this);
}

void data_append(data_t *p_this, double new_value)
{
  // Efficient solution would use mod(n) something

  // Possible solution:
  //  keep track of where front is in array
  //  mod capacity each time 1 mod 10 = 1 and keep going on
  //  that's the index!
  p_this->entries_[p_this->front % CAPACITY] = new_value;
  p_this->front = p_this->front + 1;
}

double data_current(data_t *p_this)
{
  // Find solution a.k.a. coeff for polynomial
  double coeff[] = {-9.9242e-02,  -6.2844e-02,   8.9371e-02,   1.2130e-01,   1.6396e-01,   1.8743e-01,   1.9842e-01,   1.6447e-01,   1.5546e-01,   8.1669e-02};
  size_t k;

  double result = 0.0;

  for (k = 0; k < CAPACITY; ++k)
  {
    result += coeff[k] * (p_this->entries_[p_this->front % CAPACITY] );
  }

  return result;
}

double data_next(data_t *p_this)
{
  // Your implementation here...
  return 0.0;
}