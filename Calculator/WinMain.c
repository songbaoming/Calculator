#include "Calculator.h"

char *ch;
char token[60];
char tok_type;
int is_error;//标示错误发生，无错为0，否则非零！
TCHAR szAppName[]=TEXT("计算器");
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR szCmd,int nShow)
{
	
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wcls;


	wcls.cbSize = sizeof(wcls);
	wcls.style = CS_HREDRAW|CS_VREDRAW;
	wcls.lpfnWndProc = WndProc;
	wcls.hInstance = hInst;
	wcls.cbWndExtra = DLGWINDOWEXTRA;
	wcls.cbClsExtra = 0;
	wcls.hbrBackground = (HBRUSH)(COLOR_BTNFACE +1);
	wcls.hIcon = LoadIcon(hInst,szAppName);
	wcls.hIconSm = NULL;
	wcls.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcls.lpszClassName = szAppName;
	wcls.lpszMenuName = NULL;

	if(!RegisterClassEx(&wcls)){
		MessageBox(NULL,TEXT("注册类出错！"),TEXT("错误"),MB_ICONERROR);
		return 0;
	}

	hwnd = CreateDialog(hInst,szAppName,NULL,NULL);

	ShowWindow(hwnd,nShow);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HWND hbutton;
	double answer;
	static char *temp,exp[80];
	char chtemp[70]={"\0"}, serr[][24]={"错误:幂运算对象有误！",
										"错误:表达式有误！",
										"错误:0不能做除数！"};
	static BOOL newnum = TRUE;

	switch(message)
	{
	case WM_CREATE:
		temp = exp;
		return 0;
	case WM_CHAR:
		if((hbutton = GetDlgItem(hwnd,wParam)) && (wParam>102||wParam<97))
		{
			SendMessage(hbutton,BM_SETSTATE,1,0);
			Sleep(50);
			SendMessage(hbutton,BM_SETSTATE,0,0);
		}
		else
		{
			MessageBeep(0);
			break;
		}				//下落
	case WM_COMMAND:
		SetFocus(hwnd);

		if(isalpha(LOWORD(wParam))){//处理字母
			MessageBeep(0);
			return 0;
		}
		else if(isdigit(LOWORD(wParam)))//处理数字
		{
			if(newnum){
				temp = exp;
			}
			newnum = FALSE;
			*temp++=LOWORD(wParam);
			*temp = '\0';
		}
		else if(LOWORD(wParam)==8)//backspace
		{
			if(temp>exp)
				*(--temp) = '\0';
			newnum = FALSE;
		}
		else if(LOWORD(wParam)==13)//回车或“=”
		{
			temp = ch = exp;
			is_error = ERR_NO_ERROR;
			answer = calculate();
			if(is_error > ERR_NO_ERROR){
				strcpy_s(chtemp,sizeof(chtemp),serr[is_error - 1]);
				*temp = '\0';
			}
			else{
				sprintf_s(chtemp,sizeof(chtemp),"%.2f",answer);
				sprintf_s(exp,sizeof(exp),"%.2f",answer);
				while(*temp++);
				temp--;
			}
			SetWindowTextA(GetDlgItem(hwnd,11),chtemp);
			newnum = TRUE;
			return 0;
		}
		else if(isgraph(LOWORD(wParam))){
			*temp++=LOWORD(wParam);
			*temp = '\0';
			newnum = FALSE;
		}
		else {
			MessageBeep(0);
			return 0;
		}
		SetWindowTextA(GetDlgItem(hwnd,11),exp);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
