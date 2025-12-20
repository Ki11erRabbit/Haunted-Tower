CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j -Wm-yC -DUSE_SFR_FOR_REG
OUTPATH = output
SOURCES = main.c noise.c sprites.c map.c camera.c
CHARACTER_PNGS = $(wildcard assets/*.png)
CHARACTERS = $(patsubst assets/%.png,characters/%.c,$(CHARACTER_PNGS))
CHARACTER_OBJECTS = $(patsubst characters/%.c,$(OUTPATH)/characters/%.o,$(CHARACTERS))
OBJECTS = $(patsubst %.c,$(OUTPATH)/%.o,$(SOURCES))
TARGET = $(OUTPATH)/hauntedtower.gb

.PHONY: all clean characters

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CHARACTER_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTPATH)/%.o: %.c | $(OUTPATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)/characters/%.o: characters/%.c
	$(CC) $(CFLAGS) -c $< -o $@

characters/%.c: assets/%.png
	mkdir -p characters
	png2asset $< -c $@ -sw 16 -sh 16 -tiles_only

$(OUTPATH):
	mkdir -p $(OUTPATH)/characters

characters: $(CHARACTERS)

clean:
	rm -rf $(OUTPATH)
