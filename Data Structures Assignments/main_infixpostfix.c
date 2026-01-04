#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }
int empty() { return top == -1; }

int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    char expr[MAX];
    int i;       /* for döngüsü için */
    char c;      /* her karakter için */

    printf("Enter infix: ");
    scanf("%s", expr);

    printf("Postfix: ");

    for (i = 0; expr[i] != '\0'; i++) {
        c = expr[i];

        if (isalnum((unsigned char)c)) {
            printf("%c", c);
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (!empty() && peek() != '(')
                printf("%c", pop());
            pop(); /* '(' karakterini yýðýndan at */
        }
        else { /* operator ise */
            while (!empty() && prec(peek()) >= prec(c))
                printf("%c", pop());
            push(c);
        }
    }

    while (!empty())
        printf("%c", pop());

    printf("\n");
    return 0;
}

