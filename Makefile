#
# Makefile that builds btest and other helper programs for the CS:APP data lab
# 
CC = gcc
CFLAGS = -O -Wall -m32

all: mm

all-mt: mm-mt

mm: mm.c mm.h 
	$(CC) $(CFLAGS) -o mm mm.c 

mm-mt: mm-mt.c mm-mt.h 
	$(CC) $(CFLAGS) -pthread -o mm-mt mm-mt.c 

clean:
	rm -f *.o mm
