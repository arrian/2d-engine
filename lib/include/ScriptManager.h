#pragma once

#include "Util.h"

class Channel;
class Interpreter;
class ScriptEvent;

class ScriptManager : public enable_shared_from_this<ScriptManager>
{
public:
	shared_ptr<Channel> output;
	vector<shared_ptr<Interpreter> > interpreters;
	vector<shared_ptr<ScriptEvent> > scheduled;

	ScriptManager();
	~ScriptManager();

	python::object import(string import);
	python::object execute(string code);
	python::object executeFile(string filename);

	void setAttr(string name, python::object obj);
	python::object getAttr(string name);

	shared_ptr<ScriptEvent> scheduleScript(string code, int msecsInterval);
	void cancelScript(shared_ptr<ScriptEvent> event);

	string getError();
	
	void update();

	void setOutput(shared_ptr<Channel> output);
	shared_ptr<Interpreter> createInterpreter(shared_ptr<Channel> channel);

private:
	python::object main;
	python::object global;
};
