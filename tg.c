#include <stdio.h>
#include <string.h>
#include <windows.h>

char* clip;
char joda[1024] = "start https://www.google.com/search?q=";
char jjjj[1024];

LRESULT CALLBACK lpFn(int code, WPARAM wParam, LPARAM lParam){
	if(wParam == WM_KEYUP){
		if((GetAsyncKeyState(0x78) & 0x01)){
				keybd_event(0xA2, 0, 0, 0);
				keybd_event('C', 0, 0, 0);
				
				keybd_event(0xA2, 0, KEYEVENTF_KEYUP, 0);
				keybd_event('C', 0, KEYEVENTF_KEYUP, 0);

				Sleep(10);
				OpenClipboard(0);
				clip = GetClipboardData(CF_TEXT);
				CloseClipboard();

				for(int i = 0; i < strlen(clip); i++){
					if(clip[i] == ' ') clip[i] = '+'; 
				}

				strcat(jjjj, clip);
				system(jjjj);
				strcpy(jjjj, joda);

				
		}
	}
	else{
		CallNextHookEx(NULL, code, wParam, lParam);
	}
}

int main(){
	strcpy(jjjj, joda);

	SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)lpFn, GetModuleHandle(0), 0);
	MSG msg = {0};

	while(GetMessage(&msg, 0, 0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}