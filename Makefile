# Define variables
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O2 -I./dat -I./archivos
TARGET = myprogram
SRCS = main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
		./$(TARGET)

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.0: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(TARGET) $(OBJS)