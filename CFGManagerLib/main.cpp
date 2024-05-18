#include <iostream>
#include "CFGManager.h"


using namespace std;


int main()
{
	
	CFGManager cfg("C:\\Users\\Maksim\\Desktop\\data.txt");
	cfg.openconfig();

	cout << cfg.size() << endl;

	cfg.add_key("key", "new value");
	cfg.save("C:\\Users\\Maksim\\Desktop\\data2.txt");


	//
	//for (size_t i = 0; i < cfg.size(); i++)
	//{
	//	cout << cfg.
	//}


	return 0;
}