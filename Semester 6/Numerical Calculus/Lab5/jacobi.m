function [x,nit]=jacobi(A,b,x0,max_it,err)
  M=diag(diag(A));
  N=M-A;
  T=inv(M)*N;
  c=inv(M) *b;
  alpha=norm(T,inf);

  x=x0;
  for nit = 1:max_it
    x_old = x;
    x = T * x_old + c;
    if norm(x - x_old, inf) < err * (1 - alpha) / alpha
      return
    endif
  endfor

endfunction

