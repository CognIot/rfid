

CC 	= gcc
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
DEBUG	= -O2
CFLAGS  = -Og -Wall
CFLAGS += $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC \
          -D BUILD_VERSION="\"$(shell git describe --dirty --always)\""	\
	      -D BUILD_DATE="\"$(shell date '+%Y-%m-%d %H:%M:%S')\""
	  


READER_BIN = reader
READER_SRCS = src/reader.c 

READER_OBJ = $(READER_SRCS:.c=.o)


READER_LIBS = ./libcogniot-rfid/bin/libcogniot-rfid.a -lwiringPi 

TARGETS = $(READER_BIN) 

all: $(TARGETS)

reader: $(READER_OBJ)
	$(CC) $(CFLAGS) $(READER_SRCS) -o $(READER_BIN) $(READER_LIBS)

.c.o: $(READER_SRCS)
	echo [Compile] $<
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -fv *.o $(TARGETS)
