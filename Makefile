# Compiler settings
CC      := gcc
CXX     := g++
CFLAGS  := -I.
CXXFLAGS:= -I.
CSTD := -I/C/msys64/ucrt64/include
CXXSTD := -I/C/msys64/ucrt64/include/c++/15.2.0

# Output files
CGEN_EXAMPLE_OUT := output/example/cgen
LITE_EXAMPLE_OUT  := output/example/lite
CGEN_TEST_OUT := output/test/cgen
LITE_TEST_OUT  := output/test/lite

# Source files
CGEN_EXAMPLE_SRC := example/cgen/*.c
CGEN_TEST_SRC := test/cgen/*.c
LITE_EXAMPLE_SRC := example/lite/*.cpp
LITE_TEST_SRC  := test/lite/*.cpp

# Static analysis targets
BITUTILS_HEADERS := include/meta/cgen/bitUtilitys/*.h
CGEN_HEADERS    := include/meta/cgen/*.h
LITE_HEADERS     := include/meta/lite/*.hpp
ADVA_HEADERS := include/meta/adva/*.hpp
META_HEADERS := include

.PHONY: help \
        bitUtilitys-check cgen-check lite-check static-check \
        cgen-examples lite-examples cgen-tests lite-tests compile-tests run-tests

# --------------------------------------------------
# Static analysis
# --------------------------------------------------

bitUtilitys-check:
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c11 --enable=all $(BITUTILS_HEADERS)

cgen-check: bitUtilitys-check
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c11 --enable=all $(CGEN_HEADERS)

lite-check:
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(LITE_HEADERS)

static-check:
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(BITUTILS_HEADERS)
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(CGEN_HEADERS)
	cppcheck $(CSTD) $(CXXSTD) -I. --std=c++20 --enable=all $(LITE_HEADERS)

# --------------------------------------------------
# Tests
# --------------------------------------------------

cgen-tests:
	$(CC) $(CFLAGS) $(CGEN_TEST_SRC) -o $(CGEN_TEST_OUT)
	./$(CGEN_TEST_OUT)

lite-tests:
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)
	./$(LITE_TEST_OUT)

cgen-examples:
	$(CC) $(CFLAGS) $(CGEN_EXAMPLE_SRC) -o $(CGEN_EXAMPLE_OUT)
	./$(CGEN_EXAMPLE_OUT)

lite-examples:
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLE_SRC) -o $(LITE_EXAMPLE_OUT)
	./$(LITE_EXAMPLE_OUT)

compile-tests:
	$(CC) $(CFLAGS) $(CGEN_TEST_SRC) -o $(CGEN_TEST_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)

compile-examples:
	$(CC) $(CFLAGS) $(CGEN_EXAMPLE_SRC) -o $(CGEN_EXAMPLE_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLE_SRC) -o $(LITE_EXAMPLE_OUT)

run-tests:
	./$(CGEN_TEST_OUT)
	./$(LITE_TEST_OUT)

run-examples:
	./$(CGEN_EXAMPLE_OUT)
	./$(LITE_EXAMPLE_OUT)

# --------------------------------------------------
# Help
# --------------------------------------------------

help:
	@echo "Available targets:"
	@echo ""
	@echo "  bitUtilitys-check : Run cppcheck on bitUtilitys headers"
	@echo "  cgen-check       : Run cppcheck on cgen headers"
	@echo "  lite-check        : Run cppcheck on lite headers"
	@echo "  static-check      : Run cppcheck on all project headers"
	@echo ""
	@echo "  cgen-examples    : Compile and run cgen examples"
	@echo "  lite-examples     : Compile and run lite examples"
	@echo "  cgen-tests       : Compile and run cgen tests"
	@echo "  lite-tests        : Compile and run lite tests"
	@echo "  compile-tests     : Compile all test programs"
	@echo "  compile-examples  : Compile all example programs"
	@echo "  run-tests         : Run all compiled tests"
	@echo "  run-examples      : Run all compiled examples"