CUR_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SRCS := $(wildcard ./*.c)
BINS := $(patsubst %.c,%,$(SRCS))
COMMON_DIR := $(CUR_DIR)/common
COMMON_SRCS := $(wildcard $(COMMON_DIR)/*.c)
COMMON_OBJS := $(COMMON_SRCS:.c=.o)
COMMON_LIB := $(COMMON_DIR)/libcommon.a

CFLAGS := -I $(COMMON_DIR) -g

all: $(COMMON_LIB) $(BINS)

%: %.c $(COMMON_LIB)
	gcc $(CFLAGS) -o $@ $< -L$(COMMON_DIR) -lcommon

$(COMMON_LIB): $(COMMON_OBJS)
	ar rcs $@ $^

$(COMMON_DIR)%.o: $(COMMON_DIR)%.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BINS) $(COMMON_LIB) $(COMMON_OBJS)

.PHONY: all clean