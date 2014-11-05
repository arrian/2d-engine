#pragma once

class SettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

	template<typename T> T getValue(std::string key);
	template<typename T> void setValue(std::string key, T value);

private:

};
