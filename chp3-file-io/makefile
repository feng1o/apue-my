SRC = myfile
CC = gcc
CFLAGS = -Wall -g
all:$(SRC) 
%.o : %.c 
	$(CC) $(CFLAGS) $< -o  $@ 
	#$(CC) $(CFLAGS) $@.c -o  $@ $(LDFLAGS) $(LDLIBS)

.PHONY:clean
clean:
	rm -f  *.o  $(SRC)
run:
	./$(SRC)
# include $(ROOT)/Make.libapue.inc
