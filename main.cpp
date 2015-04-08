#include <iostream>
#include "PopTartDispenser.cpp"

using namespace std;

//prevents linker error
PopTart* State::popTart;

int main()
{
	string pause;
	//create new dispenser and add pop tarts
	PopTartDispenser* dispenser = new PopTartDispenser(2);

	dispenser->displayMenu();

	cin >> pause;
	return 0;
}