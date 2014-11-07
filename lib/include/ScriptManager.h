#pragma once

#include "Util.h"

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
	string executeFile(string filename);

	string getError();
	
	void update();

	shared_ptr<Interpreter> createInterpreter(shared_ptr<Channel> channel);

private:

};
