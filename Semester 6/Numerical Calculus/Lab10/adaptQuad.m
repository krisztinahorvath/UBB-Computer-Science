function I=adaptQuad(f,a,b,eps,met, m) # met = @rect
  I1=met(f,a,b,m);
  I2=met(f,a,b,2*m);
  if( abs(I1-I2) < eps)
    I=I2;
  else I=adaptQuad(f, a, a+b/2, eps, met, m) + adaptQuad(f, a+b/2, b, eps, met, m);
  endif
endfunction
