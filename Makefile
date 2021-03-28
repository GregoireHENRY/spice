CC := gcc
AR := ar
TARGET := spicetools
LIB := spicetools

# Directories
SOURCES_DIRECTORY := src
HEADERS_DIRECTORY := includes \
					../cspice/include
OBJECTS_DIRECTORY := obj
LIBRARY_DIRECTORY := lib
ADDITIONALS := ../cspice/lib/libcspice.a
ADDITIONAL_LIBRARIES := m

# Flags
LFLAGS := -O3 \
	      -Wall \
		  -Wextra \
		  -Wformat \
		  -Wmissing-declarations \
		  -pedantic \
		  --std=c99
RFLAGS :=
AR_LFLAGS := -crs

# Apply setup
SOURCES := $(shell find $(SOURCES_DIRECTORY) -type f -name *.c)
OBJECTS := $(patsubst $(SOURCES_DIRECTORY)/%,$(OBJECTS_DIRECTORY)/%,$(SOURCES:.c=.o))
INCLUDES := $(addprefix -I, $(HEADERS_DIRECTORY))
LIBRARIES := $(addprefix -l, $(ADDITIONAL_LIBRARIES))
LIBFLAGS := $(LIBRARIES) $(INCLUDES)

# Main
.PHONY: all clean test debug directories
all: directories library

clean:
	rm -rf $(OBJECTS_DIRECTORY)

test:

debug:
	$(info ${OBJECTS})

# Create directories
directories:
		mkdir -p $(OBJECTS_DIRECTORY)

# Compile
$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c
	$(CC) $(LFLAGS) -o $@ -c $< $(LIBFLAGS) $(RFLAGS)

# Link objects
binary: $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TARGET) $^ $(ADDITIONALS) $(LIBFLAGS) $(RFLAGS)

# Link objects
library: $(OBJECTS)
	$(AR) $(AR_LFLAGS) $(LIBRARY_DIRECTORY)/lib$(LIB).a $^
