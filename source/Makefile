################################################################################
# CPT220 - Programming in C
# Study Period 2 2017 Assignment #2 
# Full Name        : Robert Ashton Beardow
# Student Number   : S3641721
# Start up code provided by Paul Miller
################################################################################

# Common headers for both builds
COMMON_HEADERS=reversi_game.h reversi_gameboard.h reversi_gamerules.h \
	reversi_helpers.h reversi_io.h reversi_player.h reversi_score.h \
	reversi_scoreboard.h reversi_shared.h reversi.h

# Common objects for both builds
COMMON_OBJECTS= reversi_game.o reversi_gameboard.o reversi_gamerules.o \
	reversi_helpers.o reversi_io.o reversi_player.o reversi_score.o \
	reversi_scoreboard.o reversi.o

# Array list implementation object files
ARRAY_LIST_OBJECTS=$(COMMON_OBJECTS) reversi_array_list.o

# Linked list implementation object files
LINKED_LIST_OBJECTS=$(COMMON_OBJECTS) reversi_linked_list.o

# C Compiler, compiler, and linker flags
C_COMPILER=gcc
C_COMPILER_FLAGS=-ansi -Wall -pedantic -g
LINKER_FLAGS=
ARRAY_OUTPUT_EXE=reversi_array
LINKED_OUTPUT_EXE=reversi_linked

%.o: %.c
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(DEFINE_FLAGS) -c $<

# Build linked list version of reversi
reversi_linked: DEFINE_FLAGS := -DLinkedList
reversi_linked: clean | $(LINKED_LIST_OBJECTS)
	$(C_COMPILER) $(LINKER_FLAGS) $(LINKED_LIST_OBJECTS) -o $(LINKED_OUTPUT_EXE)

# Build array list version of reversi
reversi_array: DEFINE_FLAGS := -DArrayList
reversi_array: clean | $(ARRAY_LIST_OBJECTS)
	$(C_COMPILER) $(LINKER_FLAGS) $(ARRAY_LIST_OBJECTS) -o $(ARRAY_OUTPUT_EXE)

# Build zip of project
archive:
	zip $(USER) reversi_array_list.c reversi_gamerules.h reversi_player.c \
	reversi_array_list.h  reversi.h reversi_player.h reversi.c \
	reversi_helpers.c reversi_scoreboard.c reversi_gameboard.c \
	reversi_helpers.h reversi_scoreboard.h reversi_gameboard.h \
	reversi_io.c reversi_score.c reversi_game.c reversi_io.h \
	reversi_score.h reversi_game.h reversi_linked_list.c reversi_shared.h \
	reversi_gamerules.c reversi_linked_list.h Makefile reversi_readme.txt

.PHONY:clean
clean:
	rm -f *.o $(OUTPUT_EXE)