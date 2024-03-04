import socket
def fetchServerClock():
    # Client socket creation
    client_socket = socket.socket()
    # Server port
    server_port = 8011
    # Connect to the Clock Server
    client_socket.connect(('localhost', server_port))
    # Receive server's response
    server_time = client_socket.recv(1024).decode()
    print("Server time:", server_time)
    # Close the connection with the server
    client_socket.close()

# Driver function
if __name__ == '__main__':
    # Trigger the function to fetch server time
    fetchServerClock()