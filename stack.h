#include "number_ADT.h"

//  Stack for storing number list.
typedef struct int_node {
	number *a;
	struct int_node *p;
}int_node;
typedef int_node *int_stack;
void int_init(int_stack *s);

void int_push(int_stack *s, number *a);

number *int_pop(int_stack *s);

int int_isempty(int_stack *s);


//----------------------------------------------------------------------------------------------------------

// Stack for storing character Operators.
typedef struct char_node {
	char a;
	struct char_node *p;
}char_node;
typedef char_node *char_stack;
void char_init(char_stack *s);

void char_push(char_stack *s, char t);

char char_pop(char_stack *s);

int char_isempty(char_stack *s);

