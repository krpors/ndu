CFLAGS = -Wall -Wextra -ggdb -MP -MMD -D_XOPEN_SOURCE=500
objects := ndu.o fs.o

all: ndu

ndu: $(objects)

clean:
	$(RM) $(objects:.o=.d) $(objects) ndu

.PHONY: clean

-include $(objects:.o=.d)
