#pragma once

unsigned int gaussian_elimination( double **array,
                                   unsigned int m,
                                   unsigned int n,
                                   double tolerance );

unsigned int max_abs_index( double **array,
                            unsigned int i,
                            unsigned int j,
                            unsigned int m );

unsigned int leading_zeros( double **array,
                            unsigned int i,
                            unsigned int n,
                            double tolerance );

unsigned int analize_row_echelon_form( double      **array,
                                       bool         *is_free_variable_array,
                                       unsigned int *index_array,
                                       unsigned int m,
                                       unsigned int n,
                                       double       tolerance );

void print_array( double **array, unsigned int m, unsigned int n, unsigned int bar );