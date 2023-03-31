#include <iostream>
#include <functional>
#include <cmath>
#include <tuple>

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
            // std::cout << range(f1, a, a + b, max_freq1) << std::endl;
            // f1(INFINITY);
            std::cout << " >> " << range(f1, a, a + b, max_freq1) - range(f1, a, a + b, max_freq1) << std::endl;
            std::cout << std::endl;
        }
    }

    // double max_freq2{1.0 / M_PI};

    // for (double a{0.0}; a <= 5.0; ++a)
    // {
    //     for (double b{1.0}; b <= 14.0; ++b)
    //     {
    //         std::cout << "[" << a << ", " << a + b << "]" << std::endl;
    //         f2(INFINITY);
    //         std::cout << range(f2, a, a + b, max_freq2) << std::endl;
    //         std::cout << "Function calls: " << f2(INFINITY) << std::endl;
    //         std::cout << range(f2, a, a + b, max_freq2) << std::endl;
    //         f2(INFINITY);
    //         std::cout << " >> " << range(f2, a, a + b, max_freq2) - range(f2, a, a + b, max_freq2) << std::endl;
    //         std::cout << std::endl;
    //     }
    // }

    // double max_freq3{2.0 / M_PI};

    // for (double a{0.0}; a <= 0.0; ++a)
    // {
    //     for (double b{10.0}; b <= 10.0; ++b)
    //     {
    //         std::cout << "[" << a << ", " << a + b << "]" << std::endl;
    //         f3(INFINITY);
    //         std::cout << range(f3, a, a + b, max_freq3) << std::endl;
    //         std::cout << "Function calls: " << f2(INFINITY) << std::endl;
    //         std::cout << range(f3, a, a + b, max_freq3) << std::endl;
    //         f3(INFINITY);
    //         std::cout << " >> " << range(f3, a, a + b, max_freq2) - range(f3, a, a + b, max_freq2) << std::endl;
    //         std::cout << std::endl;
    //     }
    // }

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

double f2(double x)
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
        return std::sin(x) + std::sin(2.0 * x + 1.0);
    }
}

double f3(double x)
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
        return std::sin(x) + std::sin(2 * x) + std::sin(3 * x) + std::sin(4 * x);
    }
}

double range(std::function<double(double)> f,
             double a, double b,
             double max_freq)
{
    // values at the endpoints
    double endpoint_a = f(a);
    double endpoint_b = f(b);

    // Range has to be greater or equal to this number
    double range = endpoint_a - endpoint_b;
    
    double k = 1;
    double T = 1.0/max_freq;

    // having this be pure reciprocal gives us number of periods in one unit of v... so for v from a to b, gives us *that* many periods
    
    std::cout << "max_freq is : " << max_freq << std::endl;

    // v_k
    double v_1 = a + 0.25*k*T;
    // v_k+1
    double v_2 = a + 0.25*(k+1)*T;
    // v_k+2
    double v_3 = a + 0.25*(k+2)*T;

    double f_v_1 = f(v_1);
    double f_v_2 = f(v_2);
    double f_v_3 = f(v_3);

    // So, the basic idea is I need to find the LCM of the periods of all the functions that make up this f(x)
    // How do I do this?

    std::cout << "Points " << v_1 << " " << v_2  << " " << v_3 << std::endl;

    
    std::tuple<double, double> max_num_range;
    std::tuple<double, double> min_num_range;

    // Step 3 logic: find where minimum and maximum lies
    if (f_v_2 > f_v_1 && f_v_2 > f_v_3)
    {
        max_num_range = std::make_tuple(v_1, v_3);
    } else if (f_v_1 > f_v_2 && f_v_1 > endpoint_a) {
        max_num_range = std::make_tuple(a, v_2);
    } else {
        max_num_range = std::make_tuple(v_3, b);
    }

    if (f_v_2 < f_v_1 && f_v_2 < f_v_3) {
        min_num_range = std::make_tuple(v_1, v_3);
    } else if (f_v_1 < endpoint_a && f_v_1 < f_v_2) {
        min_num_range = std::make_tuple(a, v_2);
    } else {
        min_num_range = std::make_tuple(v_3, b);
    }

    //std::cout << "Max Range: (" << std::get<0>(max_num_range) << ", " << std::get<1>(max_num_range) << ")" << std::endl;
    //std::cout << "Min Range: (" << std::get<0>(min_num_range) << ", " << std::get<1>(min_num_range) << ")" << std::endl;
    return 0;
}