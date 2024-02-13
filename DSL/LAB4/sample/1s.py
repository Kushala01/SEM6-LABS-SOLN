import socket
host=socket.gethostname()
port=6767
s=socket.socket()
s.bind((host,port))
s.listen(3)
con, addr=s.accept()
print('got a message from ',addr[0],'(',addr[1],')')
print('thank you for connecting')
while True:
    data=con.recv(1024)
    if not data: break
    con.sendall(data)
print('recicied data and echoed')
con.close()