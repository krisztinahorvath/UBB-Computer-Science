function t = backward_diff(f)
  n = length(f);
  t = zeros(n);
  t(:,1)=f';

  for k=2:n
    t(k:n, k) = diff(t(k-1:n, k-1));
  endfor

endfunction
