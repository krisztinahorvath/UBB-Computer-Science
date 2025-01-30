function t = forward_diff(f)
  n = length(f);
  t = zeros(n);
  t(:,1)=f';

  for k=2:n
    t(1:n-k+1, k) = diff(t(1:n-k+2, k-1));
  endfor

endfunction
