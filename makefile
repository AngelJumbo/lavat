PREFIX = /usr/local

lavat: lavat.c
	$(CC) lavat.c -o lavat

.PHONY: clean
clean:
	$(RM) lavat

.PHONY: install
install: lavat
	install 				-D lavat 		$(DESTDIR)$(PREFIX)/bin/lavat

.PHONY: unistall
unistall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/lavat
