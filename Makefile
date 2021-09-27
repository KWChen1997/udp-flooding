export PATH := /etc/xcompile/mipsel/bin:$(PATH)
CC = gcc
MIPS = mipsel-cc
SRC = $(wildcard *.c)
PROG = nems.x86

all:$(PROG) nems.mpsl

$(PROG):$(SRC)
	$(CC) -g -Wall -o $@ $^

nems.mpsl:$(SRC)
	$(MIPS) -o $@ $^

clean:
	rm $(PROG) nems.mpsl
