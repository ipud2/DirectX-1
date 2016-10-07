// Ԥ����ͷ�ļ�
#ifndef PCH_h
#define PCH_h

#ifndef STRICT
#define STRICT
#endif

// ��׼c++��
#include <fstream>
#include <string.h>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <vector>
#include <exception>

// ��׼c���ļ�
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>
#include <fcntl.h>
#include <io.h>

// DirectX ͷ�ļ�
#include <d3d11.h>
#include <d3dCompiler.h>

#include <wrl.h>

#define SAFE_RELEASE(x) {if(x){(x)->Release(); (x) = NULL;}}
#define SAFE_DELETE(x) {if(x){delete (x); (x) = NULL;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; (x) = NULL;}}

#define SAND_PI 3.14159265f

#define ConvertToRadius(fDegree)	(fDegree) * (SAND_PI / 180.0f)


#define GET_X_LPARAM(lp)	((int)(short)((WORD)(((DWORD_PTR)(lp)) & 0xffff)))
#define GET_Y_LPARAM(lp)	((int)(short)((WORD)((((DWORD_PTR)(lp)) >> 16) & 0xffff)))

#endif // PCH_h