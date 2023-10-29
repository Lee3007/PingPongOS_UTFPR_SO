CC = gcc
CFLAGS = -Wall
SRC = ppos-core-aux.c pingpong-scheduler-srtf.c libppos_static.a
TARGET = pingpongOS

all: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)
