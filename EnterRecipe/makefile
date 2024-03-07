
PROG = EnterRecipe
LIB = EnterRecipe.a
XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/weblib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a /usr/lib64/libmysqlclient.so  -lz -lssl -luuid -lcrypto -lm

# add this for reports /usr/local/lib64/libxlsxwriter.a 

DEF = /usr/local/include

PRG = /var/www/vhosts/nutrition/html/$(PROG).cgi

FILES = \
	$(LIB)(EnterRecipe.o)	\
	$(LIB)(GetInput.o)	\
	$(LIB)(ChkInput.o)	\
	$(LIB)(TakeAction.o)	\
	$(LIB)(AddRecipe.o)	\
	$(LIB)(UpdateRecipe.o)	\
	$(LIB)(FindRecipe.o)	\
	$(LIB)(DeleteRecipe.o)	\
	$(LIB)(AddRecfood.o)	\
	$(LIB)(DeleteRecfood.o)	\
	$(LIB)(CreateFood.o)	\
	$(LIB)(PaintScreen.o)	\
	$(LIB)(PaintMeal.o)	\
	$(LIB)(PaintTop.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): EnterRecipe.h $(DEF)/nutrilib.h $(DEF)/shslib.h $(DEF)/weblib.h $(DEF)/dbylib.h $(DEF)/nutrilib.h $(DEF)/filenutri.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

