/* CPSC 323 - Assignment #2
* Names: Rogelio Negrete, Ivan Vu, Angelo Salac
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

int eval_operation(char operation, int operand1, int operand2)
{
	if (operation == '+')
		return operand1 + operand2;
	else if (operation == '-')
		return operand1 - operand2;
	else if (operation == '*')
		return operand1 * operand2;
	else if (operation == '/')
		return operand1 / operand2;
	else
	{
		cout << "Unexpected Error \n";
		return -1;
	}
}

void process_expression(string expression)
{
	unordered_map<string, int> dict;
	stack<int> stack;
	string word = "";
	bool digitfound = false;

	for (int i = 0; i < expression.length(); i++)
	{
		// check for operations
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
		{
			int operand1 = stack.top(); stack.pop();
			int operand2 = stack.top(); stack.pop();

			// push computed value back onto stack
			stack.push(eval_operation(expression[i], operand1, operand2));

		}
		else if (isspace(expression[i]))
		{

			// check if the first letter of word is a valid digit
			if (word[0] - '0' >= 0 && word[0] - '0' <= 9)
			{
				cout << "Its a digit! " << word << endl;
				int x = stoi(word);
				stack.push(x);
			}
			// check if current element is NOT in our dict
			else if (dict.count(word) == 0)
			{	
				cout << "Loop #: " << i << endl;
				char char_value;
				int int_value;
				// Prompt user for the value of "expression[i]"
				cout << "\nEnter the value of " << word << ": ";
				cin >> char_value;
				int_value = char_value - '0'; // quick way to convert from char to int			
				stack.push(int_value); // push int_value to the stack 
				dict.emplace(word, int_value); // store into our dict for future use
				
			}
			else // current element is in our dict
			{
				int int_value = dict.find(word)->second; // find our match in the dict
				stack.push(int_value); // push int_value to the stack 
			}
			word.clear(); // clear out word 
		}
		// base case - there should only be one value left in the stack which is the final value
		else if (expression[i] == '$' && !stack.empty())
		{
			cout << "Final Value: " << stack.top() << endl;
		}
		else // found to be a char[a-z]
		{
			word += expression[i];
		}
	}

}

void repeat_prompt()
{
	char user_input;
	cout << "\nContinue (y/n)? ";
	cin >> user_input;

	if (user_input == 'n')
		exit(0);
	else if (user_input != 'y')
	{
		cout << "Incorrect input. Try again." << endl;
		repeat_prompt();
	}
}

int main() {
	cout << "ORIG VER MODIFIED" << endl;
	while (true)
	{
		string postfix_expression;
		cout << "Enter a postfix expression with a $ at the end: ";
		getline(cin, postfix_expression);
		process_expression(postfix_expression);
		repeat_prompt();
		cin.ignore(1000, '\n');
	}

}