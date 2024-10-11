TARGETS := all clean test s21_matrix.a gcov_report clang_i clang_n val rebuild sanitizer lcov_report
SOURCE_DIR := ./matrix
TEST_DIR := ./tests
TEST_TARGETS := test clean gcov_report lcov_report clang_i clang_n val sanitizer
SOURCE_TARGETS := clean all s21_matrix.a clang_i clang_n rebuild

define MAIN_MAKE
$(1):
	$(if $(findstring $(1),$(SOURCE_TARGETS)),$(MAKE) -C $(SOURCE_DIR) $(1);)
	$(if $(findstring $(1),$(TEST_TARGETS)),$(MAKE) -C $(TEST_DIR) $(1);)
	
endef

$(foreach TARGET,$(TARGETS),$(eval $(call MAIN_MAKE,$(TARGET))))

.PHONY: $(TARGETS)