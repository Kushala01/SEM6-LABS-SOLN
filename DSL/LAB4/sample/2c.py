import socket
s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host=socket.gethostname()
port=6565
msg='heelo hell-no'
heel=''
s.sendto(msg.encode(), (host,port))
s.sendto(heel.encode(),(host,port))
s.close()