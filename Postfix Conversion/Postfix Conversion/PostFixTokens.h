#ifndef PostFixTokens_h
#define PostFixTokens_h
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
class PostFixTokens {
public:
	PostFixTokens();
	PostFixTokens(vector<string> inFix);
	~PostFixTokens();
	vector<string> getPostFixTokens();
	vector<string> getInFixTokens();
	void setInFixTokens(vector<string> inFix);
	void printPostFix();
	void printInFix();
	void createPostFix();
	PostFixTokens(const PostFixTokens &other);
	PostFixTokens& operator=(const PostFixTokens &other);

private:
	vector<string> inFixTokens;
	vector<string> postFixTokens;
	vector<string> Stack;
	bool checkIfValid(vector<string> *inFix);
	bool parenthesesMatch(vector<string> *inFix);
	bool isOperator(string s); //Returns false for parentheses
	bool isParenthesis(string s);
	short getPrecedence(string s); // Returns the precedence of an operator (including a parenthesis)
	//If the string is not an operator returns -1
	//Parenthesis is given the lowest precedence

	void processOperator(string oper, vector<string> *Stack, vector<string> *Expression);
};
#endif /* PostFixTokens_h */

