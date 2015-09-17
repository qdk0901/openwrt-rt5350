CC = gcc

XX = g++

CFLAGS = -Wall -O

TARGET = dsp_test

%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	 $(XX) $(CFLAGS) -c $< -o $@

SOURCES = \
    dsp_test.c
	
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))


$(TARGET) : $(OBJS)
	 $(CC) $(OBJS) -o $(TARGET) $(LDFLAGS) -ldsp -lspi

clean:
	rm *.o dsp_test
	