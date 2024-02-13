import socket
s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host=socket.gethostname()
port=6565
s.bind((host,port))
while True:
    print('waiting for client')
    cli, addr=s.recvfrom(1024)
    print('recieved message from: ', cli.decode(), 'from', addr)
    if not cli: break
s.close()