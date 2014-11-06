#pragma once

#include <string>
#include <vector>

using namespace std;

class Channel;
class Interpreter;

class ScriptManager
{
public:
	shared_ptr<Channel> output;
	vector<shared_ptr<Interpreter> > interpreters;

	ScriptManager();
	~ScriptManager();

	void setOutput(shared_ptr<Channel> output);

	string import(string import);
	string execute(string code);
	string executeFile(string code);

	string getError();
	
	void update();

	shared_ptr<Interpreter> createInterpreter(shared_ptr<Channel> channel);

private:

};
