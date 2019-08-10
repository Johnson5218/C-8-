#include <Windows.h> 
#include <tchar.h> 
//��Ϣ�ص����� 
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case WM_CLOSE: 
		if (IDOK == MessageBox(hWnd, _T("��ȷ���˳���"), _T("�˳�"), MB_OKCANCEL)) 
		{ 
			DestroyWindow(hWnd); 
			return 0; 
		} 
	case WM_DESTROY: 
		PostQuitMessage(0); 
		return 0; 
	default: 
		return DefWindowProc(hWnd, message, wParam, lParam);
	} 
}