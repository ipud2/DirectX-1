#pragma once

struct ID3D11Device;
struct  ID3D11DeviceContext;

bool ImInit( void* hwnd , ID3D11Device* device , ID3D11DeviceContext* context );

void ImShutdown();

void ImNewFrame();

void ImInvalidateDeviceObjects();

bool ImCreateDeviceObjects();