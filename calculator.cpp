#include <windows.h>
#include <cstdio>

HWND textfiled,Input1,Input2;
HWND btn_ps ,btn_mn , btn_mtp , btn_dv;
int pstn_x = 40;
double result,Num1,Num2;
char input1[20],input2[20],output[100];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: 
			CreateWindow("STATIC",
						 "Please input two numbers",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  20,20,200,20,
						  hwnd, NULL, NULL, NULL);

			Input1  = CreateWindow("EDIT",
						 "",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  30,50,180,20,
						  hwnd, NULL, NULL, NULL);
			Input2  = CreateWindow("EDIT",
						 "",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  30,80,180,20,
						  hwnd, NULL, NULL, NULL);
			
			btn_ps = CreateWindow("BUTTON",
						 "+",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  pstn_x+30,120,20,20,
						  hwnd, (HMENU)1, NULL, NULL);
			btn_mn = CreateWindow("BUTTON",
						 "-",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  pstn_x+60,120,20,20,
						  hwnd, (HMENU)2, NULL, NULL);
			btn_mtp = CreateWindow("BUTTON",
						 "*",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  pstn_x+90,120,20,20,
						  hwnd, (HMENU)3, NULL, NULL);

			btn_dv = CreateWindow("BUTTON",
						 "/",
						  WS_VISIBLE| WS_CHILD | WS_BORDER,
						  pstn_x+120,120,20,20,
						  hwnd, (HMENU)4, NULL, NULL);

			
			
			break;
		
		case WM_COMMAND: {

				int wmId = LOWORD(wParam);

				if(wmId >=1 && wmId <=4){
				GetWindowText(Input1,input1,20);
				GetWindowText(Input2,input2,20);

				Num1 = atof(input1);
				Num2 = atof(input2);

				switch(wmId){
					case 1:
						result = Num1 + Num2;
					break;

					case 2:
						result = Num1 - Num2;
					break;

					case 3:
						result = Num1 * Num2;
					break;

					case 4:
					if(Num2 == 0){
						MessageBox(hwnd, "Cannot divide by zero","Error!",MB_ICONERROR|MB_OK);
						return 0;
					}
					result = Num1 / Num2;
					break;
				}
				
				sprintf(output,"%f",result);
				MessageBox(hwnd,output,"Result",MB_OK);
			}
			break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0); 
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT+1); //สี นง.สดละกัน
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_CAPTION|WS_SYSMENU,
		650, /* x */
		250, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
