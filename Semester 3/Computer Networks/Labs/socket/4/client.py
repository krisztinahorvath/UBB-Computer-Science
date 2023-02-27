# 4.   The client send to the server two sorted array of chars.
# The server will merge sort the two arrays and return the result to the client.

import socket
import pickle
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.1.4", 7777))
a1 = ['a', 'd', 'f']
a2 = ['a', 'b', 'c', 'e']

t = (a1,a2)

byteT = pickle.dumps(t)

s.send(byteT)


merged = s.recv(4096)
finalResult = pickle.loads(merged)
print(finalResult)

s.close()