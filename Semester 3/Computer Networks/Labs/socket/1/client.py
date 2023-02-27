# 1.  A client sends to the server an array of numbers.
# Server returns the sum of the numbers.

import socket
import pickle
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.1.4", 7777))
arr = [1, 2, 3, 4]
data_string = pickle.dumps(arr)
s.send(data_string)

data = s.recv(4096)
data_arr = pickle.loads(data)
print('Recieved ' + repr(data_arr))
s.close()
