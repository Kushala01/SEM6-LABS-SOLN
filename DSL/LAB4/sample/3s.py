#WAP where client can send a message to the server and the server an receive the message and send, or echo, it back to the client
import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=6464
s.bind((host,port))
s.listen(3)
cli,addr=s.accept()
while True:
    data=cli.recv(1024)
    if data:
        print('client : ',data.decode())
        data=input("enter msg tot he client")
    if not data:
        break
    cli.sendall(bytearray(data,'utf-8'))
cli.close()