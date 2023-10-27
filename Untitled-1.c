#include<stdio.h>
#define size 100
typedef struct stack{
    int arr[size];
    int top;
}stack;

stack stk;
char postfix[size];

int isEmpty(){
    return stk.top==-1;
}
int isFull(){
    return stk.top == size-1;
}
void push(char x){
    if(!isFull()){
        stk.top++;
        stk.arr[stk.top] = x;
    }
    else printf("Stack is Full");
}
int pop(){
    if(!isEmpty()){
        int x = stk.arr[stk.top];
        stk.top--;
        return x;
    }
    else {
        printf("Stack is Empty");
        return 0;
    }
}
int peek(){
    if(!isEmpty()){
        return stk.arr[stk.top];
    }
}
int precedence(char top_op, char s_op2){
    if(top_op =='$' ||top_op =="*" || top_op=='/' || top_op=="%"){
        return top_op !='$';
        // if(s_op=='$')
        //  return 0;
        // else return 1;
    }
    else{
        if(s_op2 == '+' || s_op2 == '-')
            return 1;
        return 0;
    }
}
void infix_postfix(char infix[]){
    int i=0,j=0;
    char s;
    while(infix[i]!='\0'){
        s = infix[i++];
        if(s>='a' && s<='z' || s>='A' && s<='Z' || s>='0' && s<='9'){
            postfix[j++] = s;
        }
        else if(isEmpty() || s=='('){
            push(s);
        }
        else if(s==')'){
            while(peek() != '('){
                postfix[j++] = pop();
            }
            pop();
        }
        else{
            while(!isEmpty() && peek() != '(' && precedence(peek(),s)){
                postfix[j++] = pop();
            }
            push(s);
        }
    }
    while(!isEmpty()){
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main(){
    stk.top = -1;
    char infix[size];
    printf("Enter an infix Expression: ");
    gets(infix);
    printf("Infix: %s\n",infix);
    infix_postfix(infix);
    printf("Postfix: %s", postfix);
}