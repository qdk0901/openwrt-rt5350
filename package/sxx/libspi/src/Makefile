CC = gcc

XX = g++

CFLAGS = -fPIC -Wall -Wextra -O2 -g

TARGET = libspi.so

%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	 $(XX) $(CFLAGS) -c $< -o $@

SOURCES = \
    libspi.c
	
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))


$(TARGET) : $(OBJS)
	$(CC) -shared $(OBJS) -o $(TARGET)

clean:
	rm *.o libspi.so
	