RM = rm

MAKE = make

BUILD_DIR = bin
OBJ_DIR = obj

win32:
	$(MAKE) -f make/Win32.makefile

windows:
	$(MAKE) -f make/Windows.makefile

linux:
	$(MAKE) -f make/Linux.makefile

lib:
	$(MAKE) -f make/Library.makefile

.PHONY: win32 windows linux lib clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(OBJ_DIR)
