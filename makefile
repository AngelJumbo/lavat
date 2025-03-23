PREFIX = /usr/local

lavat: lavat.c
	$(CC) lavat.c -o lavat

.PHONY: clean
clean:
	$(RM) lavat

.PHONY: install
install: lavat
	mkdir -p $(PREFIX)/bin
	install lavat $(PREFIX)/bin/lavat

.PHONY: uninstall
uninstall:
	$(RM) $(PREFIX)/bin/lavat

