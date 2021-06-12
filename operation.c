#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "number_ADT.h"
#include "operation.h"
/* Used to Destroy given Number
*/
void deleteNum(number *n) {
	if (n->head == NULL)
		return;
	node *q;
	do {
		q = n->head;
		n->head = n->head->next;
		free(q);
	} while (n->head != NULL);
	n->tail = NULL;
	n->dec = 0;
	n->sign = 0;
	return;
}
/* Number_ADT converted to double datatype
*/
double NumToDouble(number a) {
	node *p = NULL;
	p = a.head;
	double num2 = 0;
	while (p && p->num!= '.') {
		num2 = num2 * 10 + (p->num);
		p = p->next;
	}
	int mul = 10;
	if (p && p->num == '.')
		p = p->next;
	while (p) {
		num2 = num2 + (double) (p->num - '0') / mul;
		mul = mul * 10;
		p = p->next;
	}
	if (a.sign == MINUS)
		num2 = -num2;

	return num2;
}

/* Adding zero from last(to make equal after decimal point)*/
void afterdeciamlzero(number *a, number *b) {
	int i;
	if(a->dec > b->dec) {
		int diff = a->dec - b->dec;
		for(i = 0; i < diff; i++) {
			append(b, '0');
			b->dec++;
		}
	}
	else if(b->dec > a->dec) {
		int diff = b->dec - a->dec;
		for(i = 0; i < diff; i++) {
			append(a, '0');
			a->dec++;
		}
	}
}

/* Adding zero from front(to make equal before decimal point)*/
void beforedecimalzero(number *a, number *b) {
	int diff;
	diff = length(*a) - length(*b);
	if(diff > 0) {
		int i = 0;
		while(i < diff) {
			appendleft(b, 0);
			i++;
		}
	}
	else if(diff < 0) {
		int i = 0;
		diff = -diff;
		while(i < diff) {
			appendleft(a, 0);
			i++;
		}
	}
}

/*Comparing with Zero
    returns 0 if no.is zero
    else return 1
*/
int zeroEqual(number a) {
	int i, flag = 0;
	node *p = a.head;
	for(i = 0; i < length(a); i++) {
		if(p->num != 0)
			flag = 1;
		 p = p->next;
	}
	return flag;
}

/* Copying
    first no. into second
*/
void copyNumber(number *a, number *b) {
	int i, no, len;
	char ch;
	len = length(*a);
	node *t1 = a->head;
	for(i = 0; i < len; i++) {
		no = t1->num;
		ch = no + '0';
		append(b, ch);
		t1 = t1->next;
	}
	b->dec = a->dec;
	b->sign = a->sign;
	return;
}
//Addition Operation on giver number_ADT
number *addition(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	afterdeciamlzero(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = subtraction(b, a);
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = subtraction(a, b);
		}
	}
	else if(a->sign == b->sign) {
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		node *t1 = a->tail;
		node *t2 = b->tail;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == MINUS)
			ans->sign = MINUS;
		else
			ans->sign = PLUS;
		if(len_a >= len_b) {
			for(i = 1; i <= len_b; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++) {
				n1 = t1->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
			}
		}else {
			for(i = 1; i <= len_a; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->dec = a->dec;
		if(carry != 0)
			appendleft(ans, carry);
	}
	return ans;
}

