#include "ExpTree.h"

node::node() {}

node::node(string _data, node* _left, node* _right, bool _isOperator)
{
	data = _data;
	left = _left;
	right = _right;
	//index = _index;
	isOperator = _isOperator;
	//level = -1;
}

node::~node()
{
	delete left;
	delete right;
}

node::node(const node &other)
{
	this->data = other.data;
	this->left = other.left;
	this->right = other.right;
	//this->index = other.index;
}

node& node::operator=(const node &other)
{
	this->data = other.data;
	this->left = other.left;
	this->right = other.right;
	//this->index = other.index;

	return *this;
}

ExpTree::ExpTree()
{
	root = nullptr;
}

/*
ExpTree::ExpTree(vector<string> postFix)
{
	CreateTree(postFix);
}
*/

ExpTree::~ExpTree()
{
	deleteTree(root);
}

void ExpTree::CreateTree(vector<string> postFix)
{
	//try
	//{
		vector<node*> Stack;
		//int index = 0; //append to new node and increment
		for (unsigned int i = 0; i < postFix.size(); i++)
		{
			string token = postFix.at(i);
			//if token is an operand
			if (!isOperator(token))
			{
				Stack.push_back(createNode(token, false));
				//index++;
			}
			//if token is an operator
			else
			{
				if (Stack.size() < 2)
				{
					throw std::invalid_argument("Error: Invalid postFix expression.");
				}
				else
				{
					node *T1 = Stack.at(Stack.size() - 1);
					Stack.pop_back();
					node *T2 = Stack.at(Stack.size() - 1);
					Stack.pop_back();
					node *Root = createNode(token, true);
					Root->left = T2;
					Root->right = T1;
					Stack.push_back(Root);
				}
			}
		}
		if (Stack.size() != 1)
		{
			throw std::invalid_argument("Error: Invalid postFix expression.");
		}
		else
		{
			root = Stack.at(Stack.size() - 1);
		}
	//}
	//catch (std::invalid_argument &exc)
	//{
	//	cerr << exc.what() << endl;
	//}
}

//Implement --------------------------------------------------------------------------------------------------
void ExpTree::SetVariableValues(vector<int> values)
{
	//try
	//{
		vector<node*> Nodes;
		listNodesWithOperands(root, &Nodes);
		if (Nodes.size() != values.size())
		{
			throw std::invalid_argument("Invalid infix exception\n");
		}

		for (unsigned int i = 0; i < Nodes.size(); i++)
		{
			//if (!(Nodes.at(i)->isOperator))
			//{
			Nodes.at(i)->value = values.at(i);
			//}
		}
	//}
	/*
	catch (std::invalid_argument &exc)
	{
		cerr << exc.what() << endl;
	}
	*/
}

int ExpTree::EvaluateTree()
{
	return computeTree(root);
}

void ExpTree::inOrderTraversalandPrint(ostream &out)
{
	printTree(out, root);
}
//Implement ---------------------------------------------------------------------------------------------------

bool ExpTree::isOperator(string s)
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

node* ExpTree::createNode(string data, bool isOperator)
{
	node *newNode = new node(data, nullptr, nullptr, isOperator);
	return newNode;
}

void ExpTree::deleteTree(node* root)
{
	if (root != nullptr)
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			root = nullptr;
		}
		else
		{
			deleteTree(root->left);
			deleteTree(root->right);
			root = nullptr;
		}
	}
}

void ExpTree::listNodesWithOperands(node* root, vector<node*> *Nodes)
{
	if (root != nullptr)
	{
		if (!(root->isOperator))
		{
			Nodes->push_back(root);
		}
		else
		{
			listNodesWithOperands(root->left, Nodes);
			listNodesWithOperands(root->right, Nodes);
			//Nodes->push_back(root);
		}
	}
}

int ExpTree::computeTree(node* root)
{
	if (root != nullptr)
	{
		if (!(root->isOperator))
		{
			return root->value;
		}
		else
		{
			if (root->data == "+")
			{
				return computeTree(root->left) + computeTree(root->right);
			}
			else if (root->data == "-")
			{
				return computeTree(root->left) - computeTree(root->right);
			}
			else if (root->data == "*")
			{
				return computeTree(root->left) * computeTree(root->right);
			}
			else if (root->data == "/")
			{
				return computeTree(root->left) / computeTree(root->right);
			}
			else if (root->data == "^")
			{
				double x = pow(computeTree(root->left), computeTree(root->right));
				int result;

				if (x > 0)
				{
					result = (int)(x + 0.3);
				}
				else
				{
					result = (int)(x - 0.3);
				}
				return result;
			}
		}
	}
	return 0;
}


void ExpTree::printTree(ostream &out, node *root)
{
	if (root != nullptr)
	{
		//Root holds an operand
		if (!(root->isOperator))
		{
			for (unsigned int i = 0; i < root->data.size(); i++)
			{
				out << root->data.at(i);
			}
			out << " ";
		}
		//Root holds an operator
		else
		{
			printTree(out, root->left);
			for (unsigned int i = 0; i < root->data.size(); i++)
			{
				out << root->data.at(i);
			}
			out << " ";
			printTree(out, root->right);
		}

	}
}


