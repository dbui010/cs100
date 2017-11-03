CC = g++
CC_FLAGS = -Wall -ansi -pedantic -Werror
EXEC = test.out
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
        $(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
        $(CC) -c $(CC_FLAGS) $< -o $@

clean:
        rm -f $(EXEC) $(OBJECTS)

