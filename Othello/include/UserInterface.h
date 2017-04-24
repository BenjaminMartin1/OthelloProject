#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>


using namespace std;


class UserInterface
{
	public:
		UserInterface();
		virtual ~UserInterface();

		static void setup();
		static void hello();
		static void bye(int score);

		static int menu();

	private:
};

#endif // USERINTERFACE_H
