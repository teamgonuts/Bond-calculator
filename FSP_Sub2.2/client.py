#!/usr/bin/python

import socket
import os
import sys


#==============SPAWN SERVER=====================#

'''
def run(program, *args):
    pid = os.fork()
    if not pid:
       os.execvp(program, (program,) + args)
    
#return os.wait()[0]


run("sh", "run.sh")


#==============CODE===========================#

'''
HOST = socket.gethostname()
PORT = 0x1234
MSGSIZE = 8192
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
# done = False


#Server doesn't need to handle close
var = "go";
s.send(var)
data = s.recv(MSGSIZE)

print 'Received response from the server of:', repr(data)

s.close()