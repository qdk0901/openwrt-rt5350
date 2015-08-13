CC = gcc

XX = g++
CFLAGS = -Wall -O

TARGET = atest

%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	 $(XX) $(CFLAGS) -c $< -o $@

SOURCES = \
	pcm.c \
    atest.c
	
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))


$(TARGET) : $(OBJS)
	 $(CC) $(OBJS) -o $(TARGET) -lm
	 chmod a+x $(TARGET)

clean:
	rm *.o atest
	