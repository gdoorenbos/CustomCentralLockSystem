# My variables
PACKAGE_DIR := packages
INSTALL_DIR := install
OUTPUT_DIR := output
PACKAGES := $(wildcard $(PACKAGE_DIR)/*.tar.gz)
EXTRACT_TARGETS := $(addsuffix .done,$(PACKAGES))
CLEAN_TARGETS := $(addsuffix .clean,$(PACKAGES))
GTEST_VERSION := googletest-release-1.7.0

.PHONY: help
help:
	@echo "make targets:"
	@echo "    all: installs packages, builds tests, runs tests"
	@echo "    build-and-run: builds and runs the test code"
	@echo ""
	@echo "    install-packages: unpacks tarballs in the packages/ directory"
	@echo "    build: builds the test code"
	@echo "    run-tests: runs the test code"
	@echo ""
	@echo "    clean: deletes build artifacts (*.o files, *.a files, etc.)"
	@echo "    clean-packages: cleans the install/ directory"
	@echo ""

.PHONY: test
test:
	@echo "PACKAGES: $(PACKAGES)"
	@echo "EXTRACT_TARGETS: $(EXTRACT_TARGETS)"

# Gtest variables
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = $(INSTALL_DIR)/$(GTEST_VERSION)

# Where to find user code.
USER_DIR = source
LIB_DIR = ../libraries

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = $(OUTPUT_DIR)/BluetoothCentralLockSystemTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GTEST_ALL_O = $(OUTPUT_DIR)/gtest-all.o
GTEST_MAIN_O = $(OUTPUT_DIR)/gtest_main.o
GTEST_MAIN_A = $(OUTPUT_DIR)/gtest_main.a
GTEST_A = $(OUTPUT_DIR)/gtest.a

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(GTEST_ALL_O) : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(GTEST_MAIN_O) : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

$(GTEST_A) : $(GTEST_ALL_O)
	$(AR) $(ARFLAGS) $@ $^

$(GTEST_MAIN_A) : $(GTEST_ALL_O) $(GTEST_MAIN_O)
	$(AR) $(ARFLAGS) $@ $^

# .PHONY: all
# all:
# 	@echo "hello world!"

# .PHONY: clean
# clean: clean-packages

# .PHONY: clean-packages
# clean-packages:
# 	@echo "Cleaning install/ directory..."
# 	@rm -rf install/
# 	@mkdir install
# 	@echo "done"

# .PHONY: install-packages
# install-packages: clean-packages
# 	tar xzf packages/*.tar.gz --directory install/

# .PHONY: build
# build: $(OBJS)

install-packages: $(EXTRACT_TARGETS)

clean-packages: $(CLEAN_TARGETS)

$(INSTALL_DIR):
	mkdir -p $@

$(CLEAN_TARGETS):%.clean: %.done
	rm -rf $(INSTALL_DIR)/$(shell tar tf $(patsubst %.done,%,$<) | head -1)
	rm -f $<

$(EXTRACT_TARGETS):%.done: % | $(INSTALL_DIR)
	tar zxf $< --directory $(INSTALL_DIR)/
	touch $@

build: $(TESTS)

# BluetoothCentralLockSystemTest

$(OUTPUT_DIR)/BluetoothCentralLockSystemTest.o: $(GTEST_HEADERS) $(USER_DIR)/BluetoothCentralLockSystemTest.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/BluetoothCentralLockSystemTest.cpp -o $@

$(OUTPUT_DIR)/BluetoothCentralLockSystemTest: $(OUTPUT_DIR)/BluetoothCentralLockSystemTest.o $(GTEST_MAIN_A)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

