#ifndef PCH_H
#define PCH_H
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx12.h"
#include "Imgui/imgui_impl_win32.h"
#include "Render/d3dx12.h"
#include "Util/AlignMe.h"
#include "Util/HRAssert.h"
#include "Util/SafeRelease.h"
#include <Common/AssertX.h>
#include <Common/DMath.h>
#include <Common/Typedef.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <iostream>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3dcompiler.lib")

#endif //PCH_H
