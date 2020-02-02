CC = g++ 
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP 

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra 
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++03 
CXXFLAGS += -O0
# LDFLAGS += 
# LDLIBS += 

INC_DIRS += ../../include  ../../inl

SOURCES  = ./$(TARGET).cpp
SOURCES  += $(wildcard ../../src/*.cpp)

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = waitque_test

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS) -lpthread

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:
	valgrind --leak-check=full ./$(TARGET)

valHell:
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)

valDrd:
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)

