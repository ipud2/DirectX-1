#include <Engine/PCH.h>
#include "Engine/Math/Vector4f.h"
#include "Engine/Math/Vector2f.h"

using namespace Sand;

Vector3f Vector4f::xyz() const
{
	return Vector3f( x , y , z );
}

Vector2f Vector4f::xy() const
{
	return Vector2f( x , y );
}