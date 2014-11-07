#pragma once

#include "Util.h"

class Channel
{
public:
	virtual ~Channel() {}

	virtual string in() = 0;// get a string of input
	virtual void out(string value) = 0;// handle a string of output
};

class ChannelStandard : public Channel
{
public:

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
