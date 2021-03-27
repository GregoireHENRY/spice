CC := gcc
TARGET := spice

# Directories
SOURCES_DIRECTORY := src
INCLUDES_SOURCES := includes \
					${HOME}/sw/cspice/include
OBJECTS_DIRECTORY := obj
ADDITIONALS := ${HOME}/sw/cspice/lib/cspice.a

# Flags
LFLAGS := -O3 \
	      -Wall \
		  -Wextra \
		  -Wformat \
		  -Wmissing-declarations \
		  -pedantic \
		  --std=c99
RFLAGS :=
LIBRARIES := m

# Apply setup
SOURCES := $(shell find $(SOURCES_DIRECTORY) -type f -name *.c)
OBJECTS := $(patsubst $(SOURCES_DIRECTORY)/%,$(OBJECTS_DIRECTORY)/%,$(SOURCES:.c=.o))
INCLUDES := $(addprefix -I, $(INCLUDES_SOURCES))
LIBRARIES := $(addprefix -l, $(LIBRARIES))
LIBFLAGS := $(LIBRARIES) $(INCLUDES)

# Main
.PHONY: all clean test debug directories
all: directories $(TARGET)

clean:
	rm -rf $(OBJECTS_DIRECTORY)

test:

debug:
	$(info ${OBJECTS})

# Create directories
directories:
		mkdir -p $(OBJECTS_DIRECTORY)

# Link objects
$(TARGET): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TARGET) $^ $(ADDITIONALS) $(LIBFLAGS) $(RFLAGS)

# Compile
$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c
	$(CC) $(LFLAGS) -o $@ -c $< $(LIBFLAGS) $(RFLAGS)
