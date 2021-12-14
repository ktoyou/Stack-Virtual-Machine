#include <iostream>
#include <string>

#define STACK_SIZE 5
#define MAX_CODE_LENGTH 32

int sp;
int cp;
int stack[STACK_SIZE];

typedef enum {
	ADD = 0x1,
	MUL = 0x2,
	PRINT = 0x3,
	EXIT = 0x4,
	DIV = 0x5,
	PUSH = 0x6,
	POP = 0x7,
	ENTER = 0x8

} mnemonics;

void isFull() {
	if(sp >= STACK_SIZE) {
		printf("STACKOVERFLOW\n");
		exit(-1);
	}
}

int execOpcode(int opcode, int *code) 
{
	int a;
	int b;
	switch (opcode)
	{
	case ADD:
		a = stack[sp--];
		b = stack[sp--];
		sp++;
		stack[sp] = a + b;
		printf("ADD=%i\n", stack[sp]);
	break;
	case MUL:
		a = stack[sp--];
		b = stack[sp--];
		sp++;
		stack[sp] = a * b;
		printf("MUL=%i\n", stack[sp]);
	break;
	case DIV:
		a = stack[sp--];
		b = stack[sp--];
		sp++;
		stack[sp] = a / b;
		printf("DIV=%i\n", stack[sp]);
	break;
	case PUSH:
		isFull();
		sp++;
		stack[sp] = code[++cp];
		printf("PUSH=%i\n", stack[sp]);
	break;
	case POP:
		a = stack[sp--];
		printf("POP=%i\n", a);
	break;
	case ENTER:
		isFull();
		printf("ENTER=");
		scanf("%i", &stack[++sp]);
	break;
	case EXIT:
		exit(0);
	break;
	case PRINT:
		printf("LAST=%i\n", stack[sp]);
	break;
	default:
		printf("ERR SYNTAX IN %i", cp);
		break;
	}
}

int run(int *code) 
{
	cp = 0;
	sp = 0;
	while(true) {
		execOpcode(code[cp], code);
		cp++;
	}
}

int main(int argc, char const *argv[])
{
	int code[MAX_CODE_LENGTH] {
		ENTER,
		ENTER,
		ADD,
		PRINT,
		EXIT
	};
	run(code);
}