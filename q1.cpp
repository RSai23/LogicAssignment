#include<iostream>
#include<cstring>
#include<bits/stdc++.h>

using namespace std;
//done by R.Sairam and Tanishk Agarwal
struct Node
{
    char data;
    Node* left;
    Node* right;
};
/**the function returns the relative precedence for a given char*/
int precedence(char c)//returns precedence for various operators
{
    if(c=='~')return 3;
    if(c=='^')return 2;
    if(c=='V')return 1;
    if(c=='>')return 0;
    return -1;
}

class Stack
{

    public:
        char arr[20];
        int top=-1;
        void append(char x)
        {
            if(top==19)
            {
                cout<<"Overflow!"<<endl;
            }
            else
            {
                arr[++top]=x;
            }

        }
        void pop()
        {
            top--;
        }

};
///instances of stack class(global)
Stack s1;
Stack postfix;
/**the method converts infix to postfix and takes infix string as argument.*/
void infix_to_postfix(string x)
{
    for(int i=0;i<x.length();i++)
    {
        if((x[i]>='a'&&x[i]<='z')||((x[i]>='A' && x[i]<'V') || (x[i]>'V' && x[i]<='Z')))//operand
        {
          postfix.append(x[i]);
        }
        else if(x[i]=='>'||x[i]=='V'||x[i]=='^'||x[i]=='~')//operator
        {
            while(s1.top!=-1 && "s1.arr[s1.top]"!="(" && precedence(s1.arr[s1.top])>precedence(x[i]))
            {
                postfix.append(s1.arr[s1.top]);
                s1.pop();
            }
            s1.append(x[i]);
        }
        else if(x[i]=='(')//when infix exp has open bracket
        {
            s1.append(x[i]);
        }
        else if(x[i]==')')//when infix expression has a closed bracket
        {
            while(s1.top!=-1 && s1.arr[s1.top]!='(')
            {
                postfix.append(s1.arr[s1.top]);
                s1.pop();
            }
            s1.pop();
        }

    }
    while(s1.top!=-1)//emptying the stack and appending everything to postfix
        {

            postfix.append(s1.arr[s1.top]);
            s1.pop();
        }
    for(int i=0;i<postfix.top+1;i++)
    {
        cout<<postfix.arr[i];
    }
    cout<<"\n";
}
/**the method prints an inorder travesal of a parse tree and takes in the pointer to root of treee as parameter*/
void inorder(Node* x)
{

        if(x==nullptr)return;
        else if(x->data=='^'||x->data=='V'||x->data=='>'||x->data=='~')
        {
            cout<<"(";
            inorder(x->left);
            cout<<x->data;
            inorder(x->right);
            cout<<")";
        }
        else
        {
            inorder(x->left);
            cout<<x->data;
            inorder(x->right);
        }


}
/**the method returns a boolean and suggests whether c is a char or not*/
bool isOperator(char c)//return true if c is an operator
{
    if (c == '^' || c == 'V' ||c == '>' || c == '~' )
    return true;
    return false;
}
/**this method creates a new node with data=x*/
Node* newNode(char x)//creates a node with data=x
{
    Node *temp = new Node();
    temp->left = temp->right = NULL;
    temp->data= x;
    return temp;
}
/**this method converts a postfix expression to a parse tree*/
Node* postfix_to_parse(char postfix[])
{
    stack<Node *> s;
    Node *temp;//temp is a pointer to current node


    for (int i=0; i<strlen(postfix); i++)
    {

        if (!isOperator(postfix[i]))//executes when not an operator
        {
            temp = newNode(postfix[i]);//node created with data=postfix[i] and left and right as null
            s.push(temp);
        }
        else
        {
            if(postfix[i]=='~')//condition for negation as it has only one child.
            {
               temp=newNode(postfix[i]);
               temp->right=s.top();
               s.pop();
               temp->left=nullptr;
               s.push(temp);
            }
            else//condition for all other operators.
            {
            /*when an operator(binary) is encountered in postfix exp and let top two elements in stack be c1 and c2.
            create node with operator as data and c1 and c2 as children and then push into stack.*/
            temp = newNode(postfix[i]);
            temp->right = s.top();
            s.pop();
            temp->left = s.top();
            s.pop();
            s.push(temp);
            }
        }
    }
    temp = s.top();//temp points to the root node of the parse tree => root=temp
    s.pop();

    return temp;
}
int main()
{
    char infix[30];
    scanf("%s",infix);
    infix_to_postfix(infix);
    Node* root = postfix_to_parse(postfix.arr);
    inorder(root);
    return 0;


}

