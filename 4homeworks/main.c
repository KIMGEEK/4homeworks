#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char stack[MAX];
char notation[MAX];
int top = -1;
int arrIdx = -1;
int i = 0;
int notIdx = -1;
int stackInt[MAX];
int topInt = -1;

/*
a+b => ab+
a+b*c => abc*+
a*b+c => ab*c+
(a+b)*(c+d) => ab+cd+*
a+b+c+d =>ab+c+d+
(a+b)*(c-d/e) => ab+cde/-*
*/

char pop();
int push(char);
int isFull();
int isEmpty();
char nextToken(char arr[]);
int isp(char x);
int icp(char x);
char nextTokenNot(char arr[]);
int pushint(int n);
int popint();
int oper(char ch);

int calc(char notation[]);

int main() {
	char formula[100];
	char x;
	printf("Enter the fomula: ");
	scanf("%s", formula);
	x = nextToken(formula);
	while (x != NULL) {
		if (x >= '0' && x <= '9') {
			printf("%c ", x);
			notation[i] = x;
			i++;
		} else if (x == ')') {
			while (stack[top] != '(') {
				pop();
			}
			pop();
		} else if (top == -1) {
			push(x);
		} else {
			while (top > -1 && isp(stack[top]) >= icp(x)) {
				pop();
			}
			push(x);
		}
		x = nextToken(formula);
	}
	while (top > -1) {
		pop();
	}

	printf("\npostfix notation: %s", notation);

	calc(notation);

	return 0;
}

char pop() {
	isEmpty();
	char topelement;
	topelement = stack[top];
	if (stack[top] != '(') {
		printf("%c ", stack[top]);
		notation[i] = stack[top];
		i++;
	}
	top--;
	return topelement;
}

int push(char c) {
	isFull();
	top++;
	stack[top] = c;
	return 1;
}

int isEmpty() {
	if (top == -1) return 0;
}

int isFull() {
	if (top == MAX - 2) return 0;
}

char nextToken(char arr[]) {
	arrIdx++;
	return arr[arrIdx];
}

int isp(char x) {
	switch (x)
	{
	case '(':
		return 0;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	default:
		break;
	}
}

int icp(char x) {
	switch (x)
	{
	case '(':
		return 3;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	default:
		break;
	}
}

int calc(char notation[]) {
	char x;
	int n;

	x = nextTokenNot(notation);
	while (x != NULL) {
		if (x >= '0' && x<='9') {
			n = atoi(x);
			pushint(n);
		} else {
			oper(x);
		}
	}

	printf("\nResult: %d", stackInt[0]);

	return 0;
}

char nextTokenNot(char arr[]) {
	notIdx++;
	return arr[notIdx];
}

int popint() {
	isEmpty();
	int topelement;
	topelement = stack[top];
	top--;
	return topelement;
}

int pushint(int c) {
	isFull();
	topInt++;
	stackInt[topInt] = c;
	return 1;
}

int oper(char ch) {
	int result;
	switch (ch)
	{
	case '+':
		result = popint() + popint();
		pushint(result);
		break;
	case '-':
		result = popint() - popint();
		pushint(result);
		break;
	case '*':
		result = popint() * popint();
		pushint(result);
		break;
	case '/':
		result = popint() / popint();
		pushint(result);
		break;
	default:
		break;
	}
}