#ifndef KEY_TO_STRING
#define KEY_TO_STRING

//Utility functions.

inline std::string toString(sf::Keyboard::Key key) {
	std::string ans;
	switch(key) {
        case (sf::Keyboard::A		        ) : { ans = "A"; break; }
        case (sf::Keyboard::B	            ) : { ans = "B"; break; }
        case (sf::Keyboard::C	            ) : { ans = "C"; break; }
        case (sf::Keyboard::D	            ) : { ans = "D"; break; }
        case (sf::Keyboard::E	            ) : { ans = "E"; break; }
        case (sf::Keyboard::F	            ) : { ans = "F"; break; }
        case (sf::Keyboard::G	            ) : { ans = "G"; break; }
        case (sf::Keyboard::H	            ) : { ans = "H"; break; }
        case (sf::Keyboard::I	            ) : { ans = "I"; break; }
        case (sf::Keyboard::J	            ) : { ans = "J"; break; }
        case (sf::Keyboard::K	            ) : { ans = "K"; break; }
        case (sf::Keyboard::L	            ) : { ans = "L"; break; }
        case (sf::Keyboard::M	            ) : { ans = "M"; break; }
        case (sf::Keyboard::N	            ) : { ans = "N"; break; }
        case (sf::Keyboard::O	            ) : { ans = "O"; break; }
        case (sf::Keyboard::P	            ) : { ans = "P"; break; }
        case (sf::Keyboard::Q	            ) : { ans = "Q"; break; }
        case (sf::Keyboard::R	            ) : { ans = "R"; break; }
        case (sf::Keyboard::S	            ) : { ans = "S"; break; }
        case (sf::Keyboard::T	            ) : { ans = "T"; break; }
        case (sf::Keyboard::U	            ) : { ans = "U"; break; }
        case (sf::Keyboard::V	            ) : { ans = "V"; break; }
        case (sf::Keyboard::W	            ) : { ans = "W"; break; }
        case (sf::Keyboard::X	            ) : { ans = "X"; break; }
        case (sf::Keyboard::Y	            ) : { ans = "Y"; break; }
        case (sf::Keyboard::Z	            ) : { ans = "Z"; break; }
        case (sf::Keyboard::Num0	         ) : { ans = "Num0"; break; }
        case (sf::Keyboard::Num1	         ) : { ans = "Num1"; break; }
        case (sf::Keyboard::Num2	         ) : { ans = "Num2"; break; }
        case (sf::Keyboard::Num3	         ) : { ans = "Num3"; break; }
        case (sf::Keyboard::Num4	         ) : { ans = "Num4"; break; }
        case (sf::Keyboard::Num5	         ) : { ans = "Num5"; break; }
        case (sf::Keyboard::Num6	         ) : { ans = "Num6"; break; }
        case (sf::Keyboard::Num7	         ) : { ans = "Num7"; break; }
        case (sf::Keyboard::Num8	         ) : { ans = "Num8"; break; }
        case (sf::Keyboard::Num9	         ) : { ans = "Num9"; break; }
        case (sf::Keyboard::Escape      	) : { ans = "Esc"; break; }
        case (sf::Keyboard::LControl    	) : { ans = "LCtrl"; break; }
        case (sf::Keyboard::LShift      	) : { ans = "LShft"; break; }
        case (sf::Keyboard::LAlt        	) : { ans = "LAlt"; break; }
        case (sf::Keyboard::LSystem     	) : { ans = "LSys"; break; }
        case (sf::Keyboard::RControl    	) : { ans = "RCtrl"; break; }
        case (sf::Keyboard::RShift      ) : { ans = "RShft"; break; }
        case (sf::Keyboard::RAlt        ) : { ans = "RAlt"; break; }
        case (sf::Keyboard::RSystem     ) : { ans = "RSys"; break; }
        case (sf::Keyboard::Menu        ): { ans = "Menu"; break; }
        case (sf::Keyboard::LBracket     ) : { ans = "LBracket"; break; }
        case (sf::Keyboard::RBracket     ) : { ans = "RBracket"; break; }
        case (sf::Keyboard::SemiColon    ) : { ans = ";"; break; }
        case (sf::Keyboard::Comma        ) : { ans = ","; break; }
        case (sf::Keyboard::Period       ) : { ans = "."; break; }
        case (sf::Keyboard::Quote        ) : { ans = "\""; break; }
        case (sf::Keyboard::Slash        ) : { ans = "\\"; break; }
        case (sf::Keyboard::BackSlash    ) : { ans = "/"; break; }
        case (sf::Keyboard::Tilde        ) : { ans = "~"; break; }
        case (sf::Keyboard::Equal        ) : { ans = "="; break; }
        case (sf::Keyboard::Dash         ) : { ans = "-"; break; }
        case (sf::Keyboard::Space   		) : { ans = " "; break; }
        case (sf::Keyboard::Return  		) : { ans = "return"; break; }
        case (sf::Keyboard::BackSpace   		) : { ans = "backspace"; break; }
        case (sf::Keyboard::Tab         		) : { ans = "tab"; break; }
        case (sf::Keyboard::PageUp    		) : { ans = "pageup"; break; }
        case (sf::Keyboard::PageDown    		) : { ans = "pagedown"; break; }
        case (sf::Keyboard::End   		) : { ans = "end"; break; }
        case (sf::Keyboard::Home  		) : { ans = "home"; break; }
        case (sf::Keyboard::Insert   		) : { ans = "Insert"; break; }
        case (sf::Keyboard::Delete   		) : { ans = "Delete"; break; }
        case (sf::Keyboard::Add          ) : { ans = "Add"; break; }
        case (sf::Keyboard::Subtract     ) : { ans = "Subtract"; break; }
        case (sf::Keyboard::Multiply     ) : { ans = "Multiply"; break; }
        case (sf::Keyboard::Divide       ) : { ans = "Divide"; break; }
        case (sf::Keyboard::Left         ) : { ans = "Left"; break; }
        case (sf::Keyboard::Right        ) : { ans = "Right"; break; }
        case (sf::Keyboard::Up         ) : { ans = "Up"; break; }
        case (sf::Keyboard::Down         ) : { ans = "Down"; break; }
        case (sf::Keyboard::Numpad0      ) : { ans = "Numpad0"; break; }
        case (sf::Keyboard::Numpad1      ) : { ans = "Numpad1"; break; }
        case (sf::Keyboard::Numpad2      ) : { ans = "Numpad2"; break; }
        case (sf::Keyboard::Numpad3      ) : { ans = "Numpad3"; break; }
        case (sf::Keyboard::Numpad4      ) : { ans = "Numpad4"; break; }
        case (sf::Keyboard::Numpad5      ) : { ans = "Numpad5"; break; }
        case (sf::Keyboard::Numpad6      ) : { ans = "Numpad6"; break; }
        case (sf::Keyboard::Numpad7      ) : { ans = "Numpad7"; break; }
        case (sf::Keyboard::Numpad8      ) : { ans = "Numpad8"; break; }
        case (sf::Keyboard::Numpad9      ) : { ans = "Numpad9"; break; }
        case (sf::Keyboard::F1          ) : { ans = "F1"; break; }
        case (sf::Keyboard::F2          ) : { ans = "F2"; break; }
        case (sf::Keyboard::F3          ) : { ans = "F3"; break; }
        case (sf::Keyboard::F4          ) : { ans = "F4"; break; }
        case (sf::Keyboard::F5          ) : { ans = "F5"; break; }
        case (sf::Keyboard::F6          ) : { ans = "F6"; break; }
        case (sf::Keyboard::F7          ) : { ans = "F7"; break; }
        case (sf::Keyboard::F8          ) : { ans = "F8"; break; }
        case (sf::Keyboard::F9          ) : { ans = "F9"; break; }
        case (sf::Keyboard::F10          ) : { ans = "F10"; break; }
        case (sf::Keyboard::F11          ) : { ans = "F11"; break; }
        case (sf::Keyboard::F12          ) : { ans = "F12"; break; }
        case (sf::Keyboard::F13          ) : { ans = "F13"; break; }
        case (sf::Keyboard::F14          ) : { ans = "F14"; break; }
        case (sf::Keyboard::F15         ) : { ans = "F15"; break; }
        case (sf::Keyboard::Pause        ) : { ans = "Pause"; break; }
		default : { ans = "not valid";break;}
	}
	return ans;
}

