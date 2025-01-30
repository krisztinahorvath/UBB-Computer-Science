#1
pkg load symbolic
vpa(pi*sqrt(3)/9,6)
f=@(x)1./(2+sin(x));
[I,nf]=romberg(f,0,pi/2, 10^(-6), 50)

#2
gauss_quad(@(x)(x.^2+1)./(x.^2+1), 2, 3)

#3
# Legendre
n=5;
integral(@(x)exp(cos(x)),0,pi/4)
ex3=gauss_quad(@(x)(cos(x)), n, 1)

# res should be 1.9

#4 any subpoint
# a laguerre
# b hermite
# c chebyshev 1
n=4;

#c chebyshev 1
ex4=gauss_quad(@(x)(sin(x.^2)), n,2)





