
PROG=nutrition

# /usr/local/lib64/mbrlib.a 
LIB = nutrition_64.a
XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/weblib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a /usr/lib64/libmysqlclient.so -lz -lssl -luuid -lcrypto -lm

DEF = /usr/local/include

RESOURCE = /var/local/webstate/nutrition

WEBDIR = /var/www/vhosts/nutrition/html
PRG =$(WEBDIR)/$(PROG).cgi

#	$(LIB)(PaintBlog.o)	\
#	$(LIB)(SaveBlog.o)	\
#	$(LIB)(PaintEvent.o)	\
#	$(LIB)(PaintContact.o)	\
#	$(LIB)(PaintSocial.o)	\
#	$(LIB)(PaintMembers.o)	\
#	$(LIB)(SessionFuncs.o)	\

FILES = \
	$(LIB)(nutrition.o)		\
	$(LIB)(ChkInput.o)		\
	$(LIB)(Forgot.o)		\
	$(LIB)(GetContents.o)	\
	$(LIB)(GetInput.o)		\
	$(LIB)(Login.o)			\
	$(LIB)(Logout.o)		\
	$(LIB)(PaintBottom.o)	\
	$(LIB)(PaintPassword.o)	\
	$(LIB)(PaintProfile.o)	\
	$(LIB)(PaintScreen.o)	\
	$(LIB)(PaintScreen_Tables.o)	\
	$(LIB)(PaintScreen_W3_CSS.o)	\
	$(LIB)(PaintSignup.o)	\
	$(LIB)(PaintSpecial.o)	\
	$(LIB)(PaintDemoMsg.o)	\
	$(LIB)(PaintWelcome.o)	\
	$(LIB)(PaintTop.o)		\
	$(LIB)(SaveEmail.o)	\
	$(LIB)(SavePassword.o)	\
	$(LIB)(SaveProfile.o)	\
	$(LIB)(SendEmail.o)	\
	$(LIB)(Signup.o)		\
	$(LIB)(TakeAction.o)	\
	$(LIB)(Verify.o)		

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc $(LDFLAGS) -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): nutrition.h $(DEF)/filenutri.h $(DEF)/shslib.h $(DEF)/weblib.h $(DEF)/webCookie.h $(DEF)/dbylib.h

contents:
	find . \( -name '*.html' -o -name 'contents.db' \) -newer CONTENTS_STAMP -exec cp -pv {} $(RESOURCE) \;
	touch CONTENTS_STAMP

txt:
	cp -pv ExplainDietTable.HTML $(WEBDIR)/ExplainDietTable.html
	cp -pv ExplainActivity.HTML  $(WEBDIR)/ExplainActivity.html
	cp -pv ExplainGA.HTML        $(WEBDIR)/ExplainGA.html

clean:
	rm -f $(LIB)
	touch -t 199901010800 CONTENTS_STAMP

all:
	make clean
	make
	make contents
	make txt

.PRECIOUS: $(LIB)

