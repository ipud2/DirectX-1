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

// DirectX ͷ�ļ�
#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

#define SAFE_RELEASE(x) {if(x){(x)->Release(); (x) = NULL;}}
#define SAFE_DELETE(x) {if(x){delete (x); (x) = NULL;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; (x) = NULL;}}

#define SAND_PI 3.14159265f;

#endif // PCH_h