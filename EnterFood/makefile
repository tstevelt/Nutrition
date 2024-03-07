PROG = EnterFood
LIB = EnterFood.a

MYSQL_DIR = /usr/lib64
MYSQL_FLAGS = -lz -lcrypt -lm -lssl -lcrypto
XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/weblib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a $(MYSQL_DIR)/libmysqlclient.so $(MYSQL_FLAGS)
DEF = /usr/local/include
WEBDIR = /var/www/vhosts/nutrition/html
PRG = $(WEBDIR)/$(PROG).cgi

FILES = \
	$(LIB)(EnterFood.o)		\
	$(LIB)(ChkInput.o)		\
	$(LIB)(Delete.o)		\
	$(LIB)(Load.o)			\
	$(LIB)(GetInput.o)		\
	$(LIB)(Insert.o)		\
	$(LIB)(Lookup.o)		\
	$(LIB)(PaintScreen.o)	\
	$(LIB)(PaintTop.o)	\
	$(LIB)(Update.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): EnterFood.h $(DEF)/nutrilib.h $(DEF)/filenutri.h $(DEF)/weblib.h $(DEF)/dbylib.h $(DEF)/shslib.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

