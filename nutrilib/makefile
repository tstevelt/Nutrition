PROG = nutrilib
LIB = /usr/local/lib64/nutrilib.a
DEF = /usr/local/include
WEBDIR = /var/www/vhosts/nutrition/html

FILES = \
	$(LIB)(FoodGroup.o)		\
	$(LIB)(LoadFood.o)		\
	$(LIB)(LoadHistory.o)	\
	$(LIB)(LoadHistoryCB.o)	\
	$(LIB)(LoadHistfood.o)	\
	$(LIB)(LoadHistfoodCB.o) \
	$(LIB)(LoadRecipe.o)	\
	$(LIB)(LoadRecipeCB.o)	\
	$(LIB)(LoadRecfood.o)	\
	$(LIB)(LoadRecfoodCB.o) \
	$(LIB)(LoadMember.o)	\
	$(LIB)(LoadFoodCB.o)	\
	$(LIB)(LoadMemberCB.o)	\
	$(LIB)(SessionFuncs.o)	\
	$(LIB)(ChkMacroArithmetic.o)	\
	$(LIB)(ReportUp.o)		\
	$(LIB)(BlankRow.o)		\
	$(LIB)(RuleRow.o)		\
	$(LIB)(Spacer.o)		\
	$(LIB)(StartUp.o)

.SILENT:

$(LIB): $(FILES)
	make include

$(FILES): filenutri.h nutrilib.h nutriprivate.h $(DEF)/shslib.h $(DEF)/rptlib.h $(DEF)/dbylib.h

include:
	rm -f $(DEF)/filenutri.h
	cp -p filenutri.h $(DEF)/filenutri.h
	rm -f $(DEF)/nutrilib.h
	cp -p nutrilib.h $(DEF)/nutrilib.h

css:
	rm -f   member.css $(WEBDIR)/member.css	
	cp -pv member_large.css $(WEBDIR)/member_large.css	
	cp -pv member_small.css $(WEBDIR)/member_small.css	
	cp -pv my_navbar_colors.css $(WEBDIR)/my_navbar_colors.css
	cp -pv nutrition.css $(WEBDIR)/nutrition.css

js:
	cp -pv Nutrition.js $(WEBDIR)/Nutrition.js	

clean:
	rm -f $(LIB)

all:
	make clean
	make
	make css
	make js

.PRECIOUS: $(LIB)

