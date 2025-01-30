# 1
log(2)
f=@(x)1./x;
rectan=rect(f, 1, 2, 13)

trap=trapezoid(f, 1, 2, 9)
simp=simpson(f, 1, 2, 9)

g=@(x)sqrt(1+(pi*cos(pi*x)).^2);
adapt=adaptQuad(g, 0, 1, 0.1, @simpson, 4)
