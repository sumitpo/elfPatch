# File              : makefile
# Author            : guochuliang <2797366715@qq.com>
# Date              : 24.11.2023
# Last Modified Date: 25.11.2023
# Last Modified By  : guochuliang <2797366715@qq.com>
LDFLAGS = -lasan
CFLAGS = -DLOG_USE_COLOR -g -fsanitize=address
objs = main.o log.o elfReader.o
target = patchElf
$(target):$(objs)
	gcc $(LDFLAGS) -o $@ $^
$(objs):%.o : %.c
	gcc $(CFLAGS) -c -o $@ $<
clean:cleanobj
	rm $(target)
cleanobj:
	rm $(objs)
