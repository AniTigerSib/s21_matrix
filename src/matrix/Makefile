CC := gcc
# CFLAGS := -Wall -Wextra -Werror -std=c11
CFLAGS := 
LDFLAGS := -lm

SOURCEDIR := .
BUILDDIR := ../build
TARGET := s21_matrix.a
TARGETDIR := ..
SOURCES := 
GCOVDIR := ../gcov
GCOVFLAGS := --coverage

SOURCES += $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(patsubst %.c,%.o,$(foreach file,$(SOURCES),$(file)))

all: $(TARGET)
$(TARGET): $(OBJECTS)
	ar rcs $(TARGETDIR)/$@ $(foreach object,$^,$(BUILDDIR)/$(notdir $(object)))

dbg: CFLAGS += -fsanitize=address -g
dbg: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(foreach object,$@,$(BUILDDIR)/$(notdir $(object)))

clean:
	@rm -rf $(BUILDDIR)/*
	@rm $(TARGETDIR)/$(TARGET)
rebuild: clean all

clang-n:
	clang-format --style=google -n $(SOURCEDIR)/*.c
	clang-format --style=google -n $(SOURCEDIR)/*.h
clang-i:
	clang-format --style=google -i $(SOURCEDIR)/*.c
	clang-format --style=google -i $(SOURCEDIR)/*.h

gcov_report: CFLAGS += --coverage
gcov_report: $(TARGET)