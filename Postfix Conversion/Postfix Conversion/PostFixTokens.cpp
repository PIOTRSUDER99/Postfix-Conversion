#include "PostFixTokens.h"

PostFixTokens::PostFixTokens() {}

PostFixTokens::PostFixTokens(vector<string> inFix)
{
	vector<string> inFixTokens;
	vector<string> postFixTokens;
	vector<string> Stack;
	setInFixTokens(inFix);
	createPostFix();


}

void PostFixTokens::setInFixTokens(vector<string> inFix)
{
	inFixTokens.clear();
	for (unsigned int i = 0; i < inFix.size(); i++)
	{
		inFixTokens.push_back(inFix.at(i));
	}
}

vector<string> PostFixTokens::getPostFixTokens()
{
	createPostFix();
	return postFixTokens;
}
vector<string> PostFixTokens::getInFixTokens()
{
	return inFixTokens;
}

void PostFixTokens::createPostFix()
{

	//try
	//{
		if (!checkIfValid(&inFixTokens))
		{
			throw std::invalid_argument("Invalid Infix");
		}

		//Algorithm
		postFixTokens.clear();

		//Create the stack
		//vector<string> Stack;

		for (unsigned int i = 0; i < inFixTokens.size(); i++)
		{
			string token = inFixTokens.at(i);
			//If the token is an operand append it to the expression
			if (!isOperator(token) && !isParenthesis(token))
			{
				postFixTokens.push_back(token);
			}
			else if (token == "(")
			{
				Stack.push_back(token);
			}
			else if (token == ")")
			{
				while (Stack.at(Stack.size() - 1) != "(")
				{
					//pop the stack and append at the end of the expression
					postFixTokens.push_back(Stack.at(Stack.size() - 1));
					if (Stack.size() == 0)
					{
						throw std::invalid_argument("Invalid Infix");
					}
					else
					{
						Stack.pop_back();
					}
				}
			}
			else
			{
				processOperator(token, &Stack, &postFixTokens);
			}
		}
		//pop the stack and append to expression
		for (int i = (Stack.size() - 1); i >= 0; i--)
		{
			if (Stack.at(i) != "(" && Stack.at(i) != ")")
			{
				postFixTokens.push_back(Stack.at(i));
			}
			if (Stack.size() == 0)
			{
				throw std::invalid_argument("Error: Tokens of inFixTokens are not a valid expression!");
			}
			else
			{
				Stack.pop_back();
			}
		}
	//}
	//catch (const std::invalid_argument& exc)
	//{
	//	cerr << exc.what() << endl;
	//}
}

void PostFixTokens::printPostFix()
{
	createPostFix();
	for (unsigned int i = 0; i < postFixTokens.size(); i++)
	{
		for (unsigned int j = 0; j < postFixTokens.at(i).size(); j++)
		{
			cout << postFixTokens.at(i).at(j);
		}
		cout << " ";
	}
	cout << endl;
}

void PostFixTokens::printInFix()
{
	for (unsigned int i = 0; i < inFixTokens.size(); i++)
	{
		for (unsigned int j = 0; j < inFixTokens.at(i).size(); j++)
		{
			cout << inFixTokens.at(i).at(j);
		}
		cout << " ";
	}
	cout << endl;
}

