CC=gcc
CFLAGS=-g -Wall -Werror
BFLAGS = -lm

MAIN=exec
SRCS=q17.c bblib.c
OBJS=$(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(BFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : launch
launch : $(MAIN)
	./$(MAIN)

.PHONY : clean
clean:
	rm -f $(MAIN) *.o core
