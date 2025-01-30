function I=simpson(f,a,b,m)
  h = (b-a)/(2*m);
  I = h/3*(f(a) + 4* sum(f(a + (2*[1:m]-1) * h))
      + 2 * sum(f(a + 2*[1:m-1] * h)) + f(b));
endfunction
