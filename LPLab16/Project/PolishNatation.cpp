#include "PolishNatation.h"
#include <stack>
#include <list>
#include <iostream>

#define ENDEXPRECION '\n'
#define SIZESTACK 32
using namespace std;
bool polishNotation(char* expression);

int main()
{
	char expression[SIZESTACK];
	fgets(expression, SIZESTACK, stdin);
	polishNotation(expression);
}

bool polishNotation(char* expression/*int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable*/)
{
	stack <char> stack;
	list <char> operands;
	
	for (int i = 0; expression[i]; i++)
	{
		switch (expression[i])
		{
			case LEFTHESIS:
				stack.push(expression[i]);
				break;
			case RIGHTESIS:
				while (stack.top() != LEFTHESIS)
				{
						operands.push_back(stack.top());
						stack.pop();
				}
				stack.pop();
				break;
			case ADD:
			case SUB:
				if (stack.empty()) 
				{
					stack.push(expression[i]);
				}
				else if(stack.top() == MUL ||
						stack.top() == DIV ||
						stack.top() == ADD || 
						stack.top() == SUB)
				{
					operands.push_back(stack.top());
					stack.pop();
					stack.push(expression[i]);
				}
				else
					stack.push(expression[i]);
				break;
			case MUL:
			case DIV:
				if (stack.empty())
				{
					stack.push(expression[i]);
				}
				else if(stack.top() == MUL || stack.top() == DIV)
				{
					operands.push_back(stack.top());
					stack.pop();
					stack.push(expression[i]);
				}
				else
					stack.push(expression[i]);
				break;
			case ENDEXPRECION:
				while (!stack.empty())
				{
					operands.push_back(stack.top());
					stack.pop();
				}
			default:
			{
				operands.push_back(expression[i]);
				break;
			}
		}
		
		
	
	}

	while (!operands.empty()) {

		cout << operands.front();
		operands.pop_front();

	}
	return true;

}