xi=[0,1,2];
fi=1./(1+xi);
d=divided_diff(xi,fi);
xx=linspace(0,2,100);
plot(xx,newton_int(xi,d,xx));

# hermite
dfi=-1./(1+xi).^2;
[zi, d2]=divided_diff2(xi,fi,dfi);
hold on
plot(xx,newton_int(zi,d2,xx))

# 2
# xi=time
# fi=distance
# dfi=velocity

xi = [0, 3, 5, 8, 13];
fi = [0, 225, 383, 623, 993];
dfi = [0, 77, 80, 74, 72];
t=10;
[zi,d2]=divided_diff2(xi,fi,dfi);
newton_int(zi,d2,10);

d=divided_diff(xi,dfi);
newton_int(xi,d,10);

d=divided_diff(fi,dfi);
newton_int(fi,d,728.911)
