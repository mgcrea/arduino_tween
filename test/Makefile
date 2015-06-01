
ARDUINO_DIR   = /Applications/ArduinoLegacy.app/Contents/Resources/Java
SOURCES = TestMain.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
# CXX = $(ARDUINO_DIR)/hardware/tools/arm/bin/arm-none-eabi-g++
CXX = g++
ARDFLAGS = -include Arduino.h -MMD -c -DLAYOUT_US_ENGLISH -DUSB_SERIAL -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=123 -x c++ -include Arduino.h -mcpu=cortex-m4 -DF_CPU=96000000 -DARDUINO=106 -DARDUINO_ARCH_ARM -D__PROG_TYPES_COMPAT__ -I$(ARDUINO_DIR)/hardware/teensy/cores/teensy3 -I$(ARDUINO_DIR)/hardware/teensy/arm/variants/
CXXFLAGS = $(ARDFLAGS) -I.. -Wall -Wno-extra-tokens -ffunction-sections -fdata-sections -Os -fno-rtti -felide-constructors -fno-exceptions -std=gnu++0x

#-std=c++11

CatchTest: $(OBJECTS)
	$(CXX) -o $@ $^

test: CatchTest
	./CatchTest

clean:
	rm -f $(OBJECTS) CatchTest


# Working Teensy3.1 build command
# /Applications/ArduinoLegacy.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-g++
# -x c++ -include Arduino.h -MMD -c -DLAYOUT_US_ENGLISH -DUSB_SERIAL -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=123
# -mcpu=cortex-m4 -DF_CPU=96000000 -DARDUINO=106 -DARDUINO_ARCH_ARM -D__PROG_TYPES_COMPAT__
# -I/Applications/ArduinoLegacy.app/Contents/Resources/Java/hardware/teensy/cores/teensy3 -I/Applications/ArduinoLegacy.app/Contents/Resources/Java/hardware/teensy/arm/variants/
# -I/Users/olivier/Projects/foo/teensy-table/lib/ArduinoJson   -I/Users/olivier/Projects/foo/teensy-table/lib/EEPROMEx   -I/Users/olivier/Projects/foo/teensy-table/lib/Firmata   -I/Users/olivier/Projects/foo/teensy-table/lib/OctoWS2811   -I/Users/olivier/Projects/foo/teensy-table/lib/Tween
# -Wall -ffunction-sections -fdata-sections -Os -fno-rtti -felide-constructors -fno-exceptions -std=gnu++0x app.ino -o build-teensy31/app.o
