#Write a TCP chat server in python using socket programming.
import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=3434
s.connect((host,port))
print('waiting for client')
name=input(str('enter your name'))
s.send(name.encode('utf-8'))
cliName=s.recv(1024)
cliName.decode()
print(cliName,'has entered the chat room \n enter [e] to exit the chat\n')
while True:
    msg=s.recv(1024)
    msg=msg.decode()
    print(cliName,':',msg)
    msg=input(str("ME :"))
    if msg=='[e]':
        msg='client wants to leave bitcg'
        s.send(msg.encode())
        break
    s.send(msg.encode())
s.close()