#pragma once

#include "Util.h"

class Exception
{
public:
	Exception(const string& msg) : msg(msg) {}
	~Exception() {}

	string getMessage() const { return(msg); }

private:
	string msg;

};

