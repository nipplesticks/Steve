#ifndef PCH_H
#define PCH_H
#define NOMINMAX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <iostream>
#include <Common/AssertX.h>
#include <Common/DMath.h>
#include <Common/StringManip.h>
#include <Common/Typedef.h>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx12.h"
#include "Imgui/imgui_impl_win32.h"

#include "Render/Device.h"
#include "Render/Rootsignature.h"
#include "Render/d3dx12.h"
#include "Util/AlignMe.h"
#include "Util/HRAssert.h"
#include "Util/SafeRelease.h"
#include "Window/WindowEvent.h"
#include "Window/Window.h"
#include "Render/Pipelines/GraphicalPipelineState.h"

#endif //PCH_H
