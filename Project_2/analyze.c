#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "analyze.h"

// You can add other functions if you want to perform
// other calculations independent of these functions.

void data_init(data_t *p_this, double step_size)
{
  p_this->front = 0;
}

// You may not need this if you do not have a dynamically
// allocated array.
void data_destroy(data_t *p_this){}

void data_append(data_t *p_this, double new_value)
{
  // Efficient solution would use mod(n) something

  // Possible solution:
  //  keep track of where front is in array
  //  mod capacity each time 1 mod 10 = 1 and keep going on
  //  that's the index!

  //incrementing first because if increment after adding new value, when front is accessed in the for loop, we actually get front+1 instead of front
  p_this->front = p_this->front + 1;
  p_this->entries_[p_this->front % CAPACITY] = new_value;   // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0     //11 12 13 14
}

double data_current(data_t *p_this)
{
  // Find solution a.k.a. coeff for polynomial
  double coeff[] = {0.618181818181819, 0.381818181818182 ,  0.190909090909091 ,  0.045454545454545 , -0.054545454545455 , -0.109090909090910 , -0.118181818181819 , -0.081818181818182 ,  0.000000000000001 , 0.127272727272729};
  size_t k;

  double result = 0.0;

 // printf("FRONT: %d \n", p_this -> front);

  for (k = 0; k < CAPACITY; k++)
  {

    // the Capacity + (p_this->blah blah) takes care of negative numbers that might occur because of p_this->front-k
    result += coeff[k] * (p_this->entries_[(CAPACITY + (p_this->front - k)) % CAPACITY] );

   // printf("queue value x: %f \n", p_this->entries_[(CAPACITY + (p_this->front) - k) % CAPACITY]);

    // front = 44
    // 0 : 10 + 44 - 0 = 44 % 10 = 4
    // 0 : 10 + 44 - 1 = 43 % 10 = 3

  }

  return result;
}

double data_next(data_t *p_this)
{
  //Find solution a.k.a. coeff for polynomial
  double coeff_1[] = {0.022727272727273 , 0.007575757575758 , -0.003787878787879 , -0.011363636363636 , -0.015151515151515 , -0.015151515151515 , -0.011363636363636 , -0.003787878787879 ,  0.007575757575758 , 0.022727272727273};
  double coeff_2[] = {0.259090909090910 , 0.110606060606061 , -0.003787878787879 , -0.084090909090910 , -0.130303030303031 , -0.142424242424243 , -0.120454545454546 , -0.064393939393940 ,  0.025757575757576 , 0.150000000000001};
  double coeff_3[] = {0.618181818181819, 0.381818181818182 ,  0.190909090909091 ,  0.045454545454545 , -0.054545454545455 , -0.109090909090910 , -0.118181818181819 , -0.081818181818182 ,  0.000000000000001 , 0.127272727272729};
  
  size_t k;

  double result = 0.0;

  for (k = 0; k < CAPACITY; k++)
  {
    result += coeff_1[k] * (p_this->entries_[(CAPACITY + (p_this->front - k)) % CAPACITY] );
    result += coeff_2[k] * (p_this->entries_[(CAPACITY + (p_this->front - k)) % CAPACITY] );
    result += coeff_3[k] * (p_this->entries_[(CAPACITY + (p_this->front - k)) % CAPACITY] );
  }

  return result;
}


/*

   0.022727272727273   0.007575757575758  -0.003787878787879  -0.011363636363636  -0.015151515151515  -0.015151515151515  -0.011363636363636  -0.003787878787879   0.007575757575758  0.022727272727273
   0.259090909090910   0.110606060606061  -0.003787878787879  -0.084090909090910  -0.130303030303031  -0.142424242424243  -0.120454545454546  -0.064393939393940   0.025757575757576  0.150000000000001
   0.618181818181819   0.381818181818182   0.190909090909091   0.045454545454545  -0.054545454545455  -0.109090909090910  -0.118181818181819  -0.081818181818182   0.000000000000001  0.127272727272729

*/