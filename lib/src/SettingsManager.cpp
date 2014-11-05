#include "SettingsManager.h"

#include <boost/lexical_cast.hpp>


SettingsManager::SettingsManager()
{

}

SettingsManager::~SettingsManager()
{

}

template<typename T> T SettingsManager::getValue(std::string key)
{
	return boost::lexical_cast<T>(key);//example.. TODO: load config and get value using key from json
}

