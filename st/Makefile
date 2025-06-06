# st - simple terminal
# See LICENSE file for copyright and license details.
.POSIX:

include config.mk

SRC = st.c x.c boxdraw.c
OBJ = $(SRC:.c=.o)

all: st

config.h:
	cp config.def.h config.h

.c.o:
	$(CC) $(STCFLAGS) -c $<

compile_flags.txt:
	printf '%s\n' $(STCFLAGS) > $@

st.o: config.h st.h win.h
x.o: arg.h config.h st.h win.h
boxdraw.o: config.h st.h boxdraw_data.h

$(OBJ): config.h config.mk

st: $(OBJ)
	$(CC) -o $@ $(OBJ) $(STLDFLAGS)

clean:
	rm -f st $(OBJ) st-$(VERSION).tar.gz

dist: clean
	mkdir -p st-$(VERSION)
	cp -R FAQ LEGACY TODO LICENSE Makefile README config.mk\
		config.def.h st.info st.1 arg.h st.h win.h $(SRC)\
		st-$(VERSION)
	tar -cf - st-$(VERSION) | gzip > st-$(VERSION).tar.gz
	rm -rf st-$(VERSION)

install: st
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f st $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/st
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < st.1 > $(DESTDIR)$(MANPREFIX)/man1/st.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/st.1
	tic -sx st.info
	@echo Please see the README file regarding the terminfo entry of st.
	mkdir -p $(DESKTOP_DIR)
	cp -f st.desktop $(DESKTOP_DIR)

sysinstall: st
	sudo mkdir -p $(DESTDIR)$(PREFIX)/bin
	sudo cp -f st $(DESTDIR)$(PREFIX)/bin
	sudo chmod 755 $(DESTDIR)$(PREFIX)/bin/st
	sudo mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sudo sed "s/VERSION/$(VERSION)/g" < st.1 > $(DESTDIR)$(MANPREFIX)/man1/st.1
	sudo chmod 644 $(DESTDIR)$(MANPREFIX)/man1/st.1
	sudo tic -sx st.info
	@echo Please see the README file regarding the terminfo entry of st.
	sudo mkdir -p $(DESKTOP_DIR)
	sudo cp -f st.desktop $(DESKTOP_DIR)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/st
	rm -f $(DESTDIR)$(MANPREFIX)/man1/st.1
	rm -f $(DESKTOP_DIR)/st.desktop

run: st
	./st

.PHONY: all clean dist install uninstall run sysinstall
