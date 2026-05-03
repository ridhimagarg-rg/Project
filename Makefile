CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
BUILD    = build

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, $(BUILD)/%.o, $(SRCS))

all: $(BUILD) minigit

minigit: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	
$(BUILD)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) minigit

.PHONY: all clean