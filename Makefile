TARGET = example/app

BUILD_DIR = ./build
SOURCE := $(wildcard example/*.cpp) $(wildcard src/*.cpp)

CC = g++
FLAGS = -std=c++11 -Wall
CXXFLAGS = -I$(INCDIR) $(FLAGS)
LDFLAGS = $(FLAGS)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCE))
HEADERS = $(wildcard *.h)

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm $(OBJECTS) $(TARGET)
