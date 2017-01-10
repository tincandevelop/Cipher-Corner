#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <iostream>

using namespace std;

int main(){

  keybd_event( VK_F24,0x45,KEYEVENTF_EXTENDEDKEY | 0,0 );
  Sleep(10);
  keybd_event( VK_F24,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

  return 0;
}
