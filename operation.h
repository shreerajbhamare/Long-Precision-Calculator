#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#define SCALE 15 /*Maintaining precesion(boundary to floating numbers)*/

int comparision(number a, number b);
void decimalEqual(number *a, number *b);
void deleteNum(number *n);
double NumToDouble(number a);
number *addition(number *a, number *b);
number *subtraction(number *a, number *b);
number *multiplication(number *a, number *b);
number *division(number *a, number *b);
number *factorial(number *a);
number *modulo(number *a, number *b);
number *power(number *a, number *b);
number *logical_and(number *a, number *b);
number *logical_or(number *a, number *b);
number *isequal(number *a,number *b);
number *isnotequal(number *a,number *b);
number *compare(number *a, number *b);


#endif
