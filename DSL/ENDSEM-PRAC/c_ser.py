import socket
import datetime

def initiateClockServer():
    s = socket.socket()
    print("Socket successfully created")
    
    port = 9014
    s.bind(('', port))
    
    s.listen(5)
    print("Socket is listening...")

    while True:
        connection, address = s.accept()
        print('Server connected to', address)
        connection.send(str(datetime.datetime.now()).encode())
        connection.close()

if __name__== '__main__':
    initiateClockServer()