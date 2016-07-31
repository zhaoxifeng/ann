#pragma once
#include <map>
using namespace std;
class StreamSupportBase;

template<typename T> StreamSupportBase * createT() { return new T; }

class NameBasedFactory 
{
	typedef std::map<std::string, StreamSupportBase*(*)()> map_type;
public:
	static StreamSupportBase * createInstance(std::string const& s)
	{
		map_type::iterator it = map.find(s);
		if (it == map.end())
			return 0;
		return it->second();
	}

protected:
	static map_type map;
};

template<typename T>
class DerivedRegister : NameBasedFactory
{
public:
	DerivedRegister(std::string const& s) 
	{
		map.insert(std::make_pair(s, &createT<T>));
	}

};
