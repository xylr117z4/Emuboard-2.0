#define SFML_STATIC
#define _WIN32_WINNT 0x0500
#include "keypresser.hpp"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>


int main(int argc, char *argv[]) {
	sf::RenderWindow App(sf::VideoMode(256,256,32),"EmuBoard");
	const HWND HANDLE = App.getSystemHandle();
	App.setVerticalSyncEnabled(true);
	const int WINDOW_X = 265, WINDOW_Y = 290;
	const int SCREEN_X = GetSystemMetrics(SM_CXSCREEN), SCREEN_Y = GetSystemMetrics(SM_CYSCREEN);
	
	sf::Texture iController;
	iController.loadFromFile("Images/Controller.png");
	sf::Texture iOver;
	iOver.loadFromFile("Images/Over.png");
	sf::Texture iOverHalf;
	iOverHalf.loadFromFile("Images/OverHalf.png");
	
	sf::Sprite Controller(iController);
	Controller.setScale(0.5,0.5);
	Controller.setPosition(0,0);
	sf::Sprite Over(iOver);
	Over.setOrigin(31,31);
	Over.setPosition(127,127);
	Over.setColor(sf::Color(0,200,0,100));
	sf::Sprite OverHalf(iOverHalf);
	OverHalf.setOrigin(23,23);
	OverHalf.setColor(sf::Color(0,200,0,100));
	
	sf::Vector2f UP_LEFT(53,54);
	sf::Vector2f UP(127,37);
	sf::Vector2f UP_RIGHT(198,54);
	sf::Vector2f RIGHT(216,127);
	sf::Vector2f DOWN_RIGHT(203,200);
	sf::Vector2f DOWN(127,214);
	sf::Vector2f DOWN_LEFT(53,200);
	sf::Vector2f LEFT(39,127);
	
	sf::Vector2i mousePos = sf::Vector2i(0,0);
	
	sf::Clock Clock;
	sf::Time tClock = sf::seconds(0.1f);
	
	bool drawOverHalf = false;
	bool buttonPressed = false;
	bool shift = false;
	int group = 0;
	int button = 0;
	int t = 0;
	float Elapsed = 0;
	KeyPresser Presser;
	
	while(App.isOpen()){
		sf::Event Event;
		tClock = sf::seconds(Clock.restart().asSeconds());
		Elapsed = tClock.asSeconds();
		sf::IntRect gRect(0,0,30,30);
		sf::IntRect cRect(0,0,30,30);
		
		mousePos = sf::Mouse::getPosition();
		
		float Joystick0X = sf::Joystick::getAxisPosition(0, sf::Joystick::X); //First Joystick, X
		float Joystick0Y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y); //First Joystick, Y
		float Joystick0U = sf::Joystick::getAxisPosition(0, sf::Joystick::U); //Second Joystick, X
		float Joystick0R = sf::Joystick::getAxisPosition(0, sf::Joystick::R); //Second Joystick, Y
		float Joystick0Z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z); //Triggers
		int POV0 = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX); //D-pad, 0-up, 90-right, 180-down, 270-left //
        															// 45-up-right, 135-right-down, 225-down-left, 315-left-up //
        														
		
		while (App.pollEvent(Event)) {
            if (sf::Joystick::isButtonPressed(1,6) || Event.type == sf::Event::Closed)
                App.close();
                
            if(Event.type == sf::Event::JoystickButtonPressed){
	           	if(sf::Joystick::isButtonPressed(1,0)){
						button = 1;
				}
				else if(sf::Joystick::isButtonPressed(1,1)){
						button = 2;
				}
				else if(sf::Joystick::isButtonPressed(1,2)){
						button = 3;
				}
				else if(sf::Joystick::isButtonPressed(1,3)){
						button = 4;
				}
				else if(sf::Joystick::isButtonPressed(1, 4)){
						button = 5;
				}
				else if(sf::Joystick::isButtonPressed(1, 5)){
						button = 6;
				}
			}
		}		
	//Select Group
		//UP
		if(Joystick0Y <= -26 && Joystick0X <= 25 && Joystick0X >= -25){
			group = 1;
			OverHalf.setPosition(UP);
			drawOverHalf = true;
		}
		//UP_RIGHT
		else if(Joystick0Y <= -26 && Joystick0X >= 26){
			group = 2;
			OverHalf.setPosition(UP_RIGHT);
			drawOverHalf = true;
		}
		//RIGHT
		else if(Joystick0X >= 26 && Joystick0Y <= 25 && Joystick0Y >= -25){
			group = 3;
			OverHalf.setPosition(RIGHT);
			drawOverHalf = true;
		}
		//DOWN_RIGHT
		else if(Joystick0Y >= 26 && Joystick0X >= 26){
			group = 4;
			OverHalf.setPosition(DOWN_RIGHT);
			drawOverHalf = true;
		}
		//DOWN
		else if(Joystick0Y >= 26 && Joystick0X <= 25 && Joystick0X >= -25){
			group = 5;
			OverHalf.setPosition(DOWN);
			drawOverHalf = true;
		}
		//DOWN_LEFT
		else if(Joystick0Y >= 26 && Joystick0X <= -26){
			group = 6;
			OverHalf.setPosition(DOWN_LEFT);
			drawOverHalf = true;
		}
		//LEFT
		else if(Joystick0X <= -26 && Joystick0Y <= 25 && Joystick0Y >= -25){
			group = 7;
			OverHalf.setPosition(LEFT);
			drawOverHalf = true;
		}
		//UP_LEFT
		else if(Joystick0Y <= -26 && Joystick0X <= -26){
			group = 8;
			OverHalf.setPosition(UP_LEFT);
			drawOverHalf = true;
		}
		else{
			group = 0;
			drawOverHalf = false;
		}
		
	//Move Mouse
		/*float angle = atan2(Joystick0R, Joystick0U);
		if(Joystick0U < -2 || Joystick0U > 2 || Joystick0R < -2 || Joystick0R > 2){
			sf::Vector2i newMousePos = sf::Vector2i(sin(angle) * 100*Elapsed +mousePos.x, cos(angle)* 100*Elapsed +mousePos.y);
			sf::Mouse::setPosition(newMousePos);
		}*/
		
		if(Joystick0Z <= -10){
			shift = true;
		}
		else if(Joystick0Z >= 10){
			App.setVisible(false);	
		}
		else{
			shift = false;
			App.setVisible(true);
		}
		
		if(group > 0){
			switch(group){
				//UP
				case 1:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('A', button, shift);
								break;
							case 2:
								Presser.Press('B', button, shift);
								break;
							case 3:
								Presser.Press('C', button, shift);
								break;
							case 4:
								Presser.Press('D', button, shift);
								break;
						}
					}
					break;
				//UP_RIGHT
				case 2:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('E', button, shift);
								break;
							case 2:
								Presser.Press('F', button, shift);
								break;
							case 3:
								Presser.Press('G', button, shift);
								break;
							case 4:
								Presser.Press('H', button, shift);
								break;
						}
					}
					break;
				//RIGHT
				case 3:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('I', button, shift);
								break;
							case 2:
								Presser.Press('J', button, shift);
								break;
							case 3:
								Presser.Press('K', button, shift);
								break;
							case 4:
								Presser.Press('L', button, shift);
								break;
						}
					}
					break;
				//DOWN_RIGHT
				case 4:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('M', button, shift);
								break;
							case 2:
								Presser.Press('N', button, shift);
								break;
							case 3:
								Presser.Press('O', button, shift);
								break;
							case 4:
								Presser.Press('P', button, shift);
								break;
						}
					}
					break;
				//DOWN
				case 5:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('Q', button, shift);
								break;
							case 2:
								Presser.Press('R', button, shift);
								break;
							case 3:
								Presser.Press('S', button, shift);
								break;
							case 4:
								Presser.Press('T', button, shift);
								break;
						}
					}
					break;
				//DOWN_LEFT
				case 6:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('U', button, shift);
								break;
							case 2:
								Presser.Press('V', button, shift);
								break;
							case 3:
								Presser.Press('W', button, shift);
								break;
							case 4:
								Presser.Press('X', button, shift);
								break;
						}
					}
					break;
				//LEFT
				case 7:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press('Y', button, shift);
								break;
							case 2:
								Presser.Press('Z', button, shift);
								break;
							case 3:
								Presser.Press(VK_OEM_7, button, shift);
								break;
							case 4:
								break;
						}
					}
					break;
				//UP_LEFT
				case 8:
					if(button > 0){
						switch(button){
							case 1:
								Presser.Press(VK_DECIMAL, button, shift);
								break;
							case 2:
								Presser.Press('1', button, true);
								break;
							case 3:
								Presser.Press(VK_OEM_2, button, true);
								break;
							case 4:
								Presser.Press('2', button, true);
								break;
						}
					}
					break;
			}
		}
		//NONE
		else{
			if(button > 0){
				switch(button){
					case 1:
						Presser.Press(VK_RETURN, button, shift);
						break;
					case 2:
						break;
					case 3:
						Presser.Press(VK_BACK, button, shift);
						break;
					case 4:
						Presser.Press(VK_SPACE, button, shift);
						break;
					case 5:
						Presser.Press(VK_LEFT, button, shift);
						break;
					case 6:
						Presser.Press(VK_RIGHT, button, shift);
						break;
				}
			}
		}
		
		//SetWindowPos(HANDLE, HWND_TOPMOST, SCREEN_X-WINDOW_X,SCREEN_Y-WINDOW_Y,WINDOW_X,WINDOW_Y,SWP_NOACTIVATE);
		App.clear();
		App.draw(Controller);
		if(drawOverHalf){
			App.draw(OverHalf);
		}else App.draw(Over);
		App.display();
	}
}
