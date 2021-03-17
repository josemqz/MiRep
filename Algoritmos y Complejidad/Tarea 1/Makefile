CC 		= gcc
CFLAGS 		= -Wall
LDFLAGS		=
OBJFILES	= sorting.o main.o
TARGET 		= main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
