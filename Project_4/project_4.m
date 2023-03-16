a = 0
b = 2
n = 16
h = (b - a)/n

f = @(x) (sin(x))
F = @(x)( 1.0 - cos(x) );

x = zeros( n + 1, 1 );
for k = 0:n
  x(k + 1) = a + k*h;
end

y = zeros( n + 1, 1 );
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

rmse = 0.0;
for k = 2:(n + 1)
  rmse = rmse + (y(k) - F(x(k))^2);
end
rmse = sqrt( rmse/(n + 1.0) )


