SOURCEDIR := ../matrix
SOURCESDIR := .
ALLOCTESTDIR := ../allocator_wrapper
BUILDDIR := ../build
GCOVDIR := ../gcov
LCOVDIR := ../lcov
LOGDIR := ./logs
TARGETDIR := ..

CC := gcc
# ищет заголовочные файлы в этой директории 
CFLAGS := -I$(SOURCEDIR) -I$(ALLOCTESTDIR)
# GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lsubunit -lrt -lm -lpthread

TARGET := test
SOURCES := main.c
LIB := ../s21_matrix.a
PROGRAM_TARGET := all
RUN_FLAGS :=

INC_DIR := $(abspath $(SOURCEDIR))
LDFLAGS += $(abspath $(LIB))

SOURCES += $(wildcard $(SOURCESDIR)/*.c)
SOURCES += $(wildcard $(ALLOCTESTDIR)/*.c)
OBJECTS := $(patsubst %.c,%.o,$(foreach file,$(SOURCES),$(file)))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(MAKE) -C $(SOURCEDIR) $(PROGRAM_TARGET)
	$(CC) $(CFLAGS) $(foreach object,$^,$(BUILDDIR)/$(notdir $(object))) -o $(TARGETDIR)/$@ $(LDFLAGS) 
	echo "running tests"
	$(RUN_FLAGS) ./$(TARGETDIR)/$@

%.o: %.c
	@$(CC) -I$(SOURCEDIR) $(CFLAGS) -c $< -o $(foreach object,$@,$(BUILDDIR)/$(notdir $(object)))

rebuild: clean all
clean:
	@rm -rf $(BUILDDIR)/* $(TARGETDIR)/$(TARGET)
	@rm -rf $(GCOVDIR)
	@find $(LOGDIR)/ -type f ! -name ".*" -delete

valgrind: all
	valgrind --tool=memcheck --leak-check=yes  $(TARGETDIR)/$(TARGET)

clang-n:
	clang-format --style=google -n $(SOURCESDIR)/*.c
	clang-format --style=google -n $(SOURCESDIR)/*.h
clang-i:
	clang-format --style=google -i $(SOURCESDIR)/*.c
	clang-format --style=google -i $(SOURCESDIR)/*.h

# gcov_report: LDFLAGS += --coverage
gcov_report: CFLAGS += --coverage
gcov_report: PROGRAM_TARGET := gcov_report
gcov_report: all
	mkdir -p $(GCOVDIR)
	gcovr $(BUILDDIR) -r $(TARGETDIR) --html --html-details -o $(GCOVDIR)/coverage.html

# lcov_report: LDFLAGS += --coverage
lcov_report: CFLAGS += --coverage
lcov_report: PROGRAM_TARGET := gcov_report
lcov_report: all
	lcov -t "Report" -c -d $(BUILDDIR) --rc branch_coverage=1 --output-file $(BUILDDIR)/coverage.info
	genhtml $(BUILDDIR)/coverage.info --rc branch_coverage=1 --output-directory $(GCOVDIR)
	xdg-open $(GCOVDIR)/index.html

sanitizer: PROGRAM_TARGET := gdb
sanitizer: LDFLAGS += -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls
sanitizer: RUN_FLAGS += $(shell ASAN_SYMBOLIZER_PATH=$(dpkg -L llvm-$(llvm-config  --version | grep [0-9][0-9] -o ) | grep -e /usr/lib.*symbolizer))
sanitizer: all