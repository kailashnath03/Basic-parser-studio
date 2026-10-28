# BASIC Parser Studio Makefile
# Supports Linux, macOS, and Windows (MinGW / WinFlexBison)

CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -O2

# Detect flex / win_flex
ifeq ($(OS),Windows_NT)
    FLEX ?= $(shell where win_flex 2>nul || echo flex)
    BISON ?= $(shell where win_bison 2>nul || echo bison)
    TARGET = basic_parser.exe
    RM = del /Q /F
else
    FLEX ?= flex
    BISON ?= bison
    TARGET = basic_parser
    RM = rm -f
endif

SRCS = main.c ast.c parser.tab.c lex.yy.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): parser.tab.c lex.yy.c ast.c main.c
	$(CC) $(CFLAGS) -o $@ main.c ast.c parser.tab.c lex.yy.c

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d -Wall parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

test: $(TARGET)
	node run_tests.js

clean:
	-$(RM) parser.tab.c parser.tab.h lex.yy.c parser.output $(TARGET) *.o 2>nul || true
