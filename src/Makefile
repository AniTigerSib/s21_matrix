CC := gcc
# CFLAGS := -Wall -Wextra -Werror -std=c11
CFLAGS := 
LDFLAGS := -lm
COVFLAGS :=
GCOV_FLAGS :=
RUN_FLAGS :=

SOURCESDIR := .
TARGETDIR := .
TESTSDIR := ./tests
HELPERSDIR := ./allocator_wrapper
BUILDDIR := ./build
GCOVDIR := ./gcov
LOGDIR := ./logs

TARGET := s21_matrix.a
LIB := ./$(TARGET)
SOURCES := 
TESTSOURCES := 
HELPERSSOURCES :=

SOURCES += $(wildcard $(SOURCESDIR)/*.c)
OBJECTS := $(patsubst %.c,%.o,$(foreach file,$(SOURCES),$(file)))

TESTSOURCES += $(wildcard $(TESTSDIR)/*.c)
TESTOBJECTS := $(patsubst %.c,%.o,$(foreach file,$(TESTSOURCES),$(notdir $(file))))
TESTGCNO := $(patsubst %.c,%.gcno,$(foreach file,$(TESTSOURCES),$(notdir $(file))))

HELPERSSOURCES += $(wildcard $(HELPERSDIR)/*.c)
HELPERSOBJECTS := $(patsubst %.c,%.o,$(foreach file,$(HELPERSSOURCES),$(notdir $(file))))

all: test

$(TARGET): $(OBJECTS)
	@ar rcs $(TARGETDIR)/$@ $(foreach object,$^,$(BUILDDIR)/$(object))

$(filter %.o,$(OBJECTS)): %.o : %.c
	@$(CC) $(CFLAGS) $(COVFLAGS) -c $< -o $(BUILDDIR)/$@

rebuild: clean all

#---------------------------------------------------------#

test: $(TARGET)
test: CFLAGS += -I$(TESTSDIR)
test: LDFLAGS += -lcheck -lsubunit -lrt -lm -lpthread $(abspath $(LIB))
test: $(TESTOBJECTS) $(HELPERSOBJECTS)
	@$(CC) $(CFLAGS) $(COVFLAGS) $(GCOV_FLAGS) $(filter %.o,$(foreach object,$^,$(BUILDDIR)/$(object))) -o $(TARGETDIR)/$@ $(LDFLAGS)
	@echo "running tests"
	@$(RUN_FLAGS) $(TARGETDIR)/$@

$(filter %.o,$(TESTOBJECTS)): %.o : $(TESTSDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

$(filter %.o,$(HELPERSOBJECTS)): %.o : $(HELPERSDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

#---------------------------------------------------------#

debug: LDFLAGS += -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls
debug: RUN_FLAGS += $(shell ASAN_SYMBOLIZER_PATH=$(dpkg -L llvm-$(llvm-config  --version | grep [0-9][0-9] -o ) | grep -e /usr/lib.*symbolizer))
debug: test

valgrind: CFLAGS += -DWITHOUT_MEMORY_LOCKING -g
valgrind: test
	valgrind --tool=memcheck --leak-check=yes --log-file="./logs/valgrind.log"  $(TARGETDIR)/$<

#---------------------------------------------------------#

gcov_report: COVFLAGS += --coverage
gcov_report: GCOV_FLAGS += -fprofile-arcs -ftest-coverage -fPIC -O0
gcov_report: clean test
	@mkdir -p $(GCOVDIR)
	@gcovr $(BUILDDIR) -r $(TARGETDIR) --html --html-details -o $(GCOVDIR)/coverage.html

lcov_report: COVFLAGS += --coverage -fprofile-arcs -ftest-coverage
lcov_report: GCOVFLAGS += -lgcov
lcov_report: clean test
	@rm -f $(foreach object,$(TESTGCNO),$(BUILDDIR)/$(object))
	@lcov -t "Report" -c -d $(BUILDDIR) --rc lcov_branch_coverage=1 --output-file $(BUILDDIR)/coverage.info
	@genhtml $(BUILDDIR)/coverage.info --rc lcov_branch_coverage=1 --output-directory $(GCOVDIR)
	@open $(GCOVDIR)/index.html

#---------------------------------------------------------#

clang-n: # Prints style warnings
	clang-format --style=google -n $(SOURCESDIR)/*.c $(TESTSDIR)/*.c $(HELPERSDIR)/*.c
	clang-format --style=google -n $(SOURCESDIR)/*.h $(TESTSDIR)/*.h $(HELPERSDIR)/*.h
clang-i: # Fixes style warnings
	@clang-format --style=google -i $(SOURCESDIR)/*.c $(TESTSDIR)/*.c $(HELPERSDIR)/*.c
	@clang-format --style=google -i $(SOURCESDIR)/*.h $(TESTSDIR)/*.h $(HELPERSDIR)/*.h

clean:
	@rm -f $(BUILDDIR)/*
	@rm -rf $(GCOVDIR)
	@rm -f $(TARGETDIR)/$(TARGET)
	@rm -f $(TARGETDIR)/test
	@find $(LOGDIR)/ -type f ! -name ".*" -delete