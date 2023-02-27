# 1.  A client sends to the server an array of numbers.
# Server returns the sum of the numbers.

import socket 
import pickle 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)
conn, addr = s.accept()
print("Connected by ", end=' ')
print(addr)
data = conn.recv(4096)
ar = pickle.loads(data)
sum=0
for i in ar:
    sum = sum + i
print(sum)

# if not data:
#   break
conn.send(data)
conn.close()
# s.close