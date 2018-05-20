CXX = clang++
CPPFLAGS = --std=c++14 -Wall -I./
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
LIB = liblyt.a
MAIN = main.cpp
PREFIX = /usr/local

build: $(LIB)

$(LIB): $(OBJECTS)
	ar rvs $(LIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: install list

clean:
	rm -f $(LIB)
	rm $(OBJECTS)

list:
	echo $(SOURCES)
	echo $(HEADERS)
	echo $(OBJECTS)

install: $(LIB)
	mkdir -p $(PREFIX)/include/lyt
	cp $(HEADERS) $(PREFIX)/include/lyt
	mkdir -p $(PREFIX)/lib/
	cp $(LIB) $(PREFIX)/lib/

uninstall:
	rm -rf $(PREFIX)/include/lyt
	rm -f $(PREFIX)/lib/$(LIB)
	
