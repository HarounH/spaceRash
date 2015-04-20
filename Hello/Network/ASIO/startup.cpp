#include "server.h"


int main(){
	cout << "HELLO server" << '\n';

	Server s("10.192.31.236", 3001, 2000); //

	cout << "break 1" << '\n';


	//s.run_service();


	cout << "break 2" << '\n';

	
	while (true)
	{
		s.SendToAll("HELLO");
		int i = 0;
		while(i < 1000000)
			i++;
	}

	cout << "DONE" << '\n';
}