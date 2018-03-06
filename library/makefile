CXX = clang++
CPPFLAGS = --std=c++14 -Wall
SOURCES = buffer.cpp lyt.cpp settings.cpp processor.cpp delay.cpp biquad.cpp runningAverage.cpp utils.cpp realtime.cpp
HEADERS = buffer.h lyt.h settings.h processor.h delay.h biquad.h runningAverage.h utils.h realtime.h
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
LIB = liblyt.a
MAIN = main.cpp
PREFIX = /usr/local

build: $(LIB)

$(LIB): $(OBJECTS)
	ar rvs $(LIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: install

clean:
	rm -f $(LIB)
	rm $(OBJECTS)

install: $(LIB)
	mkdir -p $(PREFIX)/include/lyt
	cp $(HEADERS) $(PREFIX)/include/lyt
	mkdir -p $(PREFIX)/lib/
	cp $(LIB) $(PREFIX)/lib/

uninstall:
	rm -rf $(PREFIX)/include/lyt
	rm -f $(PREFIX)/lib/$(LIB)
	
