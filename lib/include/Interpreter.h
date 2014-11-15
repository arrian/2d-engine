#pragma once

#include "Util.h"

#include "ScriptManager.h"
#include "Channel.h"

class Interpreter
{
public:
	shared_ptr<Channel> channel;
	shared_ptr<ScriptManager> scriptManager;

	Interpreter(shared_ptr<ScriptManager> scriptManager, shared_ptr<Channel> channel)
		: channel(channel),
		  scriptManager(scriptManager)
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
		//channel->out(scriptManager->execute(channel->in()));
	}
};
