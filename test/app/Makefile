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

#INC_DIRS += ../include

INC_DIRS += ../../../include ../../include ../../include/inl

INC_DIRS += ../../../cpp/inc

SOURCES  = ./$(TARGET).cpp
SOURCES += $(wildcard ../../source/*.cpp)
//SOURCES  = ../../source/TCP_client.cpp ../../source/socket.cpp ../../source/condVar.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = app_test

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS) -lpthread

clean:

	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:

	valgrind --leak-check=full ./$(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)
