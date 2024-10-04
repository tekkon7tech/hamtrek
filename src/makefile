CFLAGS=     -O -pthread -DSCORE -DCAPTURE -DCLOAKING
# CFLAGS=     -O -Wno-unused-result

.c.o:
	$(CC) $(CFLAGS) -c $<

OFILES=     hamtrek.o finish.o reports.o setup.o osx.o moving.o battle.o events.o ai.o planets.o watch.o colors.o crewdialog.o

HFILES=     hamtrek.h

sst:  $(OFILES)
	gcc  -o sst $(OFILES) -lm

clean:
	rm $(OFILES)
        
$(OFILES):  $(HFILES)

