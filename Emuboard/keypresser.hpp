#ifndef KEYPRESSER_H
#define KEYPRESSER_H

#define WINVER 0x0500
#include <windows.h>

// No description
class KeyPresser
{
	// private section
	public:
		void Press(int VK, int& button, bool shift){
			// This structure will be used to create the keyboard
			// input event.
			INPUT ip;

			// Set up a generic keyboard event.
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0; // hardware scan code for key
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;
			
			// Press the Shift Key
			if(shift){
				ip.ki.wVk = VK_LSHIFT; 
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
			}
			
			// Press the Key
			ip.ki.wVk = VK;
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));

			// Shift Key Release
			if(shift){
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				ip.ki.wVk = VK_LSHIFT; 
				SendInput(1, &ip, sizeof(INPUT));
			}
						
			button = 0;			
		}	
};

#endif // KEYPRESSER_H

