CC=gcc
LD=gcc
OPTIMIZATIONS=-g -O3 -fdata-sections -ffunction-sections -fmerge-all-constants -flto -fuse-linker-plugin -Wl,--gc-sections -mavx
CFLAGS=-Wall $(OPTIMIZATIONS) -I..\common\inc
LDLIBS=
LDFLAGS=$(OPTIMIZATIONS) -static

OBJS=entry.o

all: sinewave.exe
	
-include $(OBJS:.o=.d)

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d

sinewave.exe: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

clean:
	del *.o *.exe *.d
