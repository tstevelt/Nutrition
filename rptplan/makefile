PROG = rptplan
LIB = rptplan.a

MYSQL_DIR = /usr/lib64

MYSQL_FLAGS = -lz -lcrypt -lm -lssl -lcrypto

XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/weblib.a /usr/local/lib64/dbylib.a /usr/local/lib64/rptlib.a /usr/local/lib64/shslib.a $(MYSQL_DIR)/libmysqlclient.so /usr/local/lib64/libxlsxwriter.a $(MYSQL_FLAGS)

DEF = /usr/local/include

WEBDIR = /var/www/vhosts/nutrition/html
PRG = $(WEBDIR)/$(PROG).cgi

FILES = \
	$(LIB)(rptplan.o)		\
	$(LIB)(ChkInput.o)		\
	$(LIB)(GetInput.o)		\
	$(LIB)(sortdata.o)		\
	$(LIB)(PaintScreen.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): rptplan.h $(DEF)/nutrilib.h $(DEF)/filenutri.h $(DEF)/weblib.h $(DEF)/dbylib.h $(DEF)/shslib.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

