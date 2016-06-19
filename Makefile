CXX = g++
CXXFLAGS = -std=c++0x $(LIB_INCLUDES)
LIB_SOURCES = $(shell find ./src -name *.cpp)
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)
LIB_INCLUDES = -I./includes
UTEST_SOURCES = $(shell find ./UnitTests -name *.cpp)
UTEST_OBJECTS = $(UTEST_SOURCES:.cpp=.o)
LIB_TARGET = libpasswordmanager.so
TESTAPP_TARGET = passwordmanager
UTEST_LIB = easyunit
DESTDIR = ./install

all: lib testapp

testapp: $(TESTAPP_TARGET)

lib: $(LIB_TARGET)

$(LIB_TARGET): $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

$(TESTAPP_TARGET): $(LIB_OBJECTS) $(UTEST_OBJECTS)
	$(MAKE) -C $(UTEST_LIB)
	$(CXX) $(CXXFLAGS) $^ -l$(UTEST_LIB) -L$(UTEST_LIB) -o $@

$(LIB_OBJECTS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UTEST_OBJECTS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJECTS) $(UTEST_OBJECTS) $(TESTAPP_TARGET) $(LIB_TARGET)
	make -C $(UTEST_LIB) clean
	rm -rf $(DESTDIR)

install:
	mkdir -p $(DESTDIR)
	cp $(LIB_TARGET) $(DESTDIR)
	cp includes/Api/*.h $(DESTDIR)

runtestapp:
	LD_LIBRARY_PATH=./$(UTEST_LIB) ./$(TESTAPP_TARGET)

.PHONY: all lib testapp clean install runtestapp
