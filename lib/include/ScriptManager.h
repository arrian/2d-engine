#pragma once

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void import(std::string import);
	void run(std::string command);
	void checkError();

	std::string getError();
	
	void update();

private:

};
