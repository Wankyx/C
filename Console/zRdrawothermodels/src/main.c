#include <windows.h>

int APIENTRY WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance, LPSTR lignesDeCommande, int modeDAffichage)
{
	HWND handleGame = FindWindow(NULL, TEXT("Counter-Strike source"));
	DWORD processId = 0;
	HANDLE processHandle;


	if(handleGame == NULL)
	{
		MessageBox(NULL, "Can't find the window handle .\nCounter-Strike source is not Open !", "Warning", MB_OK);

		while( (handleGame = FindWindow(NULL, TEXT("Counter-Strike source"))) == NULL);
 	}
	
 	MessageBox(NULL, "Handle is find ! .\nCounter-Strike source is Open !", "Warning", MB_OK);
 	GetWindowThreadProcessId(handleGame, &processId);


 	processHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);

 	if(processHandle == NULL)
 	{
 		MessageBox(NULL, "Can't get process handle . PROCESS_ALL_ACCESS failure\nConnot open process", "Error", MB_OK + MB_ICONERROR);
 		return 1;
 	}

 	DWORD data[2] = {0x1, 0x2};
 	BOOL r_drawothermodels_status = 0;

 	while(!GetAsyncKeyState(VK_ESCAPE))
 	{
 		if(GetAsyncKeyState(0x54))
 		{
 			if(r_drawothermodels_status == 0)
 			{
				WriteProcessMemory(processHandle, (LPVOID)0x55DFF29C0, &data[1],sizeof(DWORD), NULL);
 				r_drawothermodels_status = 1;
 			}
 			else 
 			{
 				WriteProcessMemory(processHandle, (LPVOID)0x55DFF29C0, &data[0],sizeof(DWORD), NULL);

 				r_drawothermodels_status = 0;
 			}
 			Sleep(70);
 		}

  	}
  	WriteProcessMemory(processHandle, (LPVOID)0x55DFF29C0, &data[0],sizeof(DWORD), NULL);

 	CloseHandle(processHandle);
   return 0;
}