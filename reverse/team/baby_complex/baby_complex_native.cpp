#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

__forceinline const char* GetHintText()
{
	static char HintBuffer[1919810];

	// "RC4 secret in PE header..."
	unsigned char secret[] = 
	{
		0x20, 0x30, 0x40, 0x55, 0x05, 
		0x12, 0x1b, 0x0b, 0x1f, 0x0f, 
		0x5c, 0x14, 0x10, 0x5f, 0xd0, 
		0xc4, 0xa2, 0xeb, 0xe1, 0xe4, 
		0xe2, 0xe2, 0xfa, 0xa7, 0xa4, 
		0xa5
	};

	for (int i = 0; i < 26; ++i)
		HintBuffer[i] = secret[i] ^ (i + 114);
	
	return HintBuffer;
}

class Game
{
private:
	enum
	{
		STAT_NONE,
		STAT_PLAYER,
		STAT_COMPUTER
	};

	enum
	{
		NOW_NONE,
		NOW_PLAYER,
		NOW_COMPUTER
	};
public:

	explicit Game() noexcept
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		Reset();
		IsActive = true;
		WinCount = 0;
	}

	void Paint(HDC hdc, PAINTSTRUCT ps)
	{
		MoveToEx(hdc, 0, 0, nullptr); LineTo(hdc, 0, 300);
		MoveToEx(hdc, 100, 0, nullptr); LineTo(hdc, 100, 300);
		MoveToEx(hdc, 200, 0, nullptr); LineTo(hdc, 200, 300);
		MoveToEx(hdc, 300, 0, nullptr); LineTo(hdc, 300, 300);

		MoveToEx(hdc, 0, 0, nullptr); LineTo(hdc, 300, 0);
		MoveToEx(hdc, 0, 100, nullptr); LineTo(hdc, 300, 100);
		MoveToEx(hdc, 0, 200, nullptr); LineTo(hdc, 300, 200);
		MoveToEx(hdc, 0, 300, nullptr); LineTo(hdc, 300, 300);

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				int centx = x * 100 + 50;
				int centy = y * 100 + 50;
				if (Plane[x][y] == STAT_PLAYER)
				{
					MoveToEx(hdc, centx - 25, centy, nullptr); LineTo(hdc, centx + 25, centy);
					MoveToEx(hdc, centx, centy - 25, nullptr); LineTo(hdc, centx, centy + 25);
				}
				else if (Plane[x][y] == STAT_COMPUTER)
				{
					MoveToEx(hdc, centx - 25, centy - 25, nullptr); LineTo(hdc, centx + 25, centy + 25);
					MoveToEx(hdc, centx - 25, centy + 25, nullptr); LineTo(hdc, centx + 25, centy - 25);
				}
			}
		}

		char buffer[0x200];
		sprintf(buffer, "WinCount = %d", WinCount);
		TextOut(hdc, 100, 315, buffer, strlen(buffer));
	}

	void ProcessClick(int x, int y)
	{
		if (!IsActive)
			return;

		if (x < 0 || x > 2 || y < 0 || y > 2)
			return;

		if (!Move(x, y, NOW_PLAYER))
			return;

		if (Is_Game_Done())
		{
			if (Get_Winner() == STAT_PLAYER)
				++WinCount;
			Reset();
			return;
		}

		AI();

		if (Is_Game_Done())
		{
			if (Get_Winner() == STAT_PLAYER)
				++WinCount;
			Reset();
		}
	}

	void AI()
	{
		while (true)
		{
			int x = rand() % 3;
			int y = rand() % 3;
			if (Move(x, y, NOW_COMPUTER))
				break;
		}
	}

	int GetWinCount() const
	{
		return WinCount;
	}

	void PrintConsole()
	{
		for (int x = 0; x < 3; ++x)
			printf("%d%d%d\n", Plane[x][0], Plane[x][1], Plane[x][2]);
	}

	bool NeedsRedraw() const
	{
		return NeedRedraw;
	}

	void Deactivate()
	{
		IsActive = false;
	}

	bool IsActivated()
	{
		return IsActive;	
	}

private:
	bool Move(int x, int y, int side)
	{
		if (Plane[x][y] != STAT_NONE)
			return false;
		Plane[x][y] = side;
		NeedRedraw = true;
		return true;
	}

	bool IsFull() const
	{
		int cnt = 0;
		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
				if (Plane[x][y] != STAT_NONE)
					++cnt;
		}
		return cnt == 9;
	}

	int Get_Winner()
	{
		for (int x = 0; x < 3; ++x)
		{
			if (Plane[x][0] == Plane[x][1] && Plane[x][0] == Plane[x][2])
				return Plane[x][0];
		}

		for (int y = 0; y < 3; ++y)
		{
			if (Plane[0][y] == Plane[1][y] && Plane[0][y] == Plane[2][y])
				return Plane[0][y];
		}

		if (Plane[0][0] == Plane[1][1] && Plane[0][0] == Plane[2][2])
			return Plane[1][1];

		if (Plane[2][0] == Plane[1][1] && Plane[2][0] == Plane[0][2])
			return Plane[1][1];

		return STAT_NONE;
	}

	bool Is_Game_Done()
	{
		return IsFull() || Get_Winner() != STAT_NONE;
	}

	void Reset()
	{
		memset(Plane, STAT_NONE, sizeof(Plane));
		AI();
		NeedRedraw = true;
	}

	int Plane[3][3];
	int WinCount;
	bool IsActive;
	bool NeedRedraw;
};

Game game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		case WM_DESTROY:
        {
			PostQuitMessage(0);
        	return 0;
		}
		case WM_LBUTTONUP:
		{
			INT xPos = LOWORD(lParam); 
			INT yPos = HIWORD(lParam); 
			game.ProcessClick(xPos / 100, yPos / 100);
			if (game.NeedsRedraw())
				RedrawWindow(hWnd, nullptr, NULL, RDW_UPDATENOW | RDW_INVALIDATE);

			if (game.GetWinCount() >= 1000) // How many times need I win it?
			{
				game.Deactivate();
				RedrawWindow(hWnd, nullptr, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			}
			return 0;
		}
		case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOWFRAME);
			game.Paint(hdc, ps);
			if (!game.IsActivated())
			{
				auto hint = GetHintText();
				TextOutA(hdc, 100, 150, hint, strlen(hint));
				Sleep(1000);
				exit(0);
			}
            EndPaint(hWnd, &ps);
			return 0;
        }
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

BOOL PASCAL WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
	WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("baby_complex_native");

    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(
        wc.lpszClassName,
        TEXT("baby_complex_native"),
        WS_OVERLAPPEDWINDOW,
        100, 100, 300, 335,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );
	SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	BOOL bRet;
	while( (bRet = GetMessage(&msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    } 

	return FALSE;
}

