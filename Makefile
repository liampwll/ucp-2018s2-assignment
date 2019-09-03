.POSIX:
.SUFFIXES:
CC      = gcc
# -fno-builtin-printf is here so we can properly wrap it in the testing program
CFLAGS  = -ansi -pedantic -Wall -Werror -Og -g -fno-builtin-printf
LDFLAGS =
LDLIBS  = -lm

OBJS = build/commands.o build/commands/pattern.o build/effectswrapper.o      \
       build/linkedlist/linkedlist.o build/state.o build/commands/helpers.o  \
       build/commands/rotate.o build/error.o build/main.o                    \
       build/strncasecmp/strncasecmp.o build/effects/effects.o               \
       build/fgetslength/fgetslength.o build/parser.o build/tokeniser.o

NORMAL_OBJS = $(OBJS) build/commands/bg.o build/commands/fg.o                \
             build/commands/draw.o build/commands/move.o

SIMPLE_OBJS = $(OBJS) build/commands/simple_bg.o build/commands/simple_fg.o  \
             build/commands/draw.o build/commands/move.o

SIMPLE_FLAGS = -DTURTLE_SIMPLE

DEBUG_OBJS  = $(OBJS) build/commands/bg.o build/commands/fg.o                \
              build/commands/debug_draw.o build/commands/debug_move.o

DEBUG_FLAGS = -DTURTLE_DEBUG

all: TurtleGraphics TurtleGraphicsSimple TurtleGraphicsDebug