bool PostFixTokens::checkIfValid(vector<string> *inFix)
{
	//Check for parentheses not matching
	if (!parenthesesMatch(inFix))
	{
		return false;
	}

	//Check if an operator is at the beginnig or at the end of the expression
	if (isOperator(inFix->at(0)) || isOperator(inFix->at(inFix->size() - 1)))
	{
		return false;
	}


	for (unsigned int i = 0; i < (inFix->size() - 1); i++)
	{
		//Check for operators next to each other
		if (isOperator(inFix->at(i)) && isOperator(inFix->at(i + 1)))
		{
			return false;
		}

		//Check if operator before ")" or after "("

		if (isOperator(inFix->at(i)) && inFix->at(i + 1) == ")")
		{
			return false;
		}
		if (isOperator(inFix->at(i + 1)) && inFix->at(i) == "(")
		{
			return false;
		}

		//Check if operands are next to each other
		if (!isOperator(inFix->at(i)) && !isOperator(inFix->at(i + 1)) && !isParenthesis(inFix->at(i)) &&
			!isParenthesis(inFix->at(i + 1)))
		{
			return false;
		}

		//Check if operand after ")" or before "("
		if ((!isOperator(inFix->at(i)) && !isParenthesis(inFix->at(i))) && inFix->at(i + 1) == "(")
		{
			return false;
		}
		if ((!isOperator(inFix->at(i + 1)) && !isParenthesis(inFix->at(i + 1))) && inFix->at(i) == ")")
		{
			return false;
		}

		//Check for opening parenthesis after closing parenthesis, i.e. (...)(...)
		if (inFix->at(i) == ")" && inFix->at(i + 1) == "(")
		{
			return false;
		}
	}

	return true;


	//Check if operator before ")" or after "(". Exception: "-" after "(", e.g. (-2 + 4)
	//ADD THE EXCEPTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool PostFixTokens::parenthesesMatch(vector<string> *inFix)
{
	short count = 0;
	for (unsigned int i = 0; i < inFix->size(); i++)
	{
		if (inFix->at(i) == "(")
		{
			count += 1;
		}
		else if (inFix->at(i) == ")")
		{
			count -= 1;
		}

		if (count < 0)
		{
			return false;
		}
	}

	return count == 0;
}

bool PostFixTokens::isOperator(string s)
{
	if (s == "+" || s == "-" || s == "*" || s == "/" || s == "^")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PostFixTokens::isParenthesis(string s)
{
	if (s == "(" || s == ")")
	{
		return true;
	}
	else
	{
		return false;
	}
}



short PostFixTokens::getPrecedence(string s)
{
	if (s == "^")
	{
		return 4;
	}
	else if (s == "*" || s == "/")
	{
		return 3;
	}
	else if (s == "+" || s == "-")
	{
		return 2;
	}
	else if (s == "(" || s == ")")
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


void PostFixTokens::processOperator(string oper, vector<string> *Stack, vector<string> *Expression)
{
	//if the stack is empty push the operator on the Stack
	//also, if the operator is a parenthesis push it on the stack
	if (Stack->size() == 0) //Check this one **************************************
	{
		Stack->push_back(oper);
	}
	else
	{
		string topOp = Stack->at(Stack->size() - 1);
		if (getPrecedence(oper) > getPrecedence(topOp))
		{
			Stack->push_back(oper);
		}
		else if (oper == "^" && topOp == "^")
		{
			Stack->push_back(oper);
		}
		else
		{
			while (Stack->size() != 0 && getPrecedence(oper) <= getPrecedence(topOp) && !(oper == "^" && topOp == "^"))
			{
				//pop the top of the stack and append it to the expression
				if (topOp != "(" && topOp != ")")
				{
					Expression->push_back(topOp);
				}
				if (Stack->size() == 0)
				{
					throw std::invalid_argument("Error: Tokens of inFixTokens are not a valid expression!");
				}
				else
				{
					Stack->pop_back();
				}
				if (Stack->size() != 0)
				{
					topOp = Stack->at(Stack->size() - 1);
				}
			}
			if (oper != "(" && oper != ")")
			{
				Stack->push_back(oper);
			}
		}
	}
}

//Copy Constructor
PostFixTokens::PostFixTokens(const PostFixTokens &other)
{
	this->inFixTokens.clear();
	for (unsigned int i = 0; i < other.inFixTokens.size(); i++)
	{
		this->inFixTokens.at(i) = other.inFixTokens.at(i);
	}

	this->postFixTokens.clear();
	for (unsigned int i = 0; i < other.postFixTokens.size(); i++)
	{
		this->postFixTokens.at(i) = other.postFixTokens.at(i);
	}

	this->Stack.clear();
	for (unsigned int i = 0; i < other.Stack.size(); i++)
	{
		this->Stack.at(i) = other.Stack.at(i);
	}
}

//Assignment Operator

PostFixTokens& PostFixTokens::operator=(const PostFixTokens &other)
{
	this->inFixTokens.clear();
	for (unsigned int i = 0; i < other.inFixTokens.size(); i++)
	{
		this->inFixTokens.at(i) = other.inFixTokens.at(i);
	}

	this->postFixTokens.clear();
	for (unsigned int i = 0; i < other.postFixTokens.size(); i++)
	{
		this->postFixTokens.at(i) = other.postFixTokens.at(i);
	}

	this->Stack.clear();
	for (unsigned int i = 0; i < other.Stack.size(); i++)
	{
		this->Stack.at(i) = other.Stack.at(i);
	}

	return *this;
}

//Destructor
PostFixTokens::~PostFixTokens() {}