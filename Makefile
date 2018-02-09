CFLAGS=-g -Wall
INCLUDE=-I/usr/local/include -I/usr/local/include/libxml2
LDFLAGS=-L/usr/local/lib
LDLIBS=-lcurl -lxml2 -lz -lm -ldl
SOURCES=src/feader.c
OUTPUT=-o out/feader


all: clean setup build run
	
	
build: $(SOURCES)
	gcc $(CFLAGS) $(OUTPUT) $(INCLUDE) $(LDFLAGS) $(SOURCES) $(LDLIBS)

clean:
	rm -rf out

setup:
	mkdir out

run:
	./out/feader http://cave.wbrawner.com/feed.xml
