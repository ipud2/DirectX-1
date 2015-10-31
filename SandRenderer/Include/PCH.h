// 预编译头文件
#ifndef PCH_h
#define PCH_h

#ifndef STRICT
#define STRICT
#endif

// 标准c++库
#include <fstream>
#include <string.h>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <vector>
#include <exception>

// 标准c库文件
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>

// DirectX 头文件
#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

#define SAFE_RELEASE(x) {if(x){(x)->Release(); (x) = NULL;}}
#define SAFE_DELETE(x) {if(x){delete (x); (x) = NULL;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; (x) = NULL;}}

#define SAND_PI 3.14159265f;

#endif // PCH_h