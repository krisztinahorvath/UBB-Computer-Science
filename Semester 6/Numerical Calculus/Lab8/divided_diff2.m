function [z, t] = divided_diff2(x, f, df)
  n = length(x);
  z = repelem(x, 2);
  nz = 2*n;
  t = zeros(nz);
  t(:,1) = repelem(f, 2)';
  t(1:2:nz-1, 2) = df';
  t(2:2:nz-2, 2) = (diff(f)./diff(x))';

  for k=3:nz
    t(1:nz-k+1, k) = diff(t(1:nz-k+2, k-1))./(z(k:nz) - z(1:nz-k+1))';
  endfor

endfunction

