# pkg load symbolic

# 2
# a.) sin(x) degree 3, 5, [-pi, pi]
clf
syms x
f = sin(x)
f1 = taylor(f, x, 0, 'Order', 4)
f2 = taylor(f, x, 0, 'Order', 6)

ezplot(f, [-pi, pi])
hold on
ezplot(f1, [-pi, pi])
ezplot(f2, [-pi, pi])

# b.)
vpa(sin(pi/5), 6)
subs(f1, x, 1)
vpa(subs(f2, x, 1), 7)

warning off
for k = 6:20
  T = taylor(sin(pi/5), x, 0, 'Order', k);
  k
  vpa(subs(T, x, 1), 6)
end

# c.)
vpa(sin(10 * pi/3)) # -0.866

warning off
for k = 6:20
  T = taylor(sin(10 * pi/3), x, 0, 'Order', k);
  k
  vpa(subs(T, x, 1), 6)
end

sin(pi/3)
sin(2*pi/3)

#
vpa(sin(-pi/3)) # -0.866

warning off
for k = 6:20
  T = taylor(sin(-pi/3), x, 0, 'Order', k);
  k
  vpa(subs(T, x, 1), 6)
end

# sin(10*pi/3) = sin(-pi/3)


