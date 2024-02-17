#WAP to create TCP time server in Python
import socket
import time
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host=socket.gethostname()
port=4545
s.bind((host,port))
s.listen(5)
while True:
    clientSock, addr=s.accept()
    print('got a connection from: ',addr)
    currentTime=time.ctime(time.time())
    clientSock.send(currentTime.encode('ascii'))
    clientSock.close()