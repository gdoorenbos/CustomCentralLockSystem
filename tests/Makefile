# My variables
PACKAGE_DIR := packages
INSTALL_DIR := install
OUTPUT_DIR := output
OBJ_DIR := $(OUTPUT_DIR)/obj
PACKAGES := $(wildcard $(PACKAGE_DIR)/*.tar.gz)
EXTRACT_TARGETS := $(addsuffix .done,$(PACKAGES))
CLEAN_TARGETS := $(addsuffix .clean,$(PACKAGES))
GTEST_VERSION := googletest-release-1.7.0

# Gtest variables
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = $(INSTALL_DIR)/$(GTEST_VERSION)

# Where to find user code.
USER_DIR = source
LIB_DIR = ../libraries
CPPFLAGS += $(patsubst %,-I%,$(wildcard $(LIB_DIR)/*))
MOCK_OBJ_NAMES := $(patsubst $(LIB_DIR)/%,%,$(wildcard $(LIB_DIR)/Mock*))
MOCK_OBJ_NAMES += $(patsubst $(LIB_DIR)/Mock%,%,$(wildcard $(LIB_DIR)/Mock*))
MOCK_OBJ_DIRS := $(foreach MOCK_OBJ_NAME,$(MOCK_OBJ_NAMES),$(OBJ_DIR)/$(MOCK_OBJ_NAME))
MOCK_OBJS := $(foreach MOCK_OBJ_NAME,$(MOCK_OBJ_NAMES),$(OBJ_DIR)/$(MOCK_OBJ_NAME)/$(MOCK_OBJ_NAME).o)
MOCK_HEADERS := $(foreach MOCK_OBJ_NAME,$(MOCK_OBJ_NAMES),$(wildcard $(LIB_DIR)/$(MOCK_OBJ_NAME)/*.h))

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TEST_SOURCES := $(wildcard $(USER_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(USER_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SOURCES))
TEST_EXECUTABLE := $(OUTPUT_DIR)/test

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GTEST_ALL_O = $(OBJ_DIR)/gtest-all.o
GTEST_MAIN_O = $(OBJ_DIR)/gtest_main.o
GTEST_MAIN_A = $(OBJ_DIR)/gtest_main.a
GTEST_A = $(OBJ_DIR)/gtest.a

# default target
.PHONY: all
all: run-tests

# Help text
.PHONY: help
help:
	@echo "make targets:"
	@echo "    all: 	default target. Builds and runs test code in $(USER_DIR)/ directory."
	@echo "    help: 	displays this help text."
	@echo ""
	@echo "    install-packages:	unpacks tarballs in the $(PACKAGE_DIR)/ directory."
	@echo "    build: 				builds the test code in the $(USER_DIR)/ directory."
	@echo "    run-tests: 			runs the test code, building it first if necessary."
	@echo ""
	@echo "    clean: 			deletes build artifacts (*.o files, *.a files, etc.)."
	@echo "    clean-packages: 	cleans the $(INSTALL_DIR)/ directory."
	@echo "    clean-all: 		cleans build artifacts and the $(INSTALL_DIR)/ directory."
	@echo ""

.PHONY: devhelp
devhelp:
	@echo "MOCK_OBJ_NAMES: $(MOCK_OBJ_NAMES)"
	@echo "MOCK_OBJS: $(MOCK_OBJS)"
	@echo "MOCK_HEADERS: $(MOCK_HEADERS)"

# Google test targets
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

# Directories
$(INSTALL_DIR):
	mkdir -p $@

$(OUTPUT_DIR):
	mkdir -p $@

$(OBJ_DIR): | $(OUTPUT_DIR)
	mkdir -p $@

$(MOCK_OBJ_DIRS): | $(OBJ_DIR)
	mkdir -p $@

# Package targets
$(EXTRACT_TARGETS):%.done: % | $(INSTALL_DIR)
	tar zxf $< --directory $(INSTALL_DIR)/
	touch $@

.PHONY: install-packages
install-packages: $(EXTRACT_TARGETS)

.PHONY: $(CLEAN_TARGETS)
$(CLEAN_TARGETS):%.clean:
	rm -rf $(INSTALL_DIR)/$(shell tar tf $(patsubst %.clean,%,$@) | head -1)
	rm -f $(patsubst %.clean,%.done,$@)

.PHONY: clean-packages
clean-packages: $(CLEAN_TARGETS)
	rm -rf $(INSTALL_DIR)

# Build targets
$(MOCK_OBJS):$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp $(MOCK_HEADERS) $(GTEST_HEADERS) | $(MOCK_OBJ_DIRS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJS):$(OBJ_DIR)/%.o: $(USER_DIR)/%.cpp $(MOCK_HEADERS) $(GTEST_HEADERS) | $(OBJ_DIR)
# $(TEST_OBJS):$(OBJ_DIR)/%.o: $(USER_DIR)/%.cpp $(GTEST_HEADERS) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_EXECUTABLE): $(TEST_OBJS) $(MOCK_OBJS) $(GTEST_MAIN_A) | $(OUTPUT_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

.PHONY: build
build: $(TEST_EXECUTABLE)

.PHONY: run-tests
run-tests: $(TEST_EXECUTABLE)
	@ $(TEST_EXECUTABLE)

# Clean targets
.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: clean-all
clean-all: clean clean-packages

