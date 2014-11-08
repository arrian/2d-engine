#pragma once

#include "Util.h"

/**
 * Executes a script event at a specific interval.
 */
class ScriptEvent : public EventHandler
{
public:
	ScriptManager* scriptManager;
	Timer* timer;
	string code;

	ScriptEvent(ScriptManager* scriptManager, string code, int msecsInterval)
		: scriptManager(scriptManager),
		  timer(new Timer(true, msecsInterval)),
		  code(code)
	{
		timer->addEventListener(this, Timer::EVENT_TRIGGER);
	}

	~ScriptEvent()
	{
		delete timer;
	}

	void handleEvent(Event *e)
	{
		if(e->getDispatcher() == timer && e->getEventCode() == Timer::EVENT_TRIGGER)
		{
			scriptManager->execute(code);
		}
		else throw Exception("ScriptEvent attempted to handle an unkown event.");
	}

};
