# 1
xi=-2:4;
fi=(xi+1)./(3*xi.^2+2*xi+1);
plot(xi,fi,'o');
xx=linspace(-2,4);
f=(xx+1)./(3*xx.^2+2*xx+1);
hold on
plot(xx, f)

# lagrange
d = divided_diff(xi, fi);
plot(xx, newton_int(xi, d, xx))

# hermite
dfi = -(3*xi.^2+6*xi+1)./(3*xi.^2+2*xi+1).^2;
[zi, d2] = divided_diff2(xi, fi, dfi);
plot(xx, newton_int(zi, d2, xx))

#clf
s=spline(xi,fi,xx);
plot(xx,s);


# 2
clf
xi=[-1, -1/2,0, 1/2, 1, 3/2];
fi=xi.*sin(pi*xi);
xx=linspace(-1,3/2);
s=spline(xi,fi,xx);
plot(xi,fi,'o',xx,s,xx,f)

hold on

dfi = sin(pi*xi)+ sin(pi*xi) + pi*xi.*cos(pi*xi);

sc=spline(xi, [pi, fi, -1], xx);
plot(xx, sc);

# piecewise Hermite interpolation
p=pchip(xi,fi,xx);
plot(xx,p);

# 3
clf
xi = [0.5, 1.5, 2, 3, 3.5, 4.5, 5, 6, 7, 8];
fi = [5, 5.8, 5.8, 6.8, 6.9, 7.6, 7.8, 8.2, 9.2, 9.9];

scatter(xi,fi);
hold on

p=polyfit(xi,fi,1);
plot([0.5, 8], polyval(p, [0.5, 8]))

error=norm(fi-polyval(p, xi))
errorAt4=polyval(p, 4)


