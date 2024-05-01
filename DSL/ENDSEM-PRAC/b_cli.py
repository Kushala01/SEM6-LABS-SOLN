from timeit import default_timer as timer
from dateutil import parser
import threading
import datetime
import socket
import time

port = 8001

def startSendingTime(slave_client):
    while True:
        slave_client.send(str(datetime.datetime.now()).encode())
        print("Recent time sent successfully", end="\n\n")
        time.sleep(5)

def startReceivingTime(slave_client):
    while True:
        synchronized_time = parser.parse(slave_client.recv(1024).decode())
        print("Synchronized time at the client is: " + str(synchronized_time), end="\n\n")

def initiateSlaveClient(port=port):
    slave_client = socket.socket()
    slave_client.connect(('127.0.0.1', port))
    print("Starting to receive time from server\n")
    
    send_time_thread = threading.Thread(
        target=startSendingTime,
        args=(slave_client,)
    )
    send_time_thread.start()
    print("Starting to receive synchronized time from server\n")
    
    receive_time_thread = threading.Thread(
        target=startReceivingTime,
        args=(slave_client,)
    )
    receive_time_thread.start()

if __name__ == '__main__':
    initiateSlaveClient(port=port)