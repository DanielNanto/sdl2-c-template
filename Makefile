CC  = gcc
CXX = g++
LD  = g++
PKGCONFIG_LIBS = sdl2 SDL2_image SDL2_ttf SDL2_mixer
CFLAGS = `pkg-config --cflags $(PKGCONFIG_LIBS)` -MMD -MP -O2 -g -Wall -Wextra
LFLAGS = `pkg-config --libs $(PKGCONFIG_LIBS)`
TARGET = joonko-sdl2-template

SOURCES = \
	src/global.c \
	src/main.c

BUILDIR = build
OBJECTS += $(addprefix $(BUILDIR)/,$(addsuffix .o,$(basename $(SOURCES))))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " LD " $@
	@$(LD) -o $(TARGET) $(OBJECTS) $(LFLAGS)

$(BUILDIR)/%.o: %.c
	@echo " CC " $<
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS)

$(BUILDIR)/%.o: %.cpp
	@echo " CC " $@
	@mkdir -p $(dir $@)
	@$(CXX) -o $@ -c $< $(CFLAGS)

-include $(OBJECTS:.o=.d)

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(TARGET) $(TARGET).exe
	rm -rf build

.PHONY: all clean
