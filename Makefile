TARGET=adb.exe
BUILD_FOLDER=build
RM_SINGLE=DEL
RM_FOLDER=DEL /s
CC=gcc

$(TARGET): $(BUILD_FOLDER)/adb.o $(BUILD_FOLDER)/middleware.o $(BUILD_FOLDER)/path.o
	$(CC) -o $@ -static $^

$(BUILD_FOLDER)/adb.o: src/adb.c build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/middleware.o: src/middleware.c  src/middleware.h build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER)/path.o: src/path.c  src/path.h build
	$(CC) -o $@ -c $<

$(BUILD_FOLDER):
	mkdir $(BUILD_FOLDER)

clean:
	$(RM_FOLDER) $(BUILD_FOLDER)

mrproper: clean
	$(RM_SINGLE) $(TARGET)