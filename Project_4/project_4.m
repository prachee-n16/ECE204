a = 0
b = 2
n = 16
h = (b - a)/n
iteration = 10

hs = zeros(iteration, 1);
rmses = zeros(iteration, 1);

for j = 1:iteration
  hs(j) = n;
  format long
  % this is the function f(x)
  f = @(x) (sin(x))
  % this is the antiderivative of the above function
  F = @(x)( 1.0 - cos(x) );

  x = zeros( n + 1, 1 ); % dimensions of x is n+1 x 1 and x is full of zeroes
  for k = 0:n
    x(k + 1) = a + k*h;
  end

  y = zeros( n + 1, 1 ); % dimensions of y is n+1 x 1 and x is full of zeroes

  % Trapezoidal rule
  y(1) = 0.0;

  for k = 1:n
    y(k + 1) = y(k) + 0.5*(f(x(k)) + f(x(k + 1)))*h;
  end

  % Next, calculate the RMSE.
  %                  x
  %                /
  % Assume F(x) = | f(x_i) d (x_i) as described above
  %               /
  %              a

  % find n approximations where

  y(1) = 0.0;
  y(2) = y(1) + ((-1/24)*f(a-h) + (13/24)*f(x(1)) + (13/24)*f(x(2)) - (1/24)*f(x(3)))*h;

  for k = 3:n
    % use the centered 4 point formula to approximate the integral
    a = (-1/24)*f(x(k-2)) + (13/24)*f(x(k-1)) + (13/24)*f(x(k)) - (1/24)*f(x(k+1));
    a = a*h;
    % y(k) = y(k-1) + approximation of integral from x(k-1) to x(k)
    y(k) = y(k-1) + a;
  end

  rmse = 0.0;

  for k = 2:(n + 1)
    rmse = rmse + (y(k) - F(x(k)))^2;
  end

  rmse = sqrt( rmse/(n + 1.0) )
  rmses(j) = rmse;

  n = n*2
  h = (b - a)/n
end

% print out h and rmse values here
y(end)

V = [log(hs) log(hs).^0];
p = V \ log(rmses)

plot( hs, rmses, 'o' );
plot( log(hs), log(rmses), 'o' );

