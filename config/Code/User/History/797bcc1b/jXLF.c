#include <stdio.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    int elements[MAX_SIZE];
} stack;

void push(int ele) {
    stack.elements[stack.top++] = ele;
}

int top() {
    return stack.elements[stack.top - 1];
}

int pop() {
    return stack.elements[--stack.top];
}

int empty() {
    return stack.top == 0;
}

int main(int argc, char* argv[]) {
    stack.top = 0;
    push(3);
    push(2);
    push(1);

    int a = top();
    int b = pop();
    int c = top();

    printf("a = %d, b = %d, c = %d\n", a, b, c);

    return 0;
}