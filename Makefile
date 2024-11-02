CC = gcc
CFLAGS = -Iinclude -Os -s
LDFLAGS = -mwindows -s
LIBS = 
SRCDIR = src
OBJDIR = obj
BINDIR = output
SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET := $(BINDIR)/bouncyerror.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	strip $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

clean_obj:
	rm -rf $(OBJDIR)

.PHONY: all clean