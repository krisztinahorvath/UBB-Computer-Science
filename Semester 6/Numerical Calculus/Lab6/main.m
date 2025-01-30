lagrange_int([1,2,3],[1,4,9],[5,4])

# 1
# a.)
xi=linspace(-2,4,10);
fi=(xi+1)./(3*xi.^2+2*xi+1);

x=linspace(-2,4,500);
f=(x+1)./(3*x.^2+2*x+1);

L9f=lagrange_int(xi,fi,x);

figure(1);plot(x,f,x,L9f,'-g')
figure(2);plot(x,abs(f-L9f),'-r')

max_err=max(abs(f-L9f))

# for x = 1/2
x=1/2;
L9f=lagrange_int(xi,fi,x);
f=(x+1)./(3*x.^2+2*x+1);

max_err=max(abs(f-L9f))

# 2
lagrange_barycentric([1,2,3],[1,4,9],[2,3,1])
xi=1980:10:2020;
fi=[4451 5287 6090 6970 7821];
lagrange_barycentric(xi,fi,[2005,2015])
rel_err=lagrange_barycentric(xi,fi,[2005,2015])/(abs(6521.9 -7144.2))

# 3
sqrt(118)
xi=[100 121 144];
fi=[10 11 12];

lagrange_barycentric(xi,fi,118)
