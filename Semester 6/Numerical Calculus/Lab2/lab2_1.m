# pkg load symbolic

# 1
# a
syms x
f = exp(x)
f1 = taylor(f, x, 0, 'Order', 2) # 2 = degree + 1
f2 = taylor(f, x, 0, 'Order', 3)
f3 = taylor(f, x, 0, 'Order', 4)
f4 =taylor(f, x, 0, 'Order', 5)

ezplot(f, [-3, 3])
hold on
ezplot(f1, [-3, 3])
ezplot(f2, [-3, 3])
ezplot(f3, [-3, 3])
ezplot(f4, [-3, 3])

# b
exp(1)
vpa(exp(1), 7)
subs(f1, x, 1)
vpa(subs(f4, x, 1), 7)

for k = 6:20
  T = taylor(f, x, 0, 'Order', k);
  k # from k = 10 on, it is  2.718282
  vpa(subs(T, x, 1), 7)
end

