function [A,b]=no_name(n)
  A=5*eye(n)+diag(-1*ones(1,n-1), 1) + diag(-1*ones(1,n-1), -1);

  b=[4;3*ones(n-2, 1); 4];

endfunction

