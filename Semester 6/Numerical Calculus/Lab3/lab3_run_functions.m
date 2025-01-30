# divided differences

# 1. Write a MATLAB function that generates the divided differences table,
# given the nodes and the function
# values (i.e., for simple nodes).

x=[0, 1/6, 1/2];
f=[0, 1/2, 1];

divided_diff(x, f)

x=[-1, 1];
f=[-3, 1];
df=[10, 2];

[z, t] = divided_diff2(x, f, df)
