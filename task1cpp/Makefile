# Makefile for the first task
NAME = first_program

INCDIR = ./headers/
SRCDIR = ./src/
OBJDIR = ./lib/
BINDIR = ./bin/
TARGET = $(BINDIR)$(NAME)
CC = g++-7
SOURCES = $(shell ls $(SRCDIR))
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS = -O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++

.PHONY: all test clean reset

all: $(TARGET)
$(TARGET): $(OBJECTS:%=$(OBJDIR)%)
	$(CC) -o $@ -g $(CFLAGS) $(OBJECTS:%=$(OBJDIR)%)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -o $@ -c -g $(CFLAGS) -I $(INCDIR) $<

output:
	mkdir output
test: $(TARGET) output
	valgrind ./$(TARGET) 1>output/stdout 2>output/stderr
stderr:
	less output/stderr
stdout:
	less output/stdout
clean:
	rm -rf $(BINDIR)*.dSYM
reset: clean
	rm -rf $(OBJDIR)* $(TARGET) output/*
