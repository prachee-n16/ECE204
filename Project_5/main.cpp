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
void sort(double &x0, double &x1, double &x2,
          double &f0, double &f1, double &f2);

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
    // scale
    double T = 1 / max_freq;
    int n = std::ceil((b - a) / T); // the number of periods between a and b
    T = (b - a) / n;

    // Let's create an array of x values where we want to sample f(x)
    double x_k[(n + 1) * 4];
    double f_x_k[(n + 1) * 4];

    for (int k = 0; k <= n * 4; k++)
    {
        // Populate the points we want to look at
        x_k[k] = a + 0.25 * k * T;
        f_x_k[k] = f(x_k[k]);
    };

    double min{0};
    double max{0};

    double f_a = f(a);
    double f_b = f(b);

    if (f_a < f(b)) {
        min = f_a;
        max = f_b;
    } else {
        min = f_b;
        max = f_a;
    }
    
    double eps_abs = 1e-12;
    int max_iterations = 100;

    // FIXME: This range is not right! but i will fix it later
    for (int i = 0; i < ((n + 1) * 4 - 5); i++)
    {
        // So, now we have points
        // let's see if we can find a local maxima or minima
        // For ease, let's store it in some fun variables
        double f0 = f_x_k[i];
        double f1 = f_x_k[i + 1];
        double f2 = f_x_k[i + 2];

        double x0{x_k[i]};
        double x1{x_k[i + 1]};
        double x2{x_k[i + 2]};

        if ((f1 > f0) && (f1 > f2))
        {
            // This is a local maxima
            // Perform successive parabolic interpolation
            // Until we have not iterated over max_iterations

            for (unsigned int k{0}; k < max_iterations; ++k)
            {
                sort(x0, x1, x2, f0, f1, f2);

                double xnew = (x2 + x1) / 2 +
                              0.5 * ((f2 - f1) * (x1 - x0) * (x0 - x2) /
                                     (((f2 - f1) * (x1 - x0)) + ((f0 - f1) * (x2 - x1))));
                double fnew = f(xnew);


                if (fnew < f0)
                {
                    break;
                }
                else if ((std::abs(f2 - fnew) < eps_abs))
                {
                    if (fnew <= f2)
                    {
                        if (max < fnew)
                        {
                            max = fnew;
                        }
                        break;
                    }
                    else
                    {
                        if (max < f2)
                        {
                            max = f2;
                        }
                        break;
                    }
                }

                x0 = xnew;
                f0 = fnew;
            }
        }

        f0 = f_x_k[i];
        f1 = f_x_k[i + 1];
        f2 = f_x_k[i + 2];

        x0 = x_k[i];
        x1 = x_k[i + 1];
        x2 = x_k[i + 2];

        if ((f1 < f0) && (f1 < f2))
        {
            for (unsigned int k{0}; k < max_iterations; ++k)
            {
                sort(x2, x1, x0, f2, f1, f0);

                double xnew = (x2 + x1) / 2 +
                              0.5 * ((f2 - f1) * (x1 - x0) * (x0 - x2) /
                                     (((f2 - f1) * (x1 - x0)) + ((f0 - f1) * (x2 - x1))));
                double fnew = f(xnew);


                if (fnew > f0)
                {
                    break;
                }
                else if ((std::abs(f2 - fnew) < eps_abs))
                {
                    if (fnew <= f2)
                    {
                        if (min > fnew)
                        {
                            min = fnew;
                        }
                        break;
                    }
                    else
                    {
                        if (min > f2)
                        {
                            min = f2;
                        }
                        break;
                    }
                }

                x0 = xnew;
                f0 = fnew;
            }
        }
    };

    // Get it down using Successive parabolic interpolation
    return max-min;
}

void sort(double &x0, double &x1, double &x2,
          double &f0, double &f1, double &f2)
{
    if ((f1 < f0) && (f1 <= f2))
    {
        std::swap(x0, x1);
        std::swap(f0, f1);
    }
    else if (f2 < f0)
    {
        std::swap(x0, x2);
        std::swap(f0, f2);
    }

    if (f2 < f1)
    {
        std::swap(x1, x2);
        std::swap(f1, f2);
    }
}