function I=trapezoid(f,a,b,n)
  h=(b-a)/n;
  I=h/2*(f(a)+f(b) + 2*(sum(f(a+[1:n-1]*h))));
endfunction
