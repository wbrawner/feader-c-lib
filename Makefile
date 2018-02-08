CFLAGS=-g -Wall
INCLUDE=-I/usr/local/include 
LDFLAGS=-L/usr/local/lib
LDLIBS=-lcurl 
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
	./out/feader
