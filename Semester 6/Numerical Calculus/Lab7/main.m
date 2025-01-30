# ex1
xi=[0,1/3,1/2,1];
fi=cos(pi*xi);
d=divided_diff(xi,fi);
xx=linspace(0,1,100);
plot(xx,cos(pi*xx), xx, newton_int(xi,d,xx))

# d
approx=newton_int(xi, d, 1/5)
cosVal=cos(pi/5)

# ex3
xi=[1000,1010,1020,1030,1040,1050];
fi=[3.0000000, 3.0043214, 3.0086002, 3.0128372, 3.0170333, 3.0211893];
d=divided_diff(xi,fi);
approxLog10=newton_int(xi,d, 1000:1009)
logVal=log10(1001:1009)

# ex2
xi=-4:4;
fi=2.^xi;
sqrt2Val=sqrt(2)
sqrt2Aitken=aitken(xi,fi,1/2)

