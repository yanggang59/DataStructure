SRCS := $(wildcard *.c)
BINS := $(patsubst %.c,%,$(SRCS))
CFLAGS := -g

all: $(BINS)

%: %.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINS)