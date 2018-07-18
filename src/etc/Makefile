
.include "makefile.conf"

CLEANFILES += $(OBJS) osj5$(LINK_SUFFIX) assym.h mkassym defun.list defun.list.tmp defvar.list defvar.list.tmp defproto.h

CPPFLAGS += -I. $(INCL_FLAGS) -I../../src/inc

all: osj5$(LINK_SUFFIX)

osj5$(LINK_SUFFIX): assym.h $(OBJS)
	$(LINK) $(CONF_FLAGS) $(LINK_FLAGS) -o osj5$(LINK_SUFFIX) $(OBJS) $(LIBS)

clean:
	-rm $(CLEANFILES)

################################################################
assym.h: mkassym
	./mkassym > assym.h

mkassym: ../../src/util/mkassym.c ../../src/inc/proc.h
	gcc $(CPPFLAGS) -o mkassym ../../src/util/mkassym.c

################################################################
defun.list.tmp: $(SRCS)
	@exec > defun.list.tmp;\
	for f in $(SRCS); do \
	        echo ""; \
	        echo "/* $$f */"  ; \
	        sed -n -f ../../src/etc/mdefun.sed $$f ; \
	done

defun.list: defun.list.tmp
	@../../bin/if-changed cp defun.list.tmp defun.list

defproto.h: defun.list defvar.list
	$(CPP) $(CPPFLAGS) -C -P ../../src/etc/defproto.gen | sed -e 's/^$$//' -e 's/  */ /g' > defproto.h

defvar.list.tmp: $(SRCS)
	@exec > defvar.list.tmp;\
	for f in $(SRCS); do \
	        echo ""; \
	        echo "/* $$f */"  ; \
	        sed -n -f ../../src/etc/mdefvar.sed $$f ; \
	done

defvar.list: defvar.list.tmp
	@../../bin/if-changed cp defvar.list.tmp defvar.list


cli.o: defun.list defvar.list defproto.h


################################################################

.include "makefile.deps"

