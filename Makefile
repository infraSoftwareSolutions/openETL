# Compiler settings
CC      := gcc
CXX     := g++
CFLAGS  := -I.
CXXFLAGS:= -I.
CSTD := -I/C/msys64/ucrt64/include
CXXSTD := -I/C/msys64/ucrt64/include/c++/15.2.0

# Output files
LITE_EXAMPLE_OUT  := output/example/lite
LITE_TEST_OUT  := output/test/lite

# Source files
LITE_EXAMPLE_SRC := example/lite/*.cpp
LITE_TEST_SRC  := test/lite/*.cpp

# Static analysis targets
LITE_HEADERS     := include/meta/lite/*.hpp
ADVA_HEADERS := include/meta/adva/*.hpp
META_HEADERS := include

.PHONY: help \
        bitUtilitys-check cgen-check lite-check static-check \
        cgen-examples lite-examples cgen-tests lite-tests compile-tests run-tests

# --------------------------------------------------
# Static analysis
# --------------------------------------------------

lite-check:
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(LITE_HEADERS)

static-check:
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(BITUTILS_HEADERS)
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(CGEN_HEADERS)
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(LITE_HEADERS)

# --------------------------------------------------
# Tests
# --------------------------------------------------

compile-tests:
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)

compile-examples:
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLE_SRC) -o $(LITE_EXAMPLE_OUT)

run-tests:
	./$(LITE_TEST_OUT)

run-examples:
	./$(LITE_EXAMPLE_OUT)

# --------------------------------------------------
# Help
# --------------------------------------------------

help:
	@echo "Available targets:"
	@echo ""
	@echo "  static-check      : Run cppcheck on all project headers"
	@echo ""
	@echo "  compile-tests     : Compile all test programs"
	@echo "  compile-examples  : Compile all example programs"
	@echo "  run-tests         : Run all compiled tests"
	@echo "  run-examples      : Run all compiled examples"