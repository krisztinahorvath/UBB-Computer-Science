import threading
import socket

IP = "0.0.0.0"
PORT = 1234
BYTES = 4096
ADDRESS = (IP, PORT)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDRESS)


def handleClient(client, address):
    end = 0

    while end != 1:
        clientMessage = client.recv(BYTES).decode("utf-8")

        print(f"Client: {clientMessage}")


    client.close()


def sendToClient(client, address):
    end = 0
    while end != 1:
        serverMessage = input("Server: ")
        serverMessage = serverMessage.encode("utf-8")
        client.send(serverMessage)



def main():
    server.listen()
    while True:
        client, address = server.accept()
        thread = threading.Thread(target=handleClient, args=(client, address))
        thread.start()

        thread1 = threading.Thread(target=sendToClient, args=(client, address))
        thread1.start()


main()