/* Comparing number one with two and
        returns 1 if number 1 is greater
        returns -1 if number 1 is greater
        else 0
*/
int comparision(number a, number b) {
	beforedecimalzero(&a, &b);
	afterdeciamlzero(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;  //i.e. number a greater than number b.
		else if(p->num < q->num)
			return -1;  //i.e. a is less than b.
		p = p->next;
		q = q->next;
	}
	return 0;    //i.e. both numbers are equal.
}
//Subtraction operation on giver number_ADT.
number *subtraction(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	afterdeciamlzero(a, b);
	beforedecimalzero(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = addition(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = addition(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == MINUS) {
			a->sign = b->sign = PLUS;
			ans = subtraction(b, a);
		}
		else if(a->sign == PLUS) {
			int n1, n2, diff, borrow = 0, i, len;
			node *t1 = a->tail;
			node *t2 = b->tail;
			len = length(*b);
			if(comparision(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(comparision(*a, *b) == -1) {
				ans->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(comparision(*a, *b) == 0) {
					appendleft(ans, 0);
				}
			}
		}
	}
	ans->dec = a->dec;
	return ans;
}
//Multiplication Operation on given two number_ADT
number *multiplication(number *a, number *b) {
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	if((zeroEqual(*a) == 0) || (zeroEqual(*b) == 0)) {
		append(ans, '0');
		return ans;
	}
	int lengthdiff;
	if(a->sign == b->sign) {
		ans->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else {
		ans->sign = MINUS;
		a->sign = b->sign = PLUS;
	}
	lengthdiff = length(*a) - length(*b);
	if(lengthdiff < 0) {
		ans = multiplication(b, a);
		return ans;
	}
	else {
		node *t1, *t2;
		int len_a = length(*a);
		int len_b = length(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b->tail;
		for(i = 0; i < len_b; i++) {
			t1 = a->tail;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			appendleft(ans, tempresult[i]);
		}
		ans->dec = a->dec + b->dec;
		return ans;
	}
}
//Division Operation on given two number_ADT.
number *division(number *m, number *n){
	if(zeroEqual(*n) == 0) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	zeroRemov(m);
	zeroRemov(n);

	int k = m->dec > n->dec ? m->dec : n->dec;
	int i = 0;

	while(i < k) {
		if(m->dec > 0)
			m->dec--;
		else
			append(m, '0');
		if(n->dec > 0)
			n->dec--;
		else
			append(n, '0');
		i++;
	}
	i = 9;
	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	ans = (number *)malloc(sizeof(number));
	pro = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));

	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	node *p = m->head;
	char ch = p->num + '0';
	append(d, ch);
	while(q->dec < SCALE){
		while(i >= 0){
			appendleft(c, i);
			pro = multiplication(n, c);
			ans = subtraction(d, pro);
			if(ans->sign != MINUS) {
				append(q, i + '0');
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			append(d, ch);
		}
		else{
			q->dec++;
			append(d, '0');
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
	return q;
}

/* remainder finding mathod
FORMULA stated as remainder = a - floor division(a/b) * b
*/
number *modulo(number *a, number *b) {
	if(zeroEqual(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == MINUS) {
		tempsign = MINUS;
		a->sign = b->sign = PLUS;
	}
	else {
		tempsign = PLUS;
		a->sign = b->sign = PLUS;
	}
	afterdeciamlzero(a, b);
	int a_dec = a->dec;
	number *ans = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(ans);
	initNumber(temp);
	temp = division(a, b);
	if(temp->dec != 0) {
		int pos = length(*temp) - 1;
		while(temp->dec != 0) {
			remov(temp, pos);
			temp->dec--;
			pos--;
		}
	}
	temp = multiplication(temp, b);
	ans = subtraction(a, temp);
	ans->sign = tempsign;
	ans->dec = a_dec;
	return ans;
}
void validate(char *line) {
	int i;
	for(i = 0; i < strlen(line); i++) {
		if(line[i] == '(') {
			int j = 1;
			while(1) {
				if(line[i + j] == ' ') {
					j++;
				}
				else {
					break;
				}
			}
			if((line[i + j] == '-') || (line[i + j] == '+')) {
				int temp = strlen(line);
				while(temp >= i + j) {
					line[temp + 1] = line[temp];
					temp--;
				}
				line[i + j] = '0';
			}
		}
	}
}
/*POWER function  - returns Power(a^b)
*/
number *power(number *a,number *b) {
	number *power1=(number *)malloc(sizeof(number));
	initNumber(power1);
    number *n1=(number *)malloc(sizeof(number));
	append(power1, '1');
	initNumber(n1);
	double expo = NumToDouble(*b);
	int exponent;

	if (expo == (int) expo) {

	} else {
		printf("Warning : Exponent contains decimal values. Considering exponent as the equivalent integer\n");
	}

	exponent = (int) expo;


	int i, sign = PLUS;

	if (exponent < 0) {
		sign = MINUS;
		exponent = -exponent;
	}

	for (i = 0; exponent; i++) {
		if (exponent % 2) {
			n1 = power1;
			length(*power1);
			length(*a);
			power1 = multiplication(power1,a);
			deleteNum(n1);
		}
		n1 = a;
		length(*a);
		a = multiplication(a, a);
		deleteNum(n1);
		exponent = exponent / 2;
	}

	deleteNum(a);


	if (sign==MINUS) {
		n1 = power1;
		number *one=(number *)malloc(sizeof(number));
		initNumber(one);
		append(one, '1');
		length(*one);
		length(*power1);
		power1 = division(one, power1);
		deleteNum(n1);
	}

	return power1;
}
number *logical_and(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (zeroEqual(*a)!=0 && zeroEqual(*b)!=0)
        	append(result,'1');
	else append(result,'0');
	return result;

}
number *logical_or(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (zeroEqual(*a)!=0 || zeroEqual(*b)!=0)
        	append(result,'1');
	else append(result,'0');
	return result;

}

number *isequal(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (comparision(*a, *b)==0 && comparision(*b, *a)==0)
        	append(result,'1');
	else append(result,'0');
	return result;
}

number *isnotequal(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (!(comparision(*a, *b)==0 && comparision(*b, *a)==0))
        	append(result,'1');
	else append(result,'0');
	return result;
}
number *compare(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (comparision(*a, *b)==1)
        	append(result,'1');
	else append(result,'0');
	return result;
}
