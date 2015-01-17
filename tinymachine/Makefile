CC = gcc
CFLAGS = -w

all: tm ftm

###################### Tiny Machine ############################
tm: tm.c
	$(CC) $(CFLAGS) tm.c -o tm

###################### Fast Tiny Machine ############################
ftm: ftm.c
	$(CC) $(CFLAGS) ftm.c -o ftm

###################### Clean up ################################
clean:  
	-rm tm ftm # Tiny Machine
