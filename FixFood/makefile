PROG = FixFood
LIB = FixFood.a
MYSQL_DIR = /usr/lib64
MYSQL_FLAGS = -lz -lcrypt -lm -lssl -lcrypto
MLIB = $(MYSQL_DIR)/libmysqlclient.so $(MYSQL_FLAGS)

XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a

DEF = /usr/local/include
PRG = /usr/local/bin/$(PROG)

FILES = \
	$(LIB)(FixFood.o)	\
	$(LIB)(EachFood.o)	\
	$(LIB)(getargs.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB) $(MLIB)

$(LIB): $(FILES)

$(FILES): FixFood.h $(DEF)/shslib.h $(DEF)/dbylib.h $(DEF)/filenutri.h $(DEF)/nutrilib.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

