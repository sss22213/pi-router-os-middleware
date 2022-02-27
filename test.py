import socket
import sys
import json
import time

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = 'server.socket'
sock.connect(server_address)

http_package = {}
http_package["Method"] = "GET"
http_package["Router"] = "/"
http_package["Content-Type"] = "application/json"
http_package["Content"] = json.dumps({"name":1})
http_package["Content-Length"] = str(len(http_package["Content"]))


buf = "%s %s HTTP/1.1\n" % (http_package["Method"], http_package["Router"])
buf += "Content-Type: %s\n" % (http_package["Content-Type"])
buf += "Content-Length: %s\n" % (http_package["Content-Length"])
buf += "\n"
buf += "%s\n" % (http_package["Content"])

'''
Method
Content-Type
Content-Length
'''

sock.sendall(bytes(buf, 'utf-8'))

data = sock.recv(1)

sock.close()
