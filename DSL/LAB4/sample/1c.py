#tcp
import socket
host=socket.gethostname()
port=6767
s=socket.socket()
s.connect((host,port))
s.sendall(b'wellcome to my ')
print('client is connected to the server and it sent a message to the server')
data=s.recv(1024)
print('This is printing the message received back by the server')
print(repr(data))
s.close()