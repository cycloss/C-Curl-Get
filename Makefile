

test: basicCall
	./basicCall 'http://jsonplaceholder.typicode.com/posts/1'

basicCall: basicCall.c basicCall.h
	cd "/Users/ted/Developer/C/CApi/"
	gcc -Wall basicCall.c -o basicCall -lcurl