function I=rect(f,a,b,n)
  h=(b-a)/n; # length of one subinterval
  I=h*(sum(f(a+([0:n-1] + 1/2)*h)));
endfunction
