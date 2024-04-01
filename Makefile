#Headers
HEADERS = LsCommands.h

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Werror

# Source files
SRCS = UnixLs.c LsCommands.c

# Object files
OBJS = UnixLs.o LsCommands.o

# Executable
TARGET = UnixLs

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compilation rule for UnixLs.c
UnixLs.o: UnixLs.c 
	$(CC) $(CFLAGS) -c UnixLs.c -o UnixLs.o

# Compilation rule for LsCommands.c
LsCommands.o: LsCommands.c $(HEADERS) 
	$(CC) $(CFLAGS) -c LsCommands.c -o LsCommands.o

clean:
	rm -f $(OBJS) $(TARGET)