TARGET = interpreter.out

CFLAGS  = -std=c99
CFLAGS += -Wall -Wextra -pedantic

SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: default all debug release clean run memtest

default: debug
all: default

debug: clean
debug: CFLAGS += -DDEBUG_BUILD -g
debug: $(TARGET)

release: clean
release: CFLAGS += -O2
release: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

run: default
	./$(TARGET)

memtest: default
	valgrind --leak-check=full ./$(TARGET)
