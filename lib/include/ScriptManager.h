#pragma once

#include "Util.h"

class Channel;
class Interpreter;

class ScriptManager : public enable_shared_from_this<ScriptManager>
{
public:
	shared_ptr<Channel> output;
	vector<shared_ptr<Interpreter> > interpreters;

	ScriptManager();
	~ScriptManager();

	string import(string import);
	string execute(string code);
	string executeFile(string filename);

	string getError();
	
	void update();

	void setOutput(shared_ptr<Channel> output);
	shared_ptr<Interpreter> createInterpreter(shared_ptr<Channel> channel);

private:

};
