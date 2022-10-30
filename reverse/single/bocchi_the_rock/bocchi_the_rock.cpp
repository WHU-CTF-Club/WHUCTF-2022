// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#define UNICODE

#define STB_IMAGE_IMPLEMENTATION
#include "crc.h"
#include "stb_image.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <cstring>

#include <iostream>

#pragma comment(lib, "d3d11.lib")

static char b64answer[] = "Vm0wd2QyUXlVWGxXYTFwT1ZsZG9WRll3WkRSV1ZsbDNXa1JTVjFadGVGWlZiVFZyWVd4S2MxZHVjRmhoTWsweFZqQmFZV1JIVmtWUmJIQk9UVEJLU1ZacVNqUlpWMDE1Vkd0c2FGSnNjRTlaYlhOM1pVWmtWMWR0ZEZSTlZUVkpWbTEwYTJGR1NuVlJiR2hYWWxob1dGUnJXbHBsUm1SelYyMTRVMDFFVmpaV01uUnZVekpHVjFOdVZsSmlWR3hXVm1wT2IxTkdVbFZTYkhCc1VtMVNNRlZ0ZUZOaFZscHpZMFZzVjAxdVVuWlZha1pXWlZaT2NscEdVbWxTTW1oWlYxWmtNRmxXVWtkVmJsSnNVak5TY1ZsclpGTmxiR1J5V2toa1ZXSkdjRlpXYlhoelZqSktWVkZZYUZkV1JWcFlWV3BHYTFkV2NFZGhSMnhUVFZWd1dGWnRNVFJaVm14V1RVaG9hbEpzY0ZsWmJHaFRWMVpXY1ZGVVJsTk5XRUpIVm14U1YxWnJNVVZTYkdSYVlXczFjbFpxU2tabFZsSlpZVVprYUdFeGNHOVdiWEJIWVRKT2MxZHVUbFJpUjFKVVZGUkJkMDFSUFQwPQ==";

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

struct MyImageData
{
    ImVec2 Size;
    ID3D11ShaderResourceView* Data;
};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ID3D11ShaderResourceView* LoadTextureFromFile(DWORD texID, int& out_width, int& out_height);
MyImageData LoadTextureFromFile(DWORD texID);
void ReleaseTexture(MyImageData& d);
std::string b64encode(const std::string src);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(4)), NULL, NULL, NULL, TEXT("Bocchi the Rock!"), NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, TEXT("Bocchi the Rock!"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    auto Image1 = LoadTextureFromFile(1);
    auto Image2 = LoadTextureFromFile(2);
    auto Image3 = LoadTextureFromFile(3);

    static ImVec4 colors[6] = 
    {
        { 0.384314, 0.435294, 0.388235, 0.388235 },
        { 0.407843, 0.411765, 0.372549, 0.388235 },
        { 0.407843, 0.380392, 0.431373, 0.372549 },
        { 0.411765, 0.450980, 0.372549, 0.450980 },
        { 0.435294, 0.372549, 0.419608, 0.380392 },
        { 0.466667, 0.380392, 0.411765, 0.411765 }
    };

    // Our state
    ImVec4 clear_color = colors[0];
    char flag[0x400] = { 0 };
    bool step1 = false;
    bool step2 = false;

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Jumping Girl(s)");
            ImGui::Image((void*)Image1.Data, {650.f, 200.f});
            ImGui::InputText("<- Please input here", flag, sizeof(flag)); ImGui::SameLine();
            if (ImGui::Button("Im Sure!"))
            {
                clear_color = colors[1];
                if (strlen(flag) == 32 && crc32(flag, strlen(flag)) == 0x926e43a8) // "mayctf{bocchi_chan_is_so_kawaii}"
                {
                    step1 = true;
                    clear_color = colors[2];
                }
            }
            ImGui::End();
        }

        if (step1)
        {
            ImGui::Begin("A good night......");
            ImGui::Image((void*)Image2.Data, {800.0f, 500.0f});
            // The flag is hidden in the colors
            if (ImGui::Button(flag))
            {
                clear_color = colors[3];
                std::string b64str = flag;
                b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str);
                b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str); b64str = b64encode(b64str);
                if (b64str == b64answer)
                {
                    step2 = true;
                    clear_color = colors[4];
                }
            }
            ImGui::End();
        }

        if (step2)
        {
            ImGui::Begin("Congratulations?");
            ImGui::Image((void*)Image3.Data, {600.0f, 375.0f});
            ImGui::Text("The flag is just what you have input in the first window!");
            if (ImGui::Button("Exit program"))
            {
                clear_color = colors[5];
                done = true;
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    std::cout << "Some secret is hidden in the color changes..." << std::endl;

    ReleaseTexture(Image1);
    ReleaseTexture(Image2);
    ReleaseTexture(Image3);

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

ID3D11ShaderResourceView* LoadTextureFromFile(DWORD texID, int& out_width, int& out_height)
{
    HRSRC hResInfo = FindResourceA(NULL, MAKEINTRESOURCEA(texID), MAKEINTRESOURCEA(810));
	if (NULL == hResInfo)
		return nullptr;
	DWORD dwSize = SizeofResource(NULL, hResInfo);
	if (NULL == dwSize)
		return nullptr;
	HGLOBAL hResData = LoadResource(NULL, hResInfo);
	if (NULL == hResData)
		return nullptr;
	LPVOID lpData = LockResource(hResData);
	if (nullptr == lpData)
		return nullptr;
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const stbi_uc*)lpData, dwSize, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
        return nullptr;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = nullptr;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    if (pTexture == nullptr)
        return nullptr;

    // Create texture view
    ID3D11ShaderResourceView* ret;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &ret);
    pTexture->Release();

    out_width = image_width;
    out_height = image_height;
    stbi_image_free(image_data);

    return ret;
}

MyImageData LoadTextureFromFile(DWORD texID)
{
    MyImageData ret;
    int x;
    int y;
    ret.Data = LoadTextureFromFile(texID, x, y);
    ret.Size.x = x;
    ret.Size.y = y;
    return ret;
}

void ReleaseTexture(MyImageData& d)
{
    if (d.Data)
        d.Data->Release();
}

std::string b64encode(const std::string src)
{
	constexpr auto _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	constexpr auto _pad = '=';
	constexpr auto PacketChars = 4;
	union PacketType
	{
		struct
		{
			unsigned char C3;
			unsigned char C2;
			unsigned char C1;
			unsigned char pad;
		} Char;
		struct
		{
			unsigned O4 : 6;
			unsigned O3 : 6;
			unsigned O2 : 6;
			unsigned O1 : 6;
			unsigned pad : 8;
		} SubCode;
		unsigned int Raw;
	} packet;

	std::string dest;

	size_t slen = src.length();

	auto sptr = (unsigned char const*)src.c_str();
	while (slen > 0)
	{
		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen)
		{
			packet.Char.C2 = *sptr++;
			slen--;
		}
		else
			pad++;
		if (slen)
		{
			packet.Char.C3 = *sptr++;
			slen--;
		}
		else
			pad++;

		dest += _encoder[packet.SubCode.O1];
		dest += _encoder[packet.SubCode.O2];
		if (pad < 2)
			dest += _encoder[packet.SubCode.O3];
		else
			dest += _pad;
		if (pad < 1)
			dest += _encoder[packet.SubCode.O4];
		else
			dest += _pad;
	}

	return dest;
}
