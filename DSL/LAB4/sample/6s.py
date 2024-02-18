#Forking/ Threading (Concurrent Server)
import socket
import os  # Importing the os module for miscellaneous operating system interfaces
from _thread import * # Importing the _thread module for multi-threading support
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host=socket.gethostname()
port=4343
threadCount=0
try:
    s.bind((host,port))
except socket.error as e:
    print(str(e))
print('waiting for a connection')
s.listen(4)

#thread program
def threaded_client(connection):
    welcomeMsg='Welcome to the server side!'
    connection.sendall(welcomeMsg.encode())
    while True:
        data=connection.recv(1024)
        if not data:
            break
        reply='server says: '+data.decode()
        connection.sendall(reply.encode())
    connection.close()

#main loop
while True:
    cli, addr=s.accept()
    print('connected to: ',addr)
    start_new_thread(threaded_client,(cli,))
    threadCount+=1
    print('now thread count is: ',threadCount)
s.close()