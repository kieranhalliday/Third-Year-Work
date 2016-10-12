from socket import *
import time

serverName='127.0.0.1'
serverPort=12000
clientSocket=socket(AF_INET,SOCK_DGRAM)
clientSocket.settimeout(1)
sequence_number=0

while sequence_number<10:
 try:
    sequence_number=sequence_number+1
    message='Ping Number: '+str(sequence_number)
    start=time.time()
    clientSocket.sendto(message,(serverName,serverPort))
    data, server = clientSocket.recvfrom(1024)
    print data+' received, RTT='+str(time.time()-start)
 except timeout:
    print 'Request timed out'
clientSocket.close()

