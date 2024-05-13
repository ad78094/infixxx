#include <iostream>
#include <cstdlib>
using namespace std;

// define default capacity of stack
#define SIZE 100

// Class for stack
template <class X>
class stack
{
    X *arr;
    int top;
    int capacity;

public:
    stack(int size = SIZE)   // constructor
    {
         arr = new X[size];
        capacity = size;
        top = -1;
    }

// function to add an element x in the stack
    void push(X newElement)
    {
         if (isFull())
        {
            cout << "OverFlow\n";
            return ;
        }

        arr[++top] = newElement;
    }

// function to pop top element from the stack
    void pop()
    {
    // check for stack underflow
        if (isEmpty())
        {
            cout << "UnderFlow\n";
            return ;
        }


        // decrease stack size by 1 and (optionally) return the popped element
        arr[top--];
        return ;
    }


    // function to return top element in a stack
    X peek()
    {
        return arr[top];
    }

    // Utility function to return the size of the stack
    int size()
    {
        return top+1;
    }
    // Utility function to check if the stack is empty or not
    bool isEmpty()
    {
        return top == -1;    // or return size() == 0;
    }

// Utility function to check if the stack is full or not
    bool isFull()
    {
        return top == capacity - 1;    // or return size() == capacity;
    }

    // destructor
    ~stack(){
        delete[] arr;
    }
};

int prec(char c)
{
    if(c == '^')
    return 3;
    else if(c == '*' || c == '/')
    return 2;
    else if(c == '+' || c == '-')
    return 1;
    else
    return -1;
}
// The main function to convert infix expression
//to postfix expression
string infixToPostfix(string s)
{
    stack<char> st(SIZE);//calling our stack
    st.push('N');
    int l = s.length();
    string ns;
    for(int i = 0; i < l; i++)
    {

        // If the scanned character is
        // an operand, add it to output string.
        if((s[i] >= 'a' && s[i] <= 'z') ||
           (s[i] >= 'A' && s[i] <= 'Z'))
        ns+=s[i];

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if(s[i] == '(')

        st.push('(');

        // If the scanned character is an ‘)’,
        // pop and to output string from the stack
        // until an ‘(‘ is encountered.
        else if(s[i] == ')')
        {
            while(st.peek() != 'N' && st.peek() != '(')
            {
                char c = st.peek();
                st.pop();
               ns += c;
            }
            if(st.peek() == '(')
            {
                char c = st.peek();
                st.pop();
            }
        }

        //If an operator is scanned
        else{
            while(st.peek() != 'N' && prec(s[i]) <=
                                   prec(st.peek()))
            {
                char c = st.peek();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }

    }

    // Pop all the remaining elements from the stack
    while(st.peek() != 'N')
    {
        char c = st.peek();
        st.pop();
        ns += c;
    }
    return ns;

}
//main function to test our program
int main()
{

  string infix,postfix;
  cout<<"Enter the String : ";
  cin>>infix;


  postfix = infixToPostfix(infix);
  cout<<"\nPrefix of given expression is: ";
  cout<<postfix;

    return 0;
}
