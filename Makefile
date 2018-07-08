CFLAGS = -ggdb -MP -MMD
objects := ndu.o fs.o

all: ndu

ndu: $(objects)

clean:
	$(RM) $(objects:.o=.d) $(objects) ndu

.PHONY: clean

-include $(objects:.o=.d) 
