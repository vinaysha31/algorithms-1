#include "wordTreeInterface.h"
#include "symbolTableInterface.h"
/*
 * This use-case of the symbol Table API is going to work on the following
 * problem.
 *
 * 1) Read-in a huge amount of text
 * 2) Each word is the key of the symbol
 * 3) The value is the number of times it has occurred so far.
 * 4) Print out the most occuring ten words.
*/

int lenValue (void *key, int currentValue)
{
	return (strlen(key));
}


int main(int argc, char **argv)
{
	int value;
	symbol_table_t *st;

	st = buildTheWordTree(lenValue);
	st->dfsPrintPreOrder(st);
	st->dfsPrintInOrder(st);
	st->dfsPrintPostOrder(st);
}