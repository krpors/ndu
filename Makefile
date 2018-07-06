CFLAGS = -ggdb
objects := ndu.o

all: ndu

ndu: $(objects)

clean:
	$(RM) $(objects:.o=.d) $(objects) ndu

.PHONY: clean
