CC      = gcc
CFLAGS  = -g -Wall -Wextra -Wmissing-declarations -std=c99 -pedantic
RM			= rm -f
DAY			= day3

default:
	$(CC) $(CFLAGS) -o $(DAY) $(DAY).c

test:
	./$(DAY) test.txt

solve:
	./$(DAY) challenge.txt

clean:
	$(RM) $(DAY)
