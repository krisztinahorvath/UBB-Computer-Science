function [x,nit]=gauss_seidel(A,b,x0,max_it,err)
  # tril - lower part of matrix
  # triu - upper part
  M = tril(A);
  N = -triu(A, 1);
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

