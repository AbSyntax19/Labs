LAB 3

'''

#include <stdio.h>
#include <stdlib.h>
#define max 10
int stack[max], top=-1, flag=1;
int i, temp, item, rev[max], num[max];
void push(){
if(top==(max-1)){
printf("Stack overflow");
}
else{
printf("Enter the elements to be inserted: ");
scanf("%d", &item);
top=top+1;
stack[top]=item;
}
}
void pop(){
if(top==-1){
printf("\nStack underflow\n");
flag=0;
}
else{
item=stack[top];
top=top-1;
}
}
void palindrome(){
i = 0;
if(top == -1){
printf("\nPush some elements into the stack first\n");
}
else{
while(top != -1){
rev[top] = stack[top]; // Copy the element from stack to 'rev' array
pop();
}
// Save the original position of the top pointer to restore it later
top = temp;
// Compare the elements of the stack with the reversed 'rev' array
for(i = 0; i <= temp; i++){
// Check if the current element of the stack matches the corresponding element
in 'rev'
if(stack[top--] == rev[i]){
if(i == temp){
printf("Palindrome\n");
return;
}
}
}
printf("Not a Palindrome\n");
}
}
void display(){
int i;
top=temp;
if(top==-1){
printf("\nStack is empty");
}
else{
printf("\nThe elements of the stack are: \n");
for(i=top; i>=0; i--){
printf("%d\n", stack[i]);
}
}
}
int main(){
int choice;
printf("\n---------Stack Operations --------- \n");
printf("1.Push 2.Pop 3.Palindrome 4.Display 5.Exit\n");
while(1){
temp=top;
printf("\nEnter your choice: ");
scanf("%d", &choice);
switch(choice){
case 1: push();
break;
case 2: pop();
if(flag)
printf("\nPopped element: %d\t", item);
temp=top;
break;
case 3: palindrome();
top=temp;
break;
case 4: display();
break;
case 5: exit(0);
break;
default:
printf("\nInvalid choice\n");
break;
}
}
return 0;
}

'''

LAB 4

'''

#define SIZE 50
#include <ctype.h>
#include <stdio.h>
char s[SIZE];
int top = -1;
void push(char elem)
{
s[++top] = elem;
}
char pop()
{
return (s[top--]);
}
int pr(char elem)
{
switch (elem)
{
case '#':
return 0;
case '(':
return 1;
case '+':
case '
-
':
return 2;
case '*':
case '/':
case '%':
return 3;
case '^':
return 4;
}
}
int main()
{
char infx[50], pofx[50], ch, elem;
int i = 0, k = 0;
printf("\nRead the infix expresssion: ");
scanf("%s", infx);
push('#');
while ((ch = infx[i++]) != '\0')
{
if (ch == '(')
{
push(ch);
}
else if (isalnum(ch))
{
pofx[k++] = ch;
}
else if (ch == ')')
{
while (s[top] != '(')
pofx[k++] = pop();
elem = pop();
}
else
{
while (pr(s[top]) >= pr(ch))
pofx[k++] = pop();
push(ch);
}
}
while (s[top] != '#')
pofx[k++] = pop();
pofx[k] =
'\0';
printf("\nGiven Infix expression: %s \nPostfix expression: %s\n\n", infx, pofx);
return 0;
}
