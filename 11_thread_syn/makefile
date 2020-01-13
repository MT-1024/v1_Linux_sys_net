src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))
all:$(target)
%:%.c
	gcc $< -o $@ -lpthread
clean:
	-rm -rf $(target) 
.PHONY: all clean
