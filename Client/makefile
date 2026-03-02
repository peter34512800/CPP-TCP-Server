# Complier
CXX := clang++

# Complier flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Target
TARGET := main

# Delete target
TARGET_DEL := main

# Source files
SRCS := main.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default rule to build  exec
all: $(TARGET)

# Rule to link object files into the target exec
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile cpp files to o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the exec
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET_DEL) $(OBJS)