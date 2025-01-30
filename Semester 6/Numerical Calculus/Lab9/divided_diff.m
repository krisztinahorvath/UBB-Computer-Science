function t = divided_diff(x, f)
  n = length(x);
  t = zeros(n);
  t(:, 1) = f'; # : bcs we go through all the indexes, 1 bcs its the first column

  for k = 2:n
    t(1:n-k+1, k) = diff(t(1:n-k+2, k-1))./(x(k:n) - x(1:n-k+1))';
  endfor

endfunction

