TARGET := binary_tree
SRC := binary_tree.c

all:
	gcc binary_tree.c -o ${TARGET} -g

clean:
	rm -f ${TARGET}