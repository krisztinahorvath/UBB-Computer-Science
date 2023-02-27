# 8.   The client sends to the server two arrays of integers.
# The server returns an arrays containing the common numbers found in both arrays.

import socket
import pickle

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

conn, addr = s.accept()

r = conn.recv(4096)

a = pickle.loads(r)

a1 = a[0]
a2 = a[1]

print(a1)
print(a2)

res = []

for i in a1:
    for j in a2:
        if i == j and i not in res:
            res.append(i)

res_final = pickle.dumps(res)

conn.send(res_final)
conn.close()

conn.close()

