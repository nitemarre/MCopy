#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

char* clip;
char joda[1024] = "start https://www.google.com/search?q=";
char jjjj[1024];
_Bool a = 0;

LRESULT CALLBACK lpFn(int code, WPARAM wParam, LPARAM lParam){
	if(wParam == WM_KEYUP){
		if((GetAsyncKeyState(0x78) & 0x01)){
			cop:

				keybd_event(0xA2, 0, 0, 0);
				keybd_event('C', 0, 0, 0);
				
				keybd_event(0xA2, 0, KEYEVENTF_KEYUP, 0);
				keybd_event('C', 0, KEYEVENTF_KEYUP, 0);

				Sleep(10);
				OpenClipboard(0);
				clip = GetClipboardData(CF_TEXT);
				if(clip[0] == 63){
					CloseClipboard();
					a = 1;
					PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
					goto cop;
				}
				CloseClipboard();

				for(int i = 0; i < strlen(clip); i++){
					if(clip[i] == ' ') clip[i] = '+'; 
				}
				if (a == 1) PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
				a = 0;
				strcat(jjjj, clip);
				system(jjjj);
				strcpy(jjjj, joda);

				
		}
		if((GetAsyncKeyState(0x7b) & 0x01)){
			system("taskkill /f /im tg.exe");
		}
	}
	else{
		CallNextHookEx(NULL, code, wParam, lParam);
	}
}

int main(){
	setlocale(LC_ALL, "Russian");
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	strcpy(jjjj, joda);

	SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)lpFn, GetModuleHandle(0), 0);
	NOTIFYICONDATA data;
	data.cbSize = sizeof(data);
	data.uID = 1;  
	data.hWnd = GetConsoleWindow();       
	data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	data.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	data.uCallbackMessage = 0x401;
	memcpy(data.szTip, "MCopy: F12 to exit", 20); 

	Shell_NotifyIcon(NIM_ADD, &data);
	MSG msg = {0};

	while(GetMessage(&msg, 0, 0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}