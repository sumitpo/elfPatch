objs = test.o
target = unstripped.exe stripped.exe
all:$(target)
stripped.exe: $(objs)
	gcc -s -o $@ $^
unstripped.exe: $(objs)
	gcc -o $@ $^

$(objs):%.o : %.c
	gcc $(CFLAGS) -c -o $@ $<
clean:cleanobj
	rm $(target)
cleanobj:
	rm $(objs)
