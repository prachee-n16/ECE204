hs = [0.4, 0.2, 0.1, 0.05, 0.025]’
V = [log(hs) log(hs).^0];

rmses = [

];

% Calculate the least-squares best-fitting linear polynomial

p = V \ log(rmses)
