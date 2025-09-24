CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = chess

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean debug

all: $(TARGET)

debug: CFLAGS += -g
debug: clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

