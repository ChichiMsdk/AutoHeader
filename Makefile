NAME = add_header
EXTENSION = .exe
OUTPUT = $(NAME)$(EXTENSION)
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = build/obj
JSON_FILE = temp.json
# SRC_GUI_DIR = src/gui

INCLUDE_DIRS =-Iinclude -IC:\Lib\tracy\public -IC:\Lib\tracy\public\tracy \
	-IC:\Lib\sources\SDL2\build\include \
	-IC:\Lib\sources\SDL2\build\include-config-debug

LIBS =-lSDL2d -lSDL2maind

STATICLIB =-lUser32 -lwinmm -lAdvapi32 -lShell32 -lGdi32 -lOle32 \
		   -lSetupapi -lUuid -lImm32 -lStrmiids -lVersion -lOleAut32

LIB_PATH =-L C:\Lib\sources\SDL2\build
CFLAGS = -fsanitize=address -DWIN_32 -DTRACY_ENABLE
# CFLAGS = -DWIN_32 -DTRACY_ENABLE

CFLAGS += -g -O0 -fdeclspec -MJ$(JSON_FILE)
CPPFLAGS = -DTRACY_ENABLE

# FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_GUI_DIR)/*.c)
# OBJS := $(patsubst $(OBJ_DIR)/gui/%.o, $(OBJ_DIR)/%.o, $(OBJS))

FILES = $(wildcard $(SRC_DIR)/*.c)
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(FILES))
CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_FILES))

all: $(OBJ_DIR) $(BUILD_DIR)/$(OUTPUT) compile_commands.json

bat:
	.\build.bat debug dll

$(BUILD_DIR)/$(OUTPUT): $(OBJS) $(CPP_OBJS)
	clang $(CFLAGS) -o $@ $^ $(INCLUDE_DIRS) $(LIB_PATH) $(LIBS)
	@rm -f $(JSON_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	-clang++ $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	@-cat $(JSON_FILE) >> soon.json

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	clang $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	@-cat $(JSON_FILE) >> soon.json

$(OBJ_DIR)/%.o: $(SRC_GUI_DIR)/%.c
	clang $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	@-cat $(JSON_FILE) >> soon.json

$(OBJ_DIR): $(BUILD_DIR)
	@mkdir -p build/obj

$(BUILD_DIR):
	@mkdir -p build

compile_commands.json:
	@echo [ > compile_commands.json
	@-cat soon.json >> compile_commands.json
	@echo ] >> compile_commands.json
	@rm -f soon.json

clean:
	@rm -f $(BUILD_DIR)/$(NAME).*
	@rm -f $(BUILD_DIR)/vc140.pdb
	@rm -f $(BUILD_DIR)/*.obj
	@rm -f $(BUILD_DIR)/obj/*.o
	@rm -f $(BUILD_DIR)/*.ilk
	@rm -f compile_commands.json

re: clean all

.PHONY: all clean re bat
