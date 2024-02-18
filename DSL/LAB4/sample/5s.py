#Write a TCP chat server in python using socket programming.
import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=3434
s.bind((host,port))
print('waiting for client')
s.listen()
cliSock, addr=s.accept()
print('got a conncection from ',addr)
cliName=cliSock.recv(1024)
cliName.decode()
print(cliName,'has entered the chat room \n enter [e] to exit the chat\n')
name=input(str('enter your name'))
cliSock.send(name.encode('utf-8'))
while True:
    msg=input(str("ME: "))
    if msg=='[e]':
        msg='server has left the chat'
        cliSock.sendall(msg.encode())
        break
    cliSock.send(msg.encode())
    msg=cliSock.recv(1024)
    msg=msg.decode()
    print(cliName,': ',msg)
s.close()