#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer

import serial

SER = serial.Serial('/dev/ttyACM0', 9600)

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
    
    #Handler for the GET requests
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()
        # Send the html message
        self.wfile.write("Hello World !")
        print "Yea"
        SER.write('X');
        return
        
class RPiServer:
    def startServer(self, server_address, server_port):
        #Create a web server and define the handler to manage the
        #incoming request
        server = HTTPServer((server_address, server_port), myHandler)
        print 'Started httpserver on port ' , 1040
        
        #Wait forever for incoming http requests
        server.serve_forever()
        
    def terminateServer(self):
        server.socket.close()
