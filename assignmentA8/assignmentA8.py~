import socket
import os

def name_to_addr():
    try:
        print('Address : ',socket.gethostbyname(input('Enter Name of Host    : \n> ')))
    except Exception as e:
        print(e)

def addr_to_name():
    try:
        print('Name    : ',socket.gethostbyaddr(input('Enter address of Host : \n> ')))
    except Exception as e:
        print(e)


def nslookup():
    try:
        string = input('Enter URL / IP address : ')
        os.system('nslookup ' + string)
    except Exception as e:
        print(e)


if __name__ == '__main__' :
    while True:
        choice = input('\n\n\nEnter choice\n1 : Name to Address\n2 : Address to Name\n3 : NSLOOKUP\n4 : Exit\n> ')
        if choice == '1':
            name_to_addr()
        elif choice == '2':
            addr_to_name()
        elif choice == '3':
            nslookup()
        else:
            break
