#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include "ScriptManager.h"

namespace Sand
{
	class Console
	{
	public:
		Console();
		~Console();

		void ProcessKey( unsigned int code );

		lua_State* GetState();

	public:
		std::string line;
		std::vector<std::string> history;

	private:
		void Execute();
		void ReportErrors();

		lua_State* L;
	};
}
#endif