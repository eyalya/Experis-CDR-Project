CC = g++

CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))

CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra

CXXFLAGS = $(CFLAGS) 

CXXFLAGS += -std=c++03 

CXXFLAGS += -O0

LDFLAGS += -pthread

# LDLIBS += 

#INC_DIRS += ../include

INC_DIRS += ../../../include ../../include

INC_DIRS += ../../../cpp/inc

SOURCES  = $(wildcard ../../source/*.cpp)

#SOURCES += ../../source/UI.cpp ../../source/ds_container.cpp 

#SOURCES += ../../source/query.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = queryTest

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:

	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:

	valgrind --leak-check=full ./$(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)
