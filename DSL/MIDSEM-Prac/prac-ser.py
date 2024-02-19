import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
host=socket.gethostname()
port=4343
s.bind((host,port))
while True:
    msg,addr=s.recvfrom(1024)
    if not msg:
        break
    print('cli says: ',msg.decode())
    sendmsg=input('send your msg')
    s.sendto(sendmsg.encode(),addr)
s.close()