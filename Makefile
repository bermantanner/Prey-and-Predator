CXX = g++

# Source files
SRC = preyandpredator.cpp Simulation.cpp Organism.cpp Bird.cpp Worm.cpp

# Include directory for SFML headers
SFML_INCLUDE = ./include

# Library directory for SFML dynamic libraries
SFML_LIB = ./lib

# Compilation flags
CXXFLAGS = -I$(SFML_INCLUDE) -fsanitize=address -g

# Linking flags
LDFLAGS = -L$(SFML_LIB) -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network

# Output target
TARGET = preyandpredator

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET) $(LDFLAGS)

# Clean rule to remove the binary
clean:
	rm -f $(TARGET)
