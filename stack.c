#include<stdlib.h>
#include"stack.h"

// Stack implementation to store number list.
void int_init(int_stack *s) {
	*s = NULL;
}
void int_push (int_stack *s, number *t) {
	int_stack temp;
	temp = (int_node *)malloc(sizeof(int_node));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}
number *int_pop(int_stack *s) {
	number *t;
	int_stack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}
int int_isempty (int_stack *s) {
	return *s == NULL;
}

//-------------------------------------------------------------------------------------------------------

//  Stack implementation to store character Operators.
void char_init(char_stack *s) {
	*s = NULL;
}
void char_push (char_stack *s, char t) {
	char_stack temp;
	temp = (char_node *)malloc(sizeof(char_node));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}
char char_pop(char_stack *s) {
	char t;
	char_stack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}
int char_isempty (char_stack *s) {
	return *s == NULL;
}
