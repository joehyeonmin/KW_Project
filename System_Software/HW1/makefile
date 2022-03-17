all : client server
client : LpcProxy.c testcase.c LpcProxy.h Lpc.h
	gcc LpcProxy.c testcase.c -o client
server : LpcStub.c Server.c Lpc.h LpcStub.h
	gcc LpcStub.c Server.c -o server

