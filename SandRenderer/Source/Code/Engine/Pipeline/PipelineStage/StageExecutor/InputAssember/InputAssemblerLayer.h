#ifndef INPUT_ASSEMBLER_LAYER_H
#define INPUT_ASSEMBLER_LAYER_H

namespace Sand
{
	enum EInputLayer
	{
		eNull		= 0x0		,
		ePos		= 0x1		,
		eColor		= 0x2		, 
		eNormal		= 0x4		,
		eTangent	= 0x8		,
		eBinormal	= 0x10		,
		eTex0		= 0x10		,
		eTex1		= 0x20		,
		eTex2		= 0x40		, 
		eTex3		= 0x80		, 
		eTex4		= 0x100		, 
		eTex5		= 0x200		, 
		eTex6		= 0x400		, 
		eTex7		= 0x800		, 
		eTex8		= 0x1000	, 
		eTex9		= 0x2000	, 
		eTex10		= 0x4000	, 
		eTex11		= 0x8000	, 
		eTex12		= 0x10000	, 
		eTex13		= 0x20000	, 
		eTex14		= 0x40000	, 
		eTex15		= 0x80000	,
	};
}
#endif