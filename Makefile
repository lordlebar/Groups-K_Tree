CC ?= gcc
CPPFLAGS = -D_GNU_SOURCE
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic

BIN = K_Tree
OBJS = src/$(BIN).o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

check: $(OBJS)
	$(CC) -o $(BIN) $(OBJS)
	./K_Tree

clean:
	$(RM) $(BIN) $(OBJS)
	$(RM) -rf src/K_Tree.dSYM
