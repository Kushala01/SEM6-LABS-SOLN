#Forking/ Threading (Concurrent Server)
import socket
c=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=4343
try:
    c.connect((host,port))
except socket.error as e:
    print(str(e))
while True:
    send=input("say samething to the server")
    c.sendall(send.encode())
    msg=c.recv(1024)
    if not msg:
        break
    print(msg.decode())
c.close()