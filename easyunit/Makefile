CXX = g++
STRIP = strip
CXXFLAGS = -std=c++0x
LDFLAGS = -shared
TARGET_LIB = libeasyunit.so

.PHONY: all clean
all: $(TARGET_LIB)

$(TARGET_LIB):
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ *.cpp
	$(STRIP) $@

clean:
	rm -f $(TARGET_LIB)

