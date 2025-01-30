# Applications
# 1

# a) Find the divided differences table of f at the simple nodes x0 = 0, x1 = 1, x2 = 2;
x=[0, 1, 2];
f = 1./(1+x);

divided_diff(x, f)

# b.)
df = -1./(1+x).^2;
[z, t] = divided_diff2(x, f, df)

# c.)
x = linspace(1, 2, 11);
f = 1./(1+x);
df = -1./(1+x).^2;

divided_diff(x, f)
[z, t] = divided_diff2(x,f, df)

# 2.
# a.)
x=[-2, -1, 0, 1, 2, 3, 4];
f=[-5, 1, 1, 1, 7, 25, 60];
divided_diff(x, f)

# b.)
forward_diff(f)

#c.)
backward_diff(f)
