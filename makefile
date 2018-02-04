PREFIX = /usr/local

build:
	$(MAKE) build -C library

install:
	$(MAKE) install PREFIX=$(PREFIX) -C library
	cp tool/lyt.py $(PREFIX)/bin/lyt
	chmod +x $(PREFIX)/bin/lyt

uninstall:
	$(MAKE) uninstall PREFIX=$(PREFIX) -C library
	rm $(PREFIX)/bin/lyt
