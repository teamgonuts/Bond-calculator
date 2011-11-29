#makefile  to build library and testdriver
.SUFFIXES:.cc
.cc.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

#	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# assign your compiler name to CC if not g++
CC = g++
# where your header files are (. is same directory as the makefile)
INCLUDES=-I.
# turn on debugging symbols
CFLAGS= -g -p -O3 -fno-inline
# where your object files are (. is the same directory as the makefile)
LDFLAGS=-L.

# when "make" is typed at command line with no args "default" will get executed and do "all"
default: 	all

#
# assign source and headers for our "utility" lib to variables below
#
# replace "SBB" (my initials) with yours or use the same filenames
LIB_UTIL_SRC = SBB_util.cc
LIB_UTIL_SRC_HDR = SBB_util.h
#
LIB_UTIL_OBJ = $(LIB_UTIL_SRC:.cc=.o)
$(LIB_UTIL_OBJ) : $(LIB_UTIL_SRC_HDR)
LIB_UTIL_TARGET = libutil.a
#
# assign source and headers for our "IO" lib to variables below
#
LIB_IO_SRC = SBB_io.cc
LIB_IO_SRC_HDR = SBB_io.h
#
LIB_IO_OBJ = $(LIB_IO_SRC:.cc=.o)
$(LIB_IO_OBJ) : $(LIB_IO_SRC_HDR)
LIB_IO_TARGET = libio.a
#
# assign source and headers for "date" lib to variables below
#
LIB_DATE_SRC = SBB_date.cc
LIB_DATE_SRC_HDR = SBB_date.h
#
LIB_DATE_OBJ = $(LIB_DATE_SRC:.cc=.o)
$(LIB_DATE_OBJ) : $(LIB_DATE_SRC_HDR)
LIB_DATE_TARGET = libdate.a
#
# assign source and headers for "bond_rating" lib to variables below
#
LIB_RATING_SRC = SBB_ratings.cc
LIB_RATING_SRC_HDR = SBB_ratings.h
#
LIB_RATING_OBJ = $(LIB_RATING_SRC:.cc=.o)
$(LIB_RATING_OBJ) : $(LIB_RATING_SRC_HDR)
LIB_RATING_TARGET = librating.a
#

# assign source and headers for "BondPrice_calculator" lib to variables below
#
LIB_CAL_SRC = BondPrice_calculator.cc
LIB_CAL_SRC_HDR = BondPrice_calculator.h
#
LIB_CAL_OBJ = $(LIB_CAL_SRC:.cc=.o)
$(LIB_CAL_OBJ) : $(LIB_CAL_SRC_HDR)
LIB_CAL_TARGET = libcal.a
#
# the file where main() is
MAIN_SRC = sbb_server.c
MAINOBJ = $(MAIN_SRC:.cc=.o) 
$(MAINOBJ) : $(LIB_TARGET) $(LIB_UTIL_TARGET) $(LIB_IO_TARGET) $(LIB_DATE_TARGET) $(LIB_RATING_TARGET)
MAINTARGET=testdriver

ARCHIVE_OPTIONS = rucsv

$(LIB_UTIL_TARGET) : $(LIB_UTIL_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_UTIL_TARGET) $(LIB_UTIL_OBJ)

$(LIB_IO_TARGET) : $(LIB_IO_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_IO_TARGET) $(LIB_IO_OBJ)

$(LIB_DATE_TARGET) : $(LIB_DATE_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_DATE_TARGET) $(LIB_DATE_OBJ)

$(LIB_CAL_TARGET) : $(LIB_CAL_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_CAL_TARGET) $(LIB_CAL_OBJ)

$(LIB_RATING_TARGET) : $(LIB_RATING_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_RATING_TARGET) $(LIB_RATING_OBJ)

$(MAINTARGET) : $(MAINOBJ) $(LIB_TARGET) $(LIB_UTIL_TARGET) $(LIB_IO_TARGET) $(LIB_DATE_TARGET) $(LIB_CAL_TARGET) $(LIB_RATING_TARGET)
	$(CC) -O $(LDFLAGS) $(MAINOBJ) $(LIB_UTIL_TARGET) $(LIB_IO_TARGET) $(LIB_DATE_TARGET) $(LIB_TARGET) $(LIB_CAL_TARGET) $(LIB_RATING_TARGET) -o $(MAINTARGET)

all : util test

test: $(MAINTARGET)

util: $(LIB_UTIL_TARGET)


clean:
	rm -f *.o 

clobber:
	-rm -f *.o *.a $(MAINTARGET)

backup: clobber
	tar cvf ./nyu.tar *.*
