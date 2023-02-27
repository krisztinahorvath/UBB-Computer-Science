# 8.   The client sends to the server two arrays of integers.
# The server returns an arrays containing the common numbers found in both arrays.

import socket
import pickle

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.1.4", 7777))

v1 = []
n1 = int(input("n1 = "))
for i in range(0, n1):
    x = int(input("x = "))
    v1.append(x)

v2 = []
n2 = int(input("n2 = "))
for i in range(0, n2):
    x = int(input("x = "))
    v2.append(x)

arr = (v1, v2)

to_send = pickle.dumps(arr)

s.send(to_send)


# todo
res = s.recv(4096)
res_final = pickle.loads(res)

print("The common nrs found in both arrays : ", end=' ')
print(res_final)
s.close()
