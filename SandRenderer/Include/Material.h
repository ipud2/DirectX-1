#ifndef MATERIAL_H
#define MATERIAL_H

#include "MaterialHelper.h"
#include "ParameterContainer.h"

struct lua_State;

namespace Sand
{
	class Renderer;

	class Material
	{
	public:
		Material( const char* name );

		~Material();

		void Update( IParameterManager* pParameterManager );

	private:
		void InitParams();

	private:
		lua_State* L;

		std::map<std::string , MatItem> ParamList;

		ParameterContainer Parameters;

		bool bInit;
	};
}
#endif