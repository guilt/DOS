
# before running "make -f crt0hx.mak" the files have to be moved
# to /djgpp/src/libc/crt0

TOP=..

EXTRA_OBJS += $(LIB)/crt0hx.o

include $(TOP)/../makefile.inc

$(LIB)/crt0hx.o : crt0hx.S exit16.ah sbrk16.ah
	$(XGCC) -MMD -c crt0hx.S -o $@
#	sed 's@crt0hx.o@$(LIB)/crt0hx.o@' crt0hx.d > crt02hx.d

