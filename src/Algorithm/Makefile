# Compiler
CXX = "C:/msys64/ucrt64/bin/g++.exe"

# Compiler flags
CXXFLAGS = -shared -static -static-libgcc -static-libstdc++ -fdiagnostics-color=always -g -Iinclude -Wl,--subsystem,windows -DALGORITHM_EXPORTS -m64

# Source files
SRCS = Algorithm.cpp \
       include/Dijkstra.cpp \
       include/RegExManager.cpp \
       include/SortBenchMark.cpp \
       include/Sudoku.cpp \
       include/TFileManager.cpp

# Output file
TARGET = Algorithm.dll

# Build rule
$(TARGET): $(SRCS)
	@echo "Building $(TARGET)..."
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
.PHONY: clean

clean:
	del /F /Q $(TARGET)