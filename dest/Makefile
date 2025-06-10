# Compiler
CXX = g++ 

# Compiler flags
CXXFLAGS = -std=c++20 -I"include" -g -DALGORITHM_EXPORTS -m64

# Linker flags
LDFLAGS = -L"lib" -lAlgorithm

# Target executable
TARGET = AlgorithmAppTestRef.exe

# Source file
SRCS = AlgorithmAppTestRef.cpp

# Object file
OBJS = AlgorithmAppTestRef.o

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile the source file into an object file
$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS) -o $(OBJS)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)