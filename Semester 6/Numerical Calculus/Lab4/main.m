U = [2 4 2; 0 -1 1; 0 0 -1];
b = [8; 0; -1];

backward_subs(U, b);

L = [1 0 0; 1/2 1 0; 1/2 1 1];
b = [8; 4; 3];
forward_subs(L, b);

# Applications:
# 1.)
A = [2 1 -1 -2; 4 4 1 3; -6 -1 10 10; -2 1 8 4];
b = [2; 4; -5; 1];
[L, U, P] = lu(A);
y = forward_subs(L, P*b);
x = backward_subs(U, y)

# 2.)

a = gauss_pivot(A, b)


