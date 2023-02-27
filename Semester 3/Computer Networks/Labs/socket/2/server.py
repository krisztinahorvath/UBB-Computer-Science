# 2.   A client sends to the server a string. The server returns the count of spaces in the string.

import socket 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

conn, addr = s.accept()

print("Connected by ", end=' ')
print(addr)

data = conn.recv(4096)
data.decode()

print(data)

count = 0
for i in data:
    if i == 32:
        count = count + 1

print("count = ", end=' ')
print(count)
conn.close()
