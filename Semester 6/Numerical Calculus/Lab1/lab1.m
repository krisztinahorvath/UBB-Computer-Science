# lab1

# review
A = [1, 2; 3, 4];

A^2 # A * A, carot = ^
A.^2 # square each element

B = [1:100];
B = [1:0.1:100]; # step size 0.1

diag([1,2,3]);  # matrix with the diagonal [1,2,3] and the rest of the elems are 0

diag(A); # returns the main diagonal

# Exercise 1
# b.) p(-2.5)

# help polyval # for documentation on the function

p = [1, -5, -16, 16, -17, 21]; # if coeff missing write a 0
polyval(p, -2.5);

# a.) plot polyn in interval [-4, 7.2]
# for exam, calculate the value for some numbers in the interval and connect the dots

x = -4:0.1:7.2;
px = polyval(p, x);

plot(x, px);

# c.)
roots(p);
polyval(p, 7); # 7 is a root

# Exercise 2
x = linspace(0, 2*pi, 150); # divides into 150 intervals
plot(x, sin(x), x, sin(2*x), x, sin(3*x))
clf # clearss the figure
plot(x, sin(x))
hold on # after this the plots will be done on the same figure
plot(x, sin(2*x))
plot(x, sin(3*x))
hold off # if you don't want to plot on the same figure anymore

# different method:
f = @(x) sin(x); # define a function
f([1,2]);
fplot(f, [0, 2*pi]);

subplot(3, 1, 1);
fplot(f, [0, 2*pi]);
subplot(3, 1, 2);
fplot(@(x) sin(2*x), [0, 2*pi]);
subplot(3, 1, 3);
fplot(@(x) sin(3*x), [0, 2*pi]);

clf

# Exercise 3
t = linspace(0, 10*pi, 1000);
R = 3.8;
r = 1;
x = (R+r)*cos(t) - r*cos((R/r + 1) *t);
y = (R + r)*sin(t) - r*sin((R/r + 1) *t);
plot(x, y);

# Exercise 4
[x, y] = meshgrid(linspace(-2,2), linspace(0.5, 4.5));
f = sin(exp(x)).*cos(log(y));
mesh(x, y, f) # mesh is like plot
plot3(x, y,f)

# Exercise 5
n = 20000;
f = 2;
for i = 1:n
  f = 1 + 1/f;
end
f # f = 1.6180 golden ratio


