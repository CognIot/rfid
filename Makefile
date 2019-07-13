

CC = gcc
CFLAGS = -gdwarf-3 -Og -Wall
CFLAGS += -D BUILD_VERSION="\"$(shell git describe --dirty --always)\""	\
		-D BUILD_DATE="\"$(shell date '+%Y-%m-%d %H:%M:%S')\""


READER_BIN = reader
READER_SRCS = src/reader.c 

READER_LIBS = ../libcogniot-rfid/bin/libcogniot-rfid.a -lwiringPi 

TARGETS = $(READER_BIN) 

all: $(TARGETS)

reader:
	$(CC) $(CFLAGS) $(READER_SRCS) -o $(READER_BIN) $(READER_LIBS)



clean:
	rm -fv *.o $(TARGETS)