TurtleGraphics: $(NORMAL_OBJS)
	$(CC) $(NORMAL_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

TurtleGraphicsSimple: $(SIMPLE_OBJS)
	$(CC) $(SIMPLE_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

TurtleGraphicsDebug: $(DEBUG_OBJS)
	$(CC) $(DEBUG_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

build/commands.o: src/commands.c src/commands.h src/commands/command.h       \
                  src/error.h src/state.h src/tokeniser.h                    \
                  src/strncasecmp/strncasecmp.h src/commands/bg.h            \
                  src/commands/draw.h src/commands/fg.h                      \
                  src/commands/move.h src/commands/pattern.h                 \
                  src/commands/rotate.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/effectswrapper.o: src/effectswrapper.c src/effectswrapper.h            \
                            src/state.h src/error.h src/config.h             \
                            src/effects/effects.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/error.o: src/error.c src/error.h src/effects/effects.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: src/main.c src/commands/command.h src/error.h src/state.h      \
                 src/tokeniser.h src/config.h src/effectswrapper.h           \
                 src/fgetslength/fgetslength.h src/linkedlist/linkedlist.h   \
                 src/parser.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/parser.o: src/parser.c src/parser.h src/commands/command.h             \
                   src/error.h src/state.h src/tokeniser.h src/commands.h    \
                   src/config.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/state.o: src/state.c src/state.h src/error.h src/effectswrapper.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/tokeniser.o: src/tokeniser.c src/tokeniser.h src/error.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/bg.o: src/commands/bg.c src/commands/bg.h                     \
                        src/commands/command.h src/error.h src/state.h       \
                        src/tokeniser.h src/config.h src/effectswrapper.h    \
                        src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/simple_bg.o: src/commands/bg.c src/commands/bg.h              \
                        src/commands/command.h src/error.h src/state.h       \
                        src/tokeniser.h src/config.h src/effectswrapper.h    \
                        src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) $(SIMPLE_FLAGS) -c $< -o $@

build/commands/draw.o: src/commands/draw.c src/commands/draw.h               \
                          src/commands/command.h src/error.h src/state.h     \
                          src/tokeniser.h src/config.h src/effectswrapper.h  \
                          src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/debug_draw.o: src/commands/draw.c src/commands/draw.h         \
                          src/commands/command.h src/error.h src/state.h     \
                          src/tokeniser.h src/config.h src/effectswrapper.h  \
                          src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

build/commands/fg.o: src/commands/fg.c src/commands/fg.h                     \
                        src/commands/command.h src/error.h src/state.h       \
                        src/tokeniser.h src/config.h src/effectswrapper.h    \
                        src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/simple_fg.o: src/commands/fg.c src/commands/fg.h              \
                        src/commands/command.h src/error.h src/state.h       \
                        src/tokeniser.h src/config.h src/effectswrapper.h    \
                        src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) $(SIMPLE_FLAGS) -c $< -o $@

build/commands/helpers.o: src/commands/helpers.c src/commands/helpers.h      \
                             src/config.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/move.o: src/commands/move.c src/commands/move.h               \
                          src/commands/command.h src/error.h src/state.h     \
                          src/tokeniser.h src/config.h src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/debug_move.o: src/commands/move.c src/commands/move.h         \
                          src/commands/command.h src/error.h src/state.h     \
                          src/tokeniser.h src/config.h src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

build/commands/pattern.o: src/commands/pattern.c src/commands/pattern.h      \
                             src/commands/command.h src/error.h src/state.h  \
                             src/tokeniser.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/commands/rotate.o: src/commands/rotate.c src/commands/rotate.h         \
                            src/commands/command.h src/error.h src/state.h   \
                            src/tokeniser.h src/config.h                     \
                            src/commands/helpers.h
	@mkdir -p build/commands
	$(CC) $(CFLAGS) -c $< -o $@

build/effects/effects.o: src/effects/effects.c src/effects/effects.h
	@mkdir -p build/effects
	$(CC) $(CFLAGS) -c $< -o $@

build/fgetslength/fgetslength.o: src/fgetslength/fgetslength.c
	@mkdir -p build/fgetslength
	$(CC) $(CFLAGS) -c $< -o $@

build/linkedlist/linkedlist.o: src/linkedlist/linkedlist.c                   \
                                  src/linkedlist/linkedlist.h
	@mkdir -p build/linkedlist
	$(CC) $(CFLAGS) -c $< -o $@

build/strncasecmp/strncasecmp.o: src/strncasecmp/strncasecmp.c               \
                                 src/strncasecmp/strncasecmp.h
	@mkdir -p build/strncasecmp
	$(CC) $(CFLAGS) -c $< -o $@

build/test/malloc.o: test/malloc.c
	@mkdir -p build/test
	$(CC) $(CFLAGS) -c $< -o $@

TurtleGraphicsMallocTest: $(NORMAL_OBJS) build/test/malloc.o
	$(CC) $(NORMAL_OBJS) build/test/malloc.o $(LDFLAGS) $(LDLIBS) \
	-Wl,--wrap=malloc,--wrap=main,--wrap=printf,--wrap=fprintf \
	-Wl,--wrap=vfprintf,--wrap=__fprintf_chk,--wrap=__vfprintf_chk \
	-Wl,--wrap=__printf_chk -o $@

TurtleGraphicsSimpleMallocTest: $(SIMPLE_OBJS) build/test/malloc.o
	$(CC) $(NORMAL_OBJS) build/test/malloc.o $(LDFLAGS) $(LDLIBS) \
	-Wl,--wrap=malloc,--wrap=main,--wrap=printf,--wrap=fprintf \
	-Wl,--wrap=vfprintf,--wrap=__fprintf_chk,--wrap=__vfprintf_chk \
	-Wl,--wrap=__printf_chk -o $@

TurtleGraphicsDebugMallocTest: $(DEBUG_OBJS) build/test/malloc.o
	$(CC) $(NORMAL_OBJS) build/test/malloc.o $(LDFLAGS) $(LDLIBS) \
	-Wl,--wrap=malloc,--wrap=main,--wrap=printf,--wrap=fprintf \
	-Wl,--wrap=vfprintf,--wrap=__fprintf_chk,--wrap=__vfprintf_chk \
	-Wl,--wrap=__printf_chk -o $@

check: TurtleGraphicsMallocTest TurtleGraphicsSimpleMallocTest \
       TurtleGraphicsDebugMallocTest
	./test/mallocTest.sh

clean:
	rm -rf TurtleGraphics TurtleGraphicsSimple TurtleGraphicsDebug build \
	TurtleGraphicsMallocTest TurtleGraphicsSimpleMallocTest \
	TurtleGraphicsDebugMallocTest
