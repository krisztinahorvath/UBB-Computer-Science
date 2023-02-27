# 2.   A client sends to the server a string. The server returns the count of spaces in the string.

import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.1.4", 7777))
msg="he l l o"
byt=msg.encode()
s.send(byt)

s.close()