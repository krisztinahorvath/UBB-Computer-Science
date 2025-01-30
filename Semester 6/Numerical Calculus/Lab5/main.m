[A,b]=no_name(500);

x0=zeros(size(b));
max_it=100;
err=10^(-5);

# 1
[x,nit]=jacobi(A,b,x0,max_it,err)

[x,nit]=gauss_seidel(A,b,x0,max_it,err)

# 2
A=[10 7 8 7; 7 5 6 5; 8 6 10 9; 7 5 9 10];
b=[32;23;33;31];

# a
systemA=A\b

# b
bTilda=[32.1;22.9;33.1;30.9];
xTilda=A\bTilda
err_b=norm(b-bTilda)/norm(b)
err_x=norm(systemA-xTilda)/norm(systemA)

#c)
ATilda=[10 7 8.1 7.2; 7.8 5.04 6 5; 8 5.98 9.89 9; 6.99 4.99 9 9.98];
systemC=ATilda\b
err_A=norm(A-ATilda)/norm(A)
err_x=norm(systemC-systemA)/norm(systemA)

#d) condition number

condA=norm(A)*norm(inv(A))

