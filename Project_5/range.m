f = @(x) sin(2.4*x + 0.8) + 3.5*sin(8.3*x + 1.5) + 3.7*sin(0.5*x + 1.2);
format long g

for a = 0:5
    for b = 1:14
        % Define the resolution of the search (number of points to evaluate)
        n_points = 100,000,000;

        % Evaluate the function at n_points equally spaced points between a and b
        x_values = linspace(a, a+b, n_points);
        y_values = f(x_values);

        % Find the minimum and maximum values of the function over the interval
        min_val = min(y_values);
        max_val = max(y_values);

        % Compute the range of the function over the interval
        range = max_val - min_val;
        fprintf('The range of the function over the interval [%f, %f] is %0.16f\n', a, a+b, range);

    end
end

