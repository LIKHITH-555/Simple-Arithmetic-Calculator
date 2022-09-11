#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<math.h>
using namespace std;

class CNode{
    public:
    char data;
    CNode *next;
};

class Node{
    public:
    float data;
    Node *nxt;
};

class Stack1{
    public:
    CNode *ctop;
    public:
      Stack1(){ctop=NULL;};
      void push(char c);
      char pop();
      bool isEmpty();
};

void Stack1::push(char c){
    CNode *t = new CNode;
    if(t==NULL){
        printf("Stack overflow\n");
    }
    else{
        t->data = c;
        t->next = NULL;
        if(ctop==NULL){
            ctop = t;
        }
        else{
            t->next = ctop;
            ctop = t;
        }
    }
}

char Stack1::pop(){
    CNode *p;
    char x;
    if(ctop==NULL){
        printf("Stack undeflow\n");
        return 0;
    }
    else{
        p = ctop;
        ctop = ctop->next;
        x = p->data;
        delete p;
        return x;
    }
}

bool Stack1::isEmpty(){
    if(ctop==NULL) return true;
    else return false;
}

class Stack2{
    Node *top;
    public:
       Stack2(){top=NULL;};
       void Push(int x);
       float Pop();
       bool IsEmpty();
};

void Stack2::Push(int x){
    Node *t = new Node;
    if(t==NULL){
        printf("Stack overflow\n");
    }
    else{
        t->data = x;
        t->nxt = NULL;
        if(top==NULL){
            top = t;
        }
        else{
            t->nxt = top;
            top = t;
        }
    }
}

float Stack2::Pop(){
    Node *p;
    float x;
    if(top==NULL){
        printf("Stack undeflow\n");
        return 0;
    }
    else{
        p = top;
        top = top->nxt;
        x = p->data;
        delete p;
        return x;
    }
}

bool Stack2::IsEmpty(){
    if(top==NULL) return true;
    else return false;
}

bool isOperand(char x){
    if(x=='+'||x=='-'||x=='*'||x=='/'||x=='('||x==')'||x=='^'){
        return false;
    }
    return true;
}

int outStackpre(char x){
    if(x=='+'||x=='-') return 1;
    else if(x=='*'||x=='/') return 3;
    else if(x=='^') return 6;
    else if(x=='(') return 7;
    else if(x==')') return 0;
    return 0;
}

int inStackpre(char x){
    if(x=='+'||x=='-') return 2;
    else if(x=='*'||x=='/') return 4;
    else if(x=='^') return 5;
    else if(x=='(') return 0;
    return 0;
}

string Convert(string infix,int n){
    char postfix[n],x;
    Stack1 st;
    int i=0,j=0;
    while(infix[i]!='\0'){
         if(isOperand(infix[i])){
            postfix[j++] = infix[i++];
         }
         else{
            if(st.isEmpty()){
                st.push(infix[i]);
                i++;
            }
            else if(outStackpre(infix[i])>inStackpre(st.ctop->data)){
                st.push(infix[i]);
                i++;
             }
             else if(outStackpre(infix[i])<=inStackpre(st.ctop->data)){
                x = st.pop();
                if(x=='('|| x==')'){}
                else{
                    postfix[j++] = x;
                }
             }
         }
    }
    while(!st.isEmpty()){
        char a = st.pop();
        if(a=='('||a==')'){}
        else{
            postfix[j++] = a;
        }
    }
    postfix[j] = '\0';
    return postfix;
}

int Sol(string s){
    Stack2 stk;
    int i=0;
    float x1,x2,result;
    for(i=0;s[i]!='\0';i++){
    if(isOperand(s[i])){
        stk.Push(s[i]-'0');
    }
    else{
        x1 = stk.Pop();
        x2 = stk.Pop();
        switch(s[i]){
            case '+':
            result = x2+x1;
            stk.Push(x2+x1);
            break;
            case '-':
            result = x2-x1;
            stk.Push(result);
            break;
            case '*':
            result = x2*x1;
            stk.Push(result);
            break;
            case '/':
            if(x1==0){
                printf("Invalid input\n");
                break;
            }
            result = x2/x1;
            stk.Push(result);
            break;
            case '^':
            result = pow(x2,x1);
            stk.Push(result);
            break;
        }
    }
    }
    return stk.Pop();
}

int main(){
    string s;
    int n;
    float result;
    cout<<"Enter you input using single digit numbers\n";
    cin>>s;
    n = s.length();
    result = Sol(Convert(s,n));
    cout<<result;
}
