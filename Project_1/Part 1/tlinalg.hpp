#pragma once

#include <iostream>
#include <string>
#include <vector>

// Class declarations
template <unsigned int n>
class vec;

template <unsigned int m, unsigned int n>
class matrix;

enum NORM {
  infinity, one, two
};

// Class definitions
template <unsigned int m, unsigned int n>
class matrix {
  public:
    matrix( double constant = 0.0 );
    matrix( std::initializer_list<std::initializer_list<double>> init );
    matrix( std::initializer_list<vec<m>> init );
    matrix( std::initializer_list<double> init );

    double &operator()( unsigned int i, unsigned int j );
    double const &operator()( unsigned int i, unsigned int j ) const;
    std::string to_string() const;

    // Scalar multiplication
    matrix operator *( double s ) const;
    matrix &operator *=( double s );
    matrix operator /( double s ) const;
    matrix &operator /=( double s );

    // Matrix addition
    matrix operator+( matrix const &A ) const;
    matrix &operator+=( matrix const &A );
    matrix operator-( matrix const &A ) const;
    matrix &operator-=( matrix const &A );

    // Scalar addition
    matrix operator+( double s ) const;
    matrix &operator+=( double s );
    matrix operator-( double s ) const;
    matrix &operator-=( double s );

    // Unary operators
    matrix operator +() const;
    matrix operator -() const;

    vec<m> operator*( vec<n> const &v ) const;

    matrix<n, m> operator*() const;

    matrix<m, n> operator*=( matrix<n, n> const &A ) const;

    unsigned int rank( double tolerance = 1e-12 ) const;

    double det( double tolerance = 1e-12 ) const;
    double tr() const; 
    matrix<n, m> inv( double tolerance = 1e-12 ) const;

    std::vector<vec<n>> solve( vec<m> const &v,
                               double        tolerance = 1e-12 ) const;

  private:
    double entries_[m][n];
    void throw_matrix_exception( unsigned int i, unsigned int j ) const;

  template <unsigned int ell, unsigned int em, unsigned int en>
  friend matrix<ell, en> operator*( matrix<ell, em> const &B, matrix<em, en> const &A );
};

template <unsigned int m, unsigned int n>
matrix<n, m> transpose( matrix<m, n> const &A );

template <unsigned int ell, unsigned int m, unsigned int n>
matrix<ell, n> operator*( matrix<ell, m> const &B, matrix<m, n> const &A );

template <unsigned int m, unsigned int n>
double det( matrix<m, n> const & A );

template <unsigned int m, unsigned int n>
double tr( matrix<m, n> const & A ); 

template <unsigned int m, unsigned int n>
matrix<n, m> inv( matrix<m, n> const & A );

template <unsigned int n>
class vec {
  public:
    vec( double constant = 0.0 );
    vec( std::initializer_list<double> init );

    double &operator()( unsigned int k );
    double const &operator()( unsigned int k ) const;
    std::string to_string() const;

    // Scalar multiplication
    vec operator *( double s ) const;
    vec &operator *=( double s );
    vec operator /( double s ) const;
    vec &operator /=( double s );

    // Vector addition
    vec operator+( vec const &v ) const;
    vec &operator+=( vec const &v );
    vec operator-( vec const &v ) const;
    vec &operator-=( vec const &v );

    // Scalar addition
    vec operator+( double s ) const;
    vec &operator+=( double s );
    vec operator-( double s ) const;
    vec &operator-=( double s );

    // Unary operators
    vec operator +() const;
    vec operator -() const;

    // Inner product
    double operator *( vec const &v ) const;

    double norm() const;
    double norm( NORM flavor ) const;
    vec &project( vec const &v );

  private:
    double entries_[n];

    void throw_vector_exception( unsigned int k ) const;
};

template <unsigned int n>
double norm( vec<n> const &v );

template <unsigned int m, unsigned int n>
unsigned int rank( matrix<m, n> const &A );

template <unsigned int n>
vec<n> operator *( double s, vec<n> const &v );

template <unsigned int n>
vec<n> operator /( double s, vec<n> const &v );

template <unsigned int n>
std::ostream &operator<<( std::ostream &out, vec<n> const &rhs );

template <unsigned int m, unsigned int n>
std::ostream &operator<<( std::ostream &out, matrix<m, n> const &rhs );

#include "vec.tpp"
#include "matrix.tpp"