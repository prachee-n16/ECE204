
a = 0
b = 2
n = 2
h = (b - a)/n
iteration = 20

hs = zeros(iteration, 1);
rmses = zeros(iteration, 1);

format long
% this is the function f(x)
f = @(x) (sin(x));
% this is the antiderivative of the above function
F = @(x)( 1.0 - cos(x) );

for j = 1:iteration
  hs(j) = h;

  x = zeros( n + 1, 1 ); % dimensions of x is n+1 x 1 and x is full of zeroes
  for k = 0:n
    x(k + 1) = a + k*h;
  end

  y = zeros( n + 1, 1 ); % dimensions of y is n+1 x 1 and x is full of zeroes

  y(1) = 0.0;
  y(2) = y(1) + ( (9/24)*(f(x(2))) + (19/24)*(f(x(1))) - (5/24)*(f(a-h)) + (1/24)*(f(a-2*h) )) *h;
  y(3) = y(2) + ( (9/24)*(f(x(3))) + (19/24)*(f(x(2))) - (5/24)*(f(x(1)))+ (1/24)*(f(a-h)) ) *h;

  % try some thing here for backward 4 point formula
  % find n approximations where
  for k = 4:n+1
    % use the backward 4 point formula to approximate the integral
    y(k) = y(k-1) + ( (9/24)*(f(x(k))) + (19/24)*(f(x(k-1))) - (5/24)*(f(x(k-2))) + (1/24)*(f(x(k-3))) ) *h;
  end

  rmse = 0.0;

  for k = 2:(n + 1)
    rmse = rmse + (y(k) - F(x(k)))^2;
  end

  rmse = sqrt( rmse/(n + 1.0) );
  rmses(j) = rmse;

  n = n*2;
  h = (b - a)/n;
end

% print out h and rmse values here
y(end)

V = [log(hs) log(hs).^0];
p = V \ log(rmses)

% plot( hs, rmses, 'o' );

display(n)
plot( log(hs), log(rmses), 'o' );

hold on
plot( [-2, -1], polyval( p, [-2, -1] ), 'r' );

hold off
