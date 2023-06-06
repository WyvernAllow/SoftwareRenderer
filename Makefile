CC := $(CC)
CFLAGS := -Wall -Werror -std=c99
LDFLAGS := -lm -lSDL2
TARGET := software-renderer

SRCS := src/main.c src/graphics.c

# Directory for object files
OBJ_DIR := bin

# Object files
OBJS := $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.c=.o)))

# Include directories
INCLUDES := 

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)