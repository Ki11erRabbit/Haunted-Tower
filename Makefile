CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG

SRCPATH = src
OUTPATH = output
SOURCES = main.c
OBJECTS = $(OUTPATH)/$(patsub %.c,%.o,$(SRCPATH)/$(SOURCES))
TARGET = $(OUTPATH)/background.gb

.PHONY: hauntedtower.gb

hauntedtower.gb: OBJECTS
	$(CC) $(CFLAGS) -o $@ $^

%.o: SOURCES
	mkdir $(OUTPATH)
	$(CC) $(CFLAGS) -c -o $<


clean: OBJECTS %.gb
	rm $^
