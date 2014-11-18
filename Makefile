TARGET=adb.exe
ADBSHELL=adb-shell.exe
BUILD_FOLDER=build
RM_SINGLE=DEL
RM_FOLDER=DEL /s
CC=gcc

ALL: $(TARGET) $(ADBSHELL)

$(TARGET): $(BUILD_FOLDER)/adb.o $(BUILD_FOLDER)/middleware.o $(BUILD_FOLDER)/path.o $(BUILD_FOLDER)/copy.o
	$(CC) -o $@ -static $^

$(ADBSHELL): $(BUILD_FOLDER)/adb-shell.o $(BUILD_FOLDER)/path.o -lgdi32 -lkernel32 -luser32
	$(CC) -o $@ -static $^

$(BUILD_FOLDER)/adb-shell.o: src/adb-shell.c build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/adb.o: src/adb.c build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/middleware.o: src/middleware.c  src/middleware.h build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/path.o: src/path.c  src/path.h build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/copy.o: src/copy.c  src/copy.h build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER):
	mkdir $(BUILD_FOLDER)

clean:
	$(RM_FOLDER) $(BUILD_FOLDER)

mrproper: clean
	$(RM_SINGLE) $(TARGET)