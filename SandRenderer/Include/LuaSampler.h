#ifndef LUA_SAMPLER_H
#define LUA_SAMPLER_H

struct lua_State;

namespace Sand
{
	class SamplerStateConfig;

	struct LuaSampler
	{
		char Filter[64];
		char AddressU[64];
		char AddressV[64];
		char AddressW[64];
		float MipLODBias;
		float MaxAnisotropy;
		char ComparisonFunc[64];
		float BorderColor[4];
		float MinLOD;
		float MaxLOD;
	};

	void ParseLuaSamplerTable( lua_State* L , LuaSampler* sampler );

	void UpdateSamplerStateConfig( SamplerStateConfig& config , LuaSampler* sampler );
};

#endif