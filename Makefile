SRC := binary_tree.c link_list.c

all:
	gcc binary_tree.c -o binary_tree -g
	gcc link_list.c -o link_list -g
	gcc array.c -o array -g
	gcc leet_code.c -o leet_code -g
	gcc heap.c -o heap -g
clean:
	rm -f binary_tree
	rm -f link_list
	rm -f array
	rm -f leet_code
	rm -f heap