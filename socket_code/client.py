#!/usr/bin/python
import socket

HOST = 'scotts-macbook-pro-17.local'
PORT = 0x1234
MSGSIZE = 8192
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('Hello, world from a python client!')
data = s.recv(MSGSIZE)
s.close()
print 'Received response from the server of:', repr(data)
