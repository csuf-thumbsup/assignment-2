/* CPSC 323 - Assignment #2
* Names: Rogelio Negrete, Ivan Vu, Angelo Salac
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

int eval_operation(string operation, int operand1, int operand2)
{
	if (operation == "+")
		return operand1 + operand2;
	else if (operation == "-")
		return operand1 - operand2;
	else if (operation == "*")
		return operand1 * operand2;
	else if (operation == "/")
		return operand1 / operand2;
	else
	{
		cout << "Unexpected Error \n";
		return -1;
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

bool is_number(const string &s)
{
	for (string::const_iterator x = s.begin(); x != s.end(); x++)
		if (!isdigit(*x)) return false;
	return true;
}

void process_expression(vector<string> expression)
{
	unordered_map<string, int> dict;
	stack<int> stack;

	for (int i = 0; i < expression.size(); i++)
	{
		// check for operations
		if (expression.at(i) == "+" || expression.at(i) == "-" || expression.at(i) == "*" || expression.at(i) == "/")
		{
			int operand1 = stack.top(); stack.pop();
			int operand2 = stack.top(); stack.pop();

			// push computed value back onto stack
			stack.push(eval_operation(expression.at(i), operand1, operand2));
		}
		// found to be a number
		else if (is_number(expression.at(i)))
		{
			stack.push(stoi(expression.at(i)));
		}
		// check for negative numbers
		else if (expression.at(i).substr(0,1) == "-" && is_number(expression.at(i).substr(1)))
		{
			stack.push(stoi(expression.at(i)));
		}
		// base case - there should only be one value left in the stack which is the final value
		else if (expression.at(i) == "$" && !stack.empty())
		{
			cout << "Final Value: " << stack.top() << endl;
		}
		else // word or char
		{
			// check if current element is NOT in our dict
			if (dict.count(expression.at(i)) == 0)
			{
				char char_value;
				int int_value;
				// Prompt user for the value of "expression.at(i)"
				cout << "\nEnter the value of " << expression.at(i) << ": ";
				cin >> char_value;
				int_value = char_value - '0'; // quick way to convert from char to int			
				stack.push(int_value); // push int_value to the stack 
				dict.emplace(expression.at(i), int_value); // store into our dict for future use
			}
			else // current element is in our dict
			{
				int int_value = dict.find(expression.at(i))->second; // find our match in the dict
				stack.push(int_value); // push int_value to the stack 
			}
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
	cout << "Version with VECTOR" << endl;
	while (true)
	{
		string postfix_expression;
		cout << "\nEnter a postfix expression with a $ at the end: ";
		getline(cin, postfix_expression);
		process_expression(split(postfix_expression, ' '));
		repeat_prompt();
		cin.ignore(1000, '\n');
	}
}