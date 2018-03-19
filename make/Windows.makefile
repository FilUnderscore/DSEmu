# 64-bit Windows

CC = x86_64-w64-mingw32-gcc
CXX = x86_64-w64-mingw32-g++

CXX_FLAGS = -Wall -g

OBJ_FLAGS = -fPIC
DIST_FLAGS = -shared

MACRO_FLAGS = -DOPENGL=1 -DENGINE_EXPORTS=1

LIBRARY_FLAGS = -lopengl32 -lglu32 -lglfw3 -lgdi32 -lDevIL -lOpenAL32 -Wl,--out-implib,GameEngine.a

TARGET_DIST = GameEngine.dll

BUILD_DIR = bin
SRC_DIR = src

OBJ_DIR = obj
OBJ_DIR_LIST = $(shell find $(SRC_DIR) -maxdepth 100 -type d)

OBJ_DL = $(OBJ_DIR_LIST:%=$(OBJ_DIR)/%)

SRC := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
OBJ := $(SRC:%=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)

OS := $(shell uname)

INC_DIRS := include /usr/x86_64-w64-mingw32/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIB_DIRS := lib /usr/x86_64-w64-mingw32/lib
LIB_FLAGS := $(addprefix -L,$(LIB_DIRS))

RM = rm

all: $(OBJ_DL) $(BUILD_DIR)/$(TARGET_DIST)

$(BUILD_DIR)/$(TARGET_DIST): $(OBJ)
	$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $^ -o $@ $(CXX_FLAGS) $(DIST_FLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(LIBRARY_FLAGS)

$(OBJ_DIR)/%.o: %

	$(CXX) $< $(CXX_FLAGS) $(OBJ_FLAGS) $(MACRO_FLAGS) $(INC_FLAGS) -c -o $@

$(OBJ_DL):
	$(MKDIR_P) $@

.PHONY: all clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(OBJ_DIR)

MKDIR_P = mkdir -p

-include $(DEP)
 
