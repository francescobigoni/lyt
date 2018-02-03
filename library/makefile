CPPFLAGS = --std=c++11 -Wall
SOURCES = buffer.cpp lyt.cpp
HEADERS = buffer.h lyt.h
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
LIB = liblyt.a
MAIN = main.cpp
PREFIX = /usr/local/

$(LIB): $(OBJECTS)
	ar rvs $(LIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	clang++ $(CPPFLAGS) -c $< -o $@

.PHONY: install

install: $(LIB)
	mkdir -p $(PREFIX)/include/lyt
	mv $(HEADERS) $(PREFIX)/include/lyt
	mkdir -p $(PREFIX)/lib/
	mv $(LIB) $(PREFIX)/lib/

uninstall:
	rm -rfi $(PREFIX)/include/lyt
	rm -fi $(PREFIX)/lib/$(LIB)
	
