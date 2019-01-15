CFLAGS = -Wall -Wextra -MP -MMD -D_XOPEN_SOURCE=500
LDLIBS = -lncurses
objects := ndu.o fs.o

all: ndu

ndu: $(objects)

debug: all
debug: CPPFLAGS += -UNDEBUG # undefine the NDEBUG flag to allow assert().
debug: CFLAGS += -ggdb -Og
debug: LDFLAGS += -ggdb -Og

clean:
	$(RM) $(objects:.o=.d) $(objects) ndu

.PHONY: clean

-include $(objects:.o=.d)
