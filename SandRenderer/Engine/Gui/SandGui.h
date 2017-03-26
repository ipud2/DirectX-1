#ifndef SAND_GUI_H
#define SAND_GUI_H

#include "ImGui/inc/imgui.h"

typedef void ( *SandGui )( ImGuiIO& io , void* ud );

void SetupImStyle( bool bStyleDark , float alpha );

std::string OpenFile( LPCSTR szFilter );

#endif