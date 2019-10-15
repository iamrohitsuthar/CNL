import socket
import threading
import sys

serverip = '127.0.0.1'
clientListServer = (serverip,5000)
matchServer = (serverip,5001)
charServerAddress = None

socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

your_name = None


def initiate_chat():
    global your_name
    global charServerAddress
    global serverip

    your_name = bytes(input('Enter your name: '), encoding='UTF-8')
    socket.sendto(your_name, clientListServer)

    chatwith = input('Enter name of user to chat with : ')
    if chatwith == '-':
        print('In pairing')
    else:
        print('in IF')
        socket.sendto(bytes(chatwith,encoding='UTF-8') , matchServer)
    portno , _ = socket.recvfrom(4096)
    charServerAddress = (serverip,int(portno.decode(encoding='UTF-8')))
    print(charServerAddress)
    print("Initiated Successfully")

def receive_message():

    while True:

        message_in, _ = socket.recvfrom(4096)
        print('{}'.format(message_in.decode(encoding='UTF-8')))


def send_message():
    global charServerAddress
    while True:

        message_out = bytes(input('>'), encoding='UTF-8')
        socket.sendto(your_name + bytes(':', encoding='UTF-8') + message_out, charServerAddress)


def main_client_loop():

    initiate_chat()

    thread1 = threading.Thread(target=send_message, args=())
    thread2 = threading.Thread(target=receive_message, args=())

    thread1.start()
    thread2.start()


if __name__ == '__main__':
    main_client_loop()