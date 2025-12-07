CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
OUTPATH = output
SOURCES = main.c noise.c sprites.c map.c
OBJECTS = $(patsubst %.c,$(OUTPATH)/%.o,$(SOURCES))
TARGET = $(OUTPATH)/hauntedtower.gb

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTPATH)/%.o: %.c | $(OUTPATH)
	cd $(OUTPATH) && $(CC) $(CFLAGS) -c ../$<

$(OUTPATH):
	mkdir -p $(OUTPATH)

clean:
	rm -rf $(OUTPATH)
