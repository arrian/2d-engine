#pragma once

#include <string>
#include <vector>

using namespace std;

class ChannelStandard : public Channel
{
	virtual string in()
	{
		string input;
		getline(cin, input);
		return input;
	}

	virtual void out(string value)
	{
		cout << value << endl;
	}
};

class Channel
{
	virtual ~Channel() {}

	virtual string in() = 0;// get a string of input
	virtual void out(string value) = 0;// handle a string of output
};

class Interpreter
{
	shared_ptr<Channel> channel;
	shared_ptr<ScriptManager> scriptManager;

	Interpreter(shared_ptr<ScriptManager> scriptManager, shared_ptr<Channel> channel)
		: scriptManager(scriptManager),
		  channel(channel)
	{
		if(!scriptManager) throw Exception("Interpreter requires a ScriptManager.");
		if(!channel) throw Exception("Interpreter requires a Channel.");
	}

	void prompt()
	{
		channel->out(">>> ");
	}

	void evaluate()
	{
		channel->out(scriptManager->execute(channel->in()));
	}
};

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
