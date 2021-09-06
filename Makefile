executable = bin/executable.out
objects_dir = bin/objects
source_dir = src

sources = $(wildcard $(source_dir)/*.cpp)
objects = $(sources:$(source_dir)/%.cpp=$(objects_dir)/%.o)
libs = -lsfml-graphics -lsfml-window -lsfml-system

# Compiling project
install: $(objects)
	g++ $(objects) -g $(libs) -o $(executable)

# Building the object files
$(objects_dir)/%.o: $(source_dir)/%.cpp 
	g++ -c $< -o $@

# Cleaning the bin folder
clean:
	rm $(executable) $(objects)

.PHONY: clean
