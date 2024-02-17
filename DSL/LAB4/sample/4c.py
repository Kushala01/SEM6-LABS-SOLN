#WAP to create TCP time server in Python
import socket
import time
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=4545
s.connect((host,port))
time=s.recv(1024)
print('time sent fromt he ser ver is ',time)
s.close()