# Makefile for Assignment 5: FIFO server and client

# Compiler
CC = gcc
# Flags
CFLAGS = -Wall -std=gnu99 -pedantic
# Source files
SRCS = $(wildcard *.c)
# Object files
OBJS = $(SRCS:.c=.o)
# Arguments
ARGS = test_urls.txt 1

# Server executable name
EXEC = kvstore
# Client executable name
EXEC2 = kvclient

# Default target
all: $(EXEC) $(EXEC2)

# Executable target: server (excluding client.c and client.h)
$(EXEC): $(filter-out kvclient.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

# Executable target: client (excluding server.c and server.h)
$(EXEC2): $(filter-out kvstore.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

# Clean target
clean:
	rm -f $(EXEC) $(EXEC2) $(OBJS)
