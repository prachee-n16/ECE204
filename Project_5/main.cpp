#include <iostream>
#include <functional>
#include <cmath>

int main();
double range(std::function<double(double)> f,
             double a,
             double b,
             double max_freq);
// These will change for the tests
double f1(double x);
double f2(double x);
double f3(double x);

int main()
{
    std::cout.precision(16);

    // These will change  for the tests
    double max_freq1{8.3 / 2.0 / M_PI};

    for (double a{0.0}; a <= 5.0; ++a)
    {
        for (double b{1.0}; b <= 14.0; ++b)
        {
            std::cout << "[" << a << ", " << a + b << "]" << std::endl;
            f1(INFINITY);
            std::cout << range(f1, a, a + b, max_freq1) << std::endl;
            std::cout << "Function calls: " << f1(INFINITY) << std::endl;
            std::cout << range(f1, a, a + b, max_freq1) << std::endl;
            f1(INFINITY);
            std::cout << " >> " << range(f1, a, a + b, max_freq1) - range(f1, a, a + b, max_freq1) << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}

////////////////////////
// The function 'f(x) //
////////////////////////

double f1(double x)
{
    static unsigned long count{0};

    if (x == INFINITY)
    {
        unsigned long value{count};
        count = 0;
        return value;
    }
    else
    {
        ++count;
        return std::sin(2.4 * x + 0.8) + 3.5 * std::sin(8.3 * x + 1.5) + 3.7 * std::sin(0.5 * x + 1.2);
    }
}

double range(std::function<double(double)> f,
             double a, double b,
             double max_freq)
{

    double T = 1/max_freq;
    int n = std::ceil((b - a)/T);
    T = (b - a)/n;

    // Let's create an array of x values where we want to sample f(x)
    double x_k[(n+1)*4];
    double f_x_k[(n+1)*4];

    

    // Get it down using Successive parabolic interpolation 
    return 0;
}