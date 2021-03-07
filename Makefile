.DEFAULT_GOAL = basic
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OUT_NAME = curlGet

test: $(OUT_NAME)
	./$(OUT_NAME) 'http://jsonplaceholder.typicode.com/posts/1'

basic: $(SOURCES) $(HEADERS)
	cd "/Users/ted/Developer/C/CApi/"
	gcc -Wall $(SOURCES) -o $(OUT_NAME) -lcurl
	