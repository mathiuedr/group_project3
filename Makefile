CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm
BUILD_DIR = ../build
TARGET_Q1 = $(BUILD_DIR)/Quest_1

SRCS_Q1 = stack.c main.c graph.c parser.c rpn.c utils.c
OBJS_Q1 = $(SRCS_Q1:.c=.o)

all: $(TARGET_Q1) $(TARGET_Q2)

$(TARGET_Q1): $(OBJS_Q1) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OBJS_Q1) $(OBJS_Q2)

rebuild: clean all