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

TARGET := ./s21_matrix.a
LIB := $(TARGET)
SOURCES := 
TESTSOURCES := 
HELPERSSOURCES :=

SOURCES += $(wildcard $(SOURCESDIR)/*.c)
OBJECTS := $(patsubst %.c,%.o,$(foreach file,$(SOURCES),$(file)))

TESTSOURCES += $(wildcard $(TESTSDIR)/*.c)
TESTOBJECTS := $(patsubst %.c,%.o,$(foreach file,$(TESTSOURCES),$(notdir $(file))))

HELPERSSOURCES += $(wildcard $(HELPERSDIR)/*.c)
HELPERSOBJECTS := $(patsubst %.c,%.o,$(foreach file,$(HELPERSSOURCES),$(notdir $(file))))

all: $(TARGET)
$(TARGET): $(OBJECTS)
	ar rcs $(TARGETDIR)/$@ $(foreach object,$^,$(BUILDDIR)/$(object))

testing:
	echo $(TESTSOURCES)
	echo "Or"
	echo $(TESTOBJECTS)

$(filter %.o,$(OBJECTS)): %.o : %.c
	$(CC) $(CFLAGS) $(COVFLAGS) -c $< -o $(BUILDDIR)/$@

rebuild: clean all

#---------------------------------------------------------#

test: $(TARGET)
test: CFLAGS += -I$(TESTSDIR)
test: LDFLAGS += -lcheck -lsubunit -lrt -lm -lpthread $(abspath $(LIB))
test: $(TESTOBJECTS) $(HELPERSOBJECTS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(filter %.o,$(foreach object,$^,$(BUILDDIR)/$(object))) -o $(TARGETDIR)/$@ $(LDFLAGS)
	echo "running tests"
	$(RUN_FLAGS) $(TARGETDIR)/$@

$(filter %.o,$(TESTOBJECTS)): %.o : $(TESTSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

$(filter %.o,$(HELPERSOBJECTS)): %.o : $(HELPERSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

#---------------------------------------------------------#

debug: LDFLAGS += -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls
debug: RUN_FLAGS += $(shell ASAN_SYMBOLIZER_PATH=$(dpkg -L llvm-$(llvm-config  --version | grep [0-9][0-9] -o ) | grep -e /usr/lib.*symbolizer))
debug: test

gcov_report: COVFLAGS += --coverage
gcov_report: GCOV_FLAGS += -fprofile-arcs -ftest-coverage -fPIC -O0
gcov_report: test
	mkdir -p $(GCOVDIR)
	gcovr $(BUILDDIR) -r $(TARGETDIR) --html --html-details -o $(GCOVDIR)/coverage.html

#---------------------------------------------------------#

clang-n:
	clang-format --style=google -n $(SOURCESDIR)/*.c
	clang-format --style=google -n $(SOURCESDIR)/*.h
clang-i:
	clang-format --style=google -i $(SOURCESDIR)/*.c
	clang-format --style=google -i $(SOURCESDIR)/*.h

clean:
	@rm -f $(BUILDDIR)/*
	@rm -rf $(GCOVDIR)
	@rm -f $(TARGETDIR)/$(TARGET)
	@rm -f $(TARGETDIR)/test
	@find $(LOGDIR)/ -type f ! -name ".*" -delete