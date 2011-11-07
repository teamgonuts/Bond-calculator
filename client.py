#!/usr/bin/python
import socket

#===============FUNCTIONS=====================#
def legalResponse(var):
    if(var == 'load' or \
       var == 'hedge30yr' or \
       var == 'yield+100bp' or \
       var == 'yield-100bp' or \
       var == 'close'):
        return True
    else:
        return False


#==============CODE===========================#
HOST = socket.gethostname()
PORT = 0x1234
MSGSIZE = 8192
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

done = False;
#Server doesn't need to handle close
while(not done):
    #getting user input
    var = raw_input("Enter Server Command: ")
    while(not legalResponse(var)):
        var = raw_input("Invalid Command Error!\nEnter Server Command: ")
        
    if(var == 'close'):
        done = True
    else:
        s.send(var)
        data = s.recv(MSGSIZE)
        print 'Received response from the server of:', repr(data)

s.close()



    
