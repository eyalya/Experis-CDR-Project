CC = g++

CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))

CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra

CFLAGS += -pthread

CXXFLAGS = $(CFLAGS) 

CXXFLAGS += -std=c++03 

CXXFLAGS += -O0

# LDFLAGS += 

# LDLIBS += 

#INC_DIRS += ../../include/inl

INC_DIRS += ../../../include ../../include

#INC_DIRS += ../../../advcpp/include

#SOURCES  = $(wildcard ../source/*.cpp)

SOURCES += ../../source/condVar.cpp 

#SOURCES += ../../source/mutex.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = waitableQueueTest

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
