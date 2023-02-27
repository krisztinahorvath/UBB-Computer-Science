# 4. The client send to the server two sorted array of chars.
# The server will merge sort the two arrays and return the result to the client.


import socket
import pickle 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

conn, addr = s.accept()
data = conn.recv(4096)
ar = pickle.loads(data)

a1 = ar[0]
a2=ar[1]
print('Recieved arrays:', end=' ')
print(a1, end=' ')
print(a2)

n1 = len(a1)
n2 = len(a2)

# merge sort of a1 and a2 into a3
a3 = [None]*(n1+n2)
i = 0
j = 0
k = 0

while i < n1 and j < n2:
    if a1[i] < a2[j]:
        a3[k] = a1[i]
        k = k + 1
        i = i + 1
    else:
        a3[k] = a2[j]
        k = k + 1
        j = j + 1

while i < n1:
    a3[k] = a1[i]
    k = k + 1
    i = i + 1

while j < n2:
    a3[k] = a2[j]
    k = k + 1
    j = j + 1

res = pickle.dumps(a3)

conn.send(res)


conn.close()

