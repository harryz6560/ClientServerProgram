# Client Server File Sharing Program
This program implements a client-server system for file sharing, where each client uploads files to a server for storage and distribution to other clients. The program can be run as a server or a client.

Running the Program
To run the program as a server, use the command:

$ a2p2 -s

To run the program as a client, use the command:

$ a2p2 -c idNumber inputFile

Where idNumber is a unique identifier for the client in the range [1, NCLIENT], and inputFile is the file containing the work to be done by the client.

The server can serve at most NCLIENT = 3 clients. The server is assigned idNumber = 0.

# Input File Format
The input file is shared among all clients and has the following format:

A line starting with # is a comment line (skipped).

Empty lines are skipped.

A line specifies a command line whose format and meaning matches one of the following cases:

idNumber (put|get|delete) objectName: The client with the specified idNumber sends to the server the specified get, put, or delete request of the named object. An object name has at most MAXWORD = 32 characters.
idNumber gtime: The client with the specified idNumber sends to the server a get time request.
idNumber delay x: The client with the specified idNumber delays reading and processing subsequent lines of the input file for an interval of x milliseconds.
idNumber quit: The client with the specified idNumber terminates normally.

# Packet Types
Communication in the system uses messages stored in formatted packets. Each packet has a type and carries a (possibly empty) message. The following packet types are supported:

PUT, GET, and DELETE: For a specified object name, a client executes a get, put, or delete command by sending a packet of the corresponding type, where the message specifies the object name. An error condition arises at the server when the client's request asks for doing one of the following:

-Getting a non-existing object.

-Putting an object that already exists.

-Deleting an object owned by another client.

GTIME and TIME: A client processes a get server's time command (gtime) by sending a GTIME packet (with an empty message). The server replies by sending a TIME packet where the message contains the time in seconds (a real number) since the server started operation.

OK and ERROR: The server replies with an OK packet if the received request is processed successfully. Else, the server replies with an ERROR packet with a suitable error description in the message part.

# Overview
The program is a client-server model with multiple clients and a server, communicating with each other through the use of FIFOs. Each client is assigned a unique idNumber and reads commands specific to its idNumber from an input file. The client performs a number of iterations, reading a text line from the input file in each iteration, and executing the specified command only if the client's idNumber matches the one specified on the line. The server uses I/O multiplexing to handle I/O from the keyboard and the FIFOs in a non-blocking manner.

# Client commands:
put <object_name>: Sends a packet to the server to store an object with the specified name.

get <object_name>: Sends a packet to the server to retrieve the object with the specified name.

delete <object_name>: Sends a packet to the server to delete the object with the specified name.

gtime <object_name>: Sends a packet to the server to retrieve the creation time of the object with the specified name.

delay <delay_time>: Pauses the client's operation for the specified amount of time.

quit: Causes the client to terminate normally and exit to the shell.

# Server commands:
list: Writes the stored information about the objects (the idNumber of the owning client and the object name) to the server terminal window.

quit: Exits the server program normally.

# Logging
The program will print information about all transmitted and received packets, as well as when the client enters and exits a delay period. This information will be printed to the client and server terminal windows.
