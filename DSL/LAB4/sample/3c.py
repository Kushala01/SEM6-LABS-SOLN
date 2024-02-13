#WAP where client can send a message to the server and the server an receive the message and send, or echo, it back to the client
import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=6464
s.connect((host,port))
msg='hello bitchrs'
s.sendall(bytearray(msg,'utf-8'))
data=s.recv(1024)
print('msg from server : ',data.decode())
s.close()