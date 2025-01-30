# pkg load symbolic

# 3
syms x
f = log(1 + x)
f1 = taylor(f, x, 0, 'Order', 3)
f2 = taylor(f, x, 0, 'Order', 6)

ezplot(f, [-0.9,1])
hold on
ezplot(f1, [-0.9, 1])
ezplot(f2, [-0.9, 1])

# b
log(2)
vpa(log(2), 6)

# warning off
for k = 6:20
  T = taylor(log(2), x, 0, 'Order', k);
  k
  vpa(subs(T, x, 1), 6)
end

# c
f = log(1-x)
f1 = taylor(log(1-x), x, 0, 'Order', 8)

# d.
f2 = taylor(log(1+x), x, 0, 'Order', 8)- taylor(log(1-x), x, 0, 'Order', 8)

# e.
# use f2 to approximate log(2)
vpa(f2, 6)

# warning off
for k = 6:20
  T = taylor(taylor(log(1+x), x, 0, 'Order', k)- taylor(log(1-x), x, 0, 'Order', k), x, 0, 'Order', k);
  k
  vpa(subs(T, x, 1/3), 6)
end


