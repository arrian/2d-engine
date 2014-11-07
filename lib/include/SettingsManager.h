#pragma once

#include "Util.h"

class SettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

	template<typename T> T getValue(std::string key) { return lexical_cast<T>(key); }
	template<typename T> void setValue(std::string key, T value) {}

private:

};
