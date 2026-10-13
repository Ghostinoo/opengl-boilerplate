CXX ?= clang++
CC  ?= clang

# Unix shell commands
MKDIR_P = mkdir -p "$(1)"
RM_RF   = rm -rf "$(1)"
RUN     = ./$(TARGET)

# Directories
SRC_DIR   = src
BUILD_DIR = build
BIN_DIR   = bin
LIB_DIR   = lib
EXT_DIR   = extlib

# Flags
CXXFLAGS = -I$(LIB_DIR) -I$(EXT_DIR) -Wall -Wextra -std=c++20
CFLAGS   = -I$(LIB_DIR) -I$(EXT_DIR) -Wall -Wextra -std=c11
LDFLAGS  = -lglfw -lGL -ldl -lpthread

# Recursive wildcard (Windows/MSYS2 friendly, no 'find')
rwildcard = $(foreach d,$(wildcard $(1)/*),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Sources
APP_SOURCES   = $(call rwildcard,$(SRC_DIR),*.cpp)
LIB_SOURCES   = $(call rwildcard,$(LIB_DIR),*.cpp)
EXT_SOURCES   = $(call rwildcard,$(EXT_DIR),*.cpp)
EXT_C_SOURCES = $(call rwildcard,$(EXT_DIR),*.c)

# Objects
APP_OBJ   = $(APP_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.o)
LIB_OBJ   = $(LIB_SOURCES:$(LIB_DIR)/%.cpp=$(BUILD_DIR)/lib/%.o)
EXT_OBJ   = $(EXT_SOURCES:$(EXT_DIR)/%.cpp=$(BUILD_DIR)/ext/%.o)
EXT_C_OBJ = $(EXT_C_SOURCES:$(EXT_DIR)/%.c=$(BUILD_DIR)/ext/%.o)

OBJ = $(APP_OBJ) $(LIB_OBJ) $(EXT_OBJ) $(EXT_C_OBJ)

TARGET = $(BIN_DIR)/app

# Rules
all: compile_flags.txt $(TARGET)

$(TARGET): $(OBJ)
	$(call MKDIR_P,$(BIN_DIR))
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/ext/%.o: $(EXT_DIR)/%.c
	$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/ext/%.o: $(EXT_DIR)/%.cpp
	$(call MKDIR_P,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.cpp
	$(call MKDIR_P,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR_P,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clangd
flags:
	@{ echo "-std=c++20"; \
	  for f in $(filter -I%,$(CXXFLAGS)); do echo "$$f"; done; \
	  for f in $(filter -D%,$(CXXFLAGS)); do echo "$$f"; done; \
	} > compile_flags.txt
	@echo "Wrote compile_flags.txt"

clean:
	$(call RM_RF,$(BUILD_DIR))
	$(call RM_RF,$(BIN_DIR))

run: all
	$(RUN)

debug:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g -O0 -DDEBUG" clean all

release:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -O2 -DNDEBUG" clean all

.PHONY: all clean run debug release flags