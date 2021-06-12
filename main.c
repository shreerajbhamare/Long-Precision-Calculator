#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"
#include"operation.h"
#include<limits.h>

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400
/*  defination of token
*/
/*
List of Operation- Addition, subtraction, Multiplication, Division, Modulo, Power, Logical AND,
                   Logical OR, Equality, Non-Equality, Greater and Less Operations .
.*/
int readline(char *line, int len);
void validate(char *line);
number *infix(char *exp);
typedef struct token{
	int type;
	union data{
	number *num;
	char op;
	}data;
}token;
int main(int argc, char *argv[]) {
    printf("\t\t\t\t\t\tName - Shreeraj Vijay Bhamare\n");
    printf("\t\t\t\t\t\t\tMIS - 111903098\n");
    printf("\t\t\t\t\t\t\t  Batch - S1\n");
    printf("\n");
    printf("ATTENTION: For Declaring Negative numbers. Kindly use Brackets.\n\n");
    printf("For Logical and(&&) use '&' only\n");
    printf("For Logical or(||) use '|' only\n");
    printf("For checking Not-Equality(!=) use '!' only\n");
    printf("For checking Equality(==) use '=' only\n");
    printf("\n");
    printf("\n");
	number *r;
	char line[2048];
	while(readline(line, 2048)) {
		validate(line);
		r = infix(line);
		if(r != NULL)
			printNumber(*r);
		else
			fprintf(stderr, "Error in expression\n");
	}
	return 0;
}
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };
token getnext(char *expr, int *reset) {
	static int i = 0;
	number *a = (number *)malloc(sizeof(number));
	initNumber(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						append(a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : case '^':
                    case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case DOT:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						append(a, currchar);
						a->dec++;
						nextstate = DOT;
						currstate = nextstate;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : case '^':
                    case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;
						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : case '^':
                    case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						t.type = OPERATOR;
						t.data.op = expr[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						append(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : case '^':
                    case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = DOT;
						i++;
						break;

					default:
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}
char char_top(char_stack *s) {
	char ch;
	ch = char_pop(s);
	char_push(s, ch);
	return ch;
}
int precedance(char o) {
	switch(o) {
	    case '>':
		case '<':
		case '=':
		case '!':
			return 6;
            break;
		case '&':
		case '|':
			return 7;
			break;
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
        case '^' :
			return 4;
			break;
		case '(' :
			return 5;
			break;
		default :
			return 6;
			break;
	}
	return 6;
}
number *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	int  cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *a, *b, *z;
	a = (number *)malloc(sizeof(number));
	b = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	initNumber(a);
	initNumber(b);
	initNumber(z);
	int_stack is;
	char_stack cs;
	int_init(&is);
	char_init(&cs);
	prev = ERR;
	while(1) {
		t = getnext(exp, &reset);
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			return NULL;
		}
		if(t.type == OPERAND){
			int_push(&is, t.data.num);
		}
		else if(t.type == OPERATOR){
			curr_op = t.data.op;
			if(curr_op == '(')
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob)
				return NULL;
			if(!char_isempty(&cs)) {
				prev_op = char_top(&cs);
				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = char_pop(&cs);
					if(!int_isempty(&is)) {
						a = int_pop(&is);
					}
					else{
						char_push(&cs, prev_op);
						break;
					}
					if(!int_isempty(&is)) {
						b = int_pop(&is);
					}
					else {
						char_push(&cs, prev_op);
						int_push(&is, a);
						break;
					}
					if((prev_op == '/' || prev_op == '%') && a == 0) {
                            fprintf(stderr, "Mathematical error\n");
                            return NULL;
                    }
					switch (prev_op) {
						case '+' :
							z = addition(a, b);
							int_push(&is, z);
							break;
						case '-' :
							z = subtraction(b, a);
							int_push(&is, z);
							break;
						case '*' :
							z = multiplication(b, a);
							int_push(&is, z);
							break;
						case '/' :
							z = division(b, a);
							int_push(&is, z);
							break;
						case '%' :
							z = modulo(b, a);
							int_push(&is, z);
							break;
                        case '^' :
                            z=power(b, a);
                            int_push(&is, z);
                            break;
										break;
                        case '>':
                            z = compare(b,a);
                            int_push(&is,z);
                            break;
                        case '<':
                            z=compare(a,b);
                            int_push(&is,z);
                            break;
                        case '=':
                            z=isequal(a,b);
                            int_push(&is,z);
                            break;
                        case '!':
                            z=isnotequal(a,b);
                            int_push(&is,z);
                            break;
                        case '&':
                            z = logical_and(b,a);
                            int_push(&is,z);
                            break;
                        case '|':
                            z = logical_or(b,a);
                            int_push(&is,z);
                            break;
						case '(' :
							char_push(&cs, prev_op);
							int_push(&is, b);
							int_push(&is, a);
							break;
						default :
							return NULL;
							break;
					}
					if (prev_op == '(')
						break;
					if(!char_isempty(&cs))
						prev_op = char_top(&cs);
					else
						break;
				}
			}
			char_push(&cs, t.data.op);
			if(curr_op == ')') {
				ch = char_pop(&cs);
				cnt_cb--;
				ch = char_pop(&cs);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			if(cnt_ob == cnt_cb) {
				while(!char_isempty(&cs)) {
					if(!int_isempty(&is)) {
						a = int_pop(&is);
					}
					else {
						fprintf(stderr, "Less no.of operands in the expression.\n");
                                return NULL;
					}
					if(!int_isempty(&is)) {
						b = int_pop(&is);
					}
					else {
						fprintf(stderr, "Less no.of operands in the expression.\n");
                            return NULL;
					}
					ch = char_pop(&cs);
					if((ch == '/' || ch == '%') && a == 0) {
						fprintf(stderr, "Mathematical error\n");
						return NULL;
					}
					switch(ch) {
						case '+' :
							z = addition(b, a);
							int_push(&is, z);
							break;
						case '-' :
							z = subtraction(b, a);
							int_push(&is, z);
							break;
						case '*' :
							z = multiplication(b, a);
							int_push(&is, z);
							break;
						case '/' :
							z = division(b, a);
							int_push(&is, z);
							break;
						case '%' :
							z = modulo(b, a);
							int_push(&is, z);
							break;
                        case '^'  :
                            z= power(b,a);
                            int_push(&is,z);
                            break;
						case '>':
                            z = compare(b,a);
                            int_push(&is,z);
                            break;
                        case '<':
                            z=compare(a,b);
                            int_push(&is,z);
                            break;
                        case '=':
                            z=isequal(a,b);
                            int_push(&is,z);
                            break;
                        case '!':
                            z=isnotequal(a,b);
                            int_push(&is,z);
                            break;
                        case '&':
                            z = logical_and(b,a);
                            int_push(&is,z);
                            break;
                        case '|':
                            z = logical_or(b,a);
                            int_push(&is,z);
                            break;
						default :
							return NULL;
					}
				}
			}
			else {
				fprintf(stderr, "Error in Given Expression\n");
				return NULL;
			}
			if(!int_isempty(&is)){
				z = int_pop(&is);
				if(int_isempty(&is))
					return z;
				else {
                    fprintf(stderr, "Less Operators in the Expression\n");
                    return NULL;
                }
			}
			else {
				fprintf(stderr, "Less Operands in the Expression\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
			return NULL;
		}
		prev = curr;
	}
}

int readline(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}
