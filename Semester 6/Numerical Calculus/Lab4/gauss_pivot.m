function x = gauss_pivot(A, b)
  [r, n] = size(A); # m n
  x = zeros(size(b));
  A = [A, b];
  for j = 1:n-1
    #[v, p] = max( abs( A( A) )); ##

    # swap rows: A([a,b],:) = A([b, a], :);
    for i = j+1:r
      if(abs(A(j, j)) < abs(A(i, j)))
        A([j i], :) = A([i j], :);
        b([j i]) = b([i j]);
      endif

      m = A(i, j) / A(j, j); ##
      A(i, j+1:n) = A(i, j+1:n) - m*A(j, j+1:n); ##
    endfor
  endfor

  x = backward_subs( A(:,1:n), A(:, n+1));

endfunction

