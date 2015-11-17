#ifndef DSTREAM_H
#define DSTREAM_H

#include <iostream>
#include <sstream>
#include <windows.h>

extern std::ostream dout;

class debug_stream : public std::ostringstream
{
public:
	template<typename T>
	friend debug_stream& operator<<(debug_stream& os, T&& s);
};

template<typename T>
debug_stream& operator<<(debug_stream& os, T&& s)
{
	(ostringstream&amp;)os << s;
	PrintToDebug(os.str());
	os.str("");
	return os;
}

class dbgview_buffer : public std::stringbuf
{
public:
	~dbgview_buffer()
	{
		sync(); // can be avoided
	}

	int sync()
	{
		OutputDebugString(str().c_str());
		str("");
		return 0;
	}
};

#endif 
