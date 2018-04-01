CC = gcc
CXX = g++

CXX_FLAGS = -Wall -g -Wextra

MACRO_FLAGS = -DOPENGL=1

LIB_FLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lalut -lopenal

TEMP_LIB_FLAGS = 

TARGET_DIST = DSEmu

BUILD_DIR = bin
SRC_DIR = src

OBJ_DIR = obj
OBJ_DIR_LIST = $(shell find $(SRC_DIR) -maxdepth 100 -type d)

OBJ_DL = $(OBJ_DIR_LIST:%=$(OBJ_DIR)/%)

SRC := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
OBJ := $(SRC:%=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)

OS := $(shell uname)

INC_DIRS := ../DSEmu/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

RM = rm

all: $(OBJ_DL) $(BUILD_DIR)/$(TARGET_DIST)

$(BUILD_DIR)/$(TARGET_DIST): $(OBJ)
	$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $^ -o $@ -D LINUX $(CXX_FLAGS) $(MACRO_FLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(TEMP_LIB_FLAGS)

$(OBJ_DIR)/%.o: %

	$(CXX) $< $(CXX_FLAGS) $(INC_FLAGS) -c -o $@

$(OBJ_DL):
	$(MKDIR_P) $@

.PHONY: all clean

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(BUILD_DIR)

MKDIR_P = mkdir -p

-include $(DEP)