inline std::string toString(KeyboardInput key) {
	string ans;
	switch(key) {
		case (ACCELERATE) : { ans = "accelerate"; break; }
		case (DECELERATE) : { ans = "decelerate"; break; }
		case (STRAFE_LEFT) : { ans = "strafe-left"; break; }
		case (STRAFE_RIGHT) : { ans = "strafe-right"; break; }
		case (ASCEND) : { ans = "ascend"; break; }
		case (DESCEND) : { ans = "descend"; break; }
		case (PITCH_UP) : { ans = "pitch-up" ; break; }
		case (PITCH_DOWN) : { ans = "pitch-down" ; break; }
		case (YAW_LEFT) : { ans = "yaw-left" ; break; }
		case (YAW_RIGHT) : { ans = "yaw-right" ; break; }
		case (ROLL_LEFT) : { ans = "right-left" ; break; }
		case (ROLL_RIGHT) : { ans = "roll-right" ; break; }
		case (TOGGLE_FULLSCREEN) : { ans = "toggle-fscrn" ; break; }
		case (TOGGLE_CAM) : { ans = "toggle-cam" ; break; }
		case (FIRE_WEAPON) : { ans = "shoot" ; break; }
		case (TOGGLE_WEAPON) : { ans = "toggle-weapon" ; break; }
		case (USE_ABILITY) : { ans = "use-ability" ; break; }
		case (ESCAPE) : { ans = "escape" ; break; }
		case (START_CHAT) : { ans = "start-chat" ; break; }
		case (ESCAPE_CHAT) : { ans = "escape-chat" ; break; }
		case (SEND_CHAT) : { ans = "send-chat" ; break; }
		default : { ans = "not valid";break;}
	}
	return ans;	
}
inline sf::Keyboard::Key keyFromString(std::string str) {
	sf::Keyboard::Key ans= sf::Keyboard::Unknown;

	if ( str == "A") { ans=sf::Keyboard::A; return ans; }
	if ( str == "B") { ans=sf::Keyboard::B; return ans; }
	if ( str == "C") { ans=sf::Keyboard::C; return ans; }
	if ( str == "D") { ans=sf::Keyboard::D; return ans; }
	if ( str == "E") { ans=sf::Keyboard::E; return ans; }
	if ( str == "F") { ans=sf::Keyboard::F; return ans; }
	if ( str == "G") { ans=sf::Keyboard::G; return ans; }
	if ( str == "H") { ans=sf::Keyboard::H; return ans; }
	if ( str == "I") { ans=sf::Keyboard::I; return ans; }
	if ( str == "J") { ans=sf::Keyboard::J; return ans; }
	if ( str == "K") { ans=sf::Keyboard::K; return ans; }
	if ( str == "L") { ans=sf::Keyboard::L; return ans; }
	if ( str == "M") { ans=sf::Keyboard::M; return ans; }
	if ( str == "N") { ans=sf::Keyboard::N; return ans; }
	if ( str == "O") { ans=sf::Keyboard::O; return ans; }
	if ( str == "P") { ans=sf::Keyboard::P; return ans; }
	if ( str == "Q") { ans=sf::Keyboard::Q; return ans; }
	if ( str == "R") { ans=sf::Keyboard::R; return ans; }
	if ( str == "S") { ans=sf::Keyboard::S; return ans; }
	if ( str == "T") { ans=sf::Keyboard::T; return ans; }
	if ( str == "U") { ans=sf::Keyboard::U; return ans; }
	if ( str == "V") { ans=sf::Keyboard::V; return ans; }
	if ( str == "W") { ans=sf::Keyboard::W; return ans; }
	if ( str == "X") { ans=sf::Keyboard::X; return ans; }
	if ( str == "Y") { ans=sf::Keyboard::Y; return ans; }
	if ( str == "Z") { ans=sf::Keyboard::Z; return ans; }
	if ( str == "Num0") { ans=sf::Keyboard::Num0; return ans; }
	if ( str == "Num1") { ans=sf::Keyboard::Num1; return ans; }
	if ( str == "Num2") { ans=sf::Keyboard::Num2; return ans; }
	if ( str == "Num3") { ans=sf::Keyboard::Num3; return ans; }
	if ( str == "Num4") { ans=sf::Keyboard::Num4; return ans; }
	if ( str == "Num5") { ans=sf::Keyboard::Num5; return ans; }
	if ( str == "Num6") { ans=sf::Keyboard::Num6; return ans; }
	if ( str == "Num7") { ans=sf::Keyboard::Num7; return ans; }
	if ( str == "Num8") { ans=sf::Keyboard::Num8; return ans; }
	if ( str == "Num9") { ans=sf::Keyboard::Num9; return ans; }
	if ( str == "Esc") { ans=sf::Keyboard::Escape; return ans; }
	if ( str == "LCtrl") { ans=sf::Keyboard::LControl; return ans; }
	if ( str == "LShft") { ans=sf::Keyboard::LShift; return ans; }
	if ( str == "LAlt") { ans=sf::Keyboard::LAlt; return ans; }
	if ( str == "LSys") { ans=sf::Keyboard::LSystem; return ans; }
	if ( str == "RCtrl")  { ans=sf::Keyboard::RControl; return ans; }
	if ( str == "RShft")  { ans=sf::Keyboard::RShift; return ans; }
	if ( str == "RAlt")  { ans=sf::Keyboard::RAlt; return ans; }
	if ( str == "RSys")  { ans=sf::Keyboard::RSystem; return ans; }
	if ( str == "Menu")  { ans=sf::Keyboard::Menu; return ans; }
	if ( str == "LBracket")  { ans=sf::Keyboard::LBracket; return ans; }
	if ( str == "RBracket")  { ans=sf::Keyboard::RBracket; return ans; }
	if ( str == "pageup")  { ans=sf::Keyboard::PageUp; return ans; }
	if ( str == "pagedown")  { ans=sf::Keyboard::PageDown; return ans; }
	if ( str == "Left")  { ans=sf::Keyboard::Left; return ans; }
	if ( str == "Right")  { ans=sf::Keyboard::Right; return ans; }
	if ( str == "Up")  { ans=sf::Keyboard::Up; return ans; }
	if ( str == "Down")  { ans=sf::Keyboard::Down; return ans; }
	if ( str == "Numpad0")  { ans=sf::Keyboard::Numpad0; return ans; }
	if ( str == "Numpad1")  { ans=sf::Keyboard::Numpad1; return ans; }
	if ( str == "Numpad2")  { ans=sf::Keyboard::Numpad2; return ans; }
	if ( str == "Numpad3")  { ans=sf::Keyboard::Numpad3; return ans; }
	if ( str == "Numpad4")  { ans=sf::Keyboard::Numpad4; return ans; }
	if ( str == "Numpad5")  { ans=sf::Keyboard::Numpad5; return ans; }
	if ( str == "Numpad6")  { ans=sf::Keyboard::Numpad6; return ans; }
	if ( str == "Numpad7")  { ans=sf::Keyboard::Numpad7; return ans; }
	if ( str == "Numpad8")  { ans=sf::Keyboard::Numpad8; return ans; }
	if ( str == "Numpad9")  { ans=sf::Keyboard::Numpad9; return ans; }
	if ( str == "F1")  { ans=	sf::Keyboard::F1;  return ans; }
	if ( str == "F2")  { ans=	sf::Keyboard::F2;  return ans; }
	if ( str == "F3")  { ans=	sf::Keyboard::F3;  return ans; }
	if ( str == "F4")  { ans=	sf::Keyboard::F4;  return ans; }
	if ( str == "F5")  { ans=	sf::Keyboard::F5;  return ans; }
	if ( str == "F6")  { ans=	sf::Keyboard::F6;  return ans; }
	if ( str == "F7")  { ans=	sf::Keyboard::F7;  return ans; }
	if ( str == "F8")  { ans=	sf::Keyboard::F8;  return ans; }
	if ( str == "F9")  { ans=	sf::Keyboard::F9;  return ans; }
	if ( str == "F10")  { ans=sf::Keyboard::F10;  return ans; }
	if ( str == "F11")  { ans=sf::Keyboard::F11;  return ans; }
	if ( str == "F12")  { ans=sf::Keyboard::F12;  return ans; }
	if ( str == "F13")  { ans=sf::Keyboard::F13;  return ans; }
	if ( str == "F14")  { ans=sf::Keyboard::F14;  return ans; }
	if ( str == "F15")  { ans=sf::Keyboard::F15;  return ans; }
	else {ans=sf::Keyboard::Unknown; return ans;}

	return ans;
}

#endif