
.include "makefile.conf"

CLEANFILES += $(OBJS) osj5$(LINK_SUFFIX) assym.h mkassym defun.list defun.list.tmp defproto.h

CPPFLAGS += -I. -I../src/inc -I../src/machdep/$(CONF_ARCH)/$(CONF_VARIANT)/inc -I../src/machdep/$(CONF_ARCH)/common/inc

all: osj5$(LINK_SUFFIX)

osj5$(LINK_SUFFIX): assym.h $(OBJS)
#	$(LD) -o osj5$(LINK_SUFFIX) $(OBJS) $(LINK_FLAGS)
	$(CC) -v $(CONF_FLAGS) -o osj5$(LINK_SUFFIX) $(OBJS) -nostartfiles -nostdlib -nodefaultlibs -Wl,-T$(LINK_SCRIPT)

clean:
	-rm $(CLEANFILES)

################################################################
assym.h: mkassym
	./mkassym > assym.h

mkassym: ../src/util/mkassym.c ../src/inc/proc.h
	gcc $(CPPFLAGS) -o mkassym ../src/util/mkassym.c

################################################################
defun.list.tmp: $(SRCS)
	exec > defun.list.tmp;\
	for f in $(SRCS); do \
	        echo ""; \
	        echo "/* $$f */"  ; \
	        sed -n -f ../src/etc/mdefun.sed $$f ; \
	done

defun.list: defun.list.tmp
	../bin/if-changed cp defun.list.tmp defun.list

defproto.h: defun.list
	$(CPP) $(CPPFLAGS) -C -P ../src/etc/defproto.gen | sed -e 's/^$$//' -e 's/  */ /g' > defproto.h

cli.o: defun.list defproto.h


################################################################

.include "makefile.deps"

