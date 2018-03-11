#include "stdafx.h"
#include "XzMessage.h"
#include "XzDirector.h"
#include "XzInput.h"

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

#define MAX_LOADSTRING 100
// 全局变量:
//HINSTANCE			hInst;										// 当前实例
//HWND				hWnd;										// 窗口句柄
//WNDCLASSEX			wcex;										// 窗口结构体
//LPDIRECT3D9			g_pD3D = NULL;								// D3D指针
//LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;						// 设备指针
//INT					g_iWindowWidth = 960;						// 宽	
//INT					g_iWindowHeight = 540;						// 高
//FLOAT				g_time = 0.0f;								// 计时
//FLOAT				g_FrameTime = (1.0f / 30.f);				// 帧率

XzDirector*			xDirector = NULL;
XzInput*			xInput = NULL;
XzProfile*			xProfile = NULL;
// 此代码模块中包含的函数的前向声明:

//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
HRESULT InitD3D(HWND hWnd);
VOID Init();
VOID Update();
VOID Render();
VOID Cleanup();

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
//#if defined(DEBUG) | defined(_DEBUG)
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//#endif
	//_CrtSetBreakAlloc(414);
	xProfile = XzProfile::GetSingleton();
	if (!xProfile->LoadProfile("SYSinfo.xml"))
	{
		return 0;
	}
	XzTime::GetSingleton();
	xInput = XzInput::GetSingleton();
	xDirector = XzDirector::GetSingleton();

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    if (FAILED(InitD3D(xProfile->hWnd)))
    {
        return FALSE;
    }

    ShowWindow(xProfile->hWnd, nCmdShow);
    UpdateWindow(xProfile->hWnd);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));


    xDirector->Init();

    while (xDirector->GetGameSurvival())
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (xProfile->m_pd3dDevice)
        {
			xDirector->MainLoop();
        }
    }
	xDirector->EndGame();
	Cleanup();
	UnregisterClass(L"Engine", xProfile->wcex.hInstance);
	return 0;
}

// 注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    xProfile->wcex.cbSize = sizeof(WNDCLASSEX);

    xProfile->wcex.style = CS_CLASSDC;
    xProfile->wcex.lpfnWndProc = MsgProc;
    xProfile->wcex.cbClsExtra = 0;
    xProfile->wcex.cbWndExtra = 0;
    xProfile->wcex.hInstance = hInstance;
    xProfile->wcex.hIcon = NULL;
    xProfile->wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    xProfile->wcex.hbrBackground = NULL;
    xProfile->wcex.lpszMenuName = NULL;
    xProfile->wcex.lpszClassName = L"Engine";
    xProfile->wcex.hIconSm = NULL;

    return RegisterClassEx(&xProfile->wcex);
}

// 保存实例句柄并创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    xProfile->hInst = hInstance; // 将实例句柄存储在全局变量中

    xProfile->hWnd = CreateWindow(L"Engine", L"new world", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, xProfile->m_iWidth, xProfile->m_iHeight, NULL, NULL, hInstance, NULL);

    if (!xProfile->hWnd)
    {
        return FALSE;
    }
    return TRUE;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_NULL:
        break;
	case WM_KEYDOWN:
		xInput->ProcMsg(msg,wParam,lParam);
		XzMessage::GetSingleton()->MsgProc(hWnd, msg, wParam, lParam);
		break;
	case WM_KEYUP:
		xInput->ProcMsg(msg,wParam,lParam);
		XzMessage::GetSingleton()->MsgProc(hWnd, msg, wParam, lParam);
		break;
    case WM_DESTROY:
		XzDirector::GetSingleton()->SetGameOver();
        //PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        ValidateRect(hWnd, NULL);
        return 0;
	default:
		xInput->ProcMsg(msg,wParam,lParam);
		XzMessage::GetSingleton()->MsgProc(hWnd, msg, wParam, lParam);
		break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
//初始化D3D
HRESULT InitD3D(HWND hWnd)
{
    if (NULL == (xProfile->m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        return E_FAIL;
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if (FAILED(xProfile->m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, xProfile->hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &xProfile->m_pd3dDevice)))
    {
        return E_FAIL;
    }

    xProfile->m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    xProfile->m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    xProfile->m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    return S_OK;
}

VOID Cleanup()
{
    if (xProfile->m_pd3dDevice)
    {
        xProfile->m_pd3dDevice->Release();
        xProfile->m_pd3dDevice = NULL;
    }
    if (xProfile->m_pD3D)
    {
        xProfile->m_pD3D->Release();
        xProfile->m_pD3D = NULL;
    }
}
