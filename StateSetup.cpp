#include <iostream>
#include <string>
#include <vector>
#include <sstream>
//#include "PopTart.h"
#include "StateSetup.h"



//class containing extra methods used by states & PopTart interface

string Functionality::validateYesNo(string str)
{
	//validates user y/n input and returns a valid input

	string answer;

	if (str == "y" || str == "n" || str ==  "Y" || str == "N")
	{	answer = str;
		return answer;
	}

	while (str != "y" && str != "n" && str !=  "Y" && str != "N")
	{
		cout << "Please enter a valid answer (y/n)" << endl;
		getline(cin,str);
	}

	answer = str;
	return answer;
}



int Functionality::stringToInt(string str)
{
	//converts a string to an integer;

	int num;

	stringstream convert(str);
	convert >> num;

	return num;
}

bool Functionality::validateNumber(int num, int maxCorrect, int minCorrect){
	
	//checks if a number is within two boundaries

	if(num >=minCorrect && num <=maxCorrect)
	{
		return true;
	}
	else
	{
		return false;
	}


	
}

string Functionality::handleUserEntry(vector<string> menu)
{
	int selection;
	string menuChoice;
	string textToNum;
	bool numOk;

	getline(cin,textToNum);
	
	//gets the int value of the users entry
	selection = stringToInt(textToNum);

	//checks the user has entered a valid number on the menu
	numOk = validateNumber(selection, menu.size(), 1);
	selection--;//makes the value of selection = to the index of the option selected

	//keeps asking for a new entry until user enters a valid number
	while (numOk == false)
	{
		cout << "Please enter a valid menu number" << endl;
		getline(cin,textToNum);
		selection = stringToInt(textToNum);
		numOk = validateNumber(selection,menu.size(), 1);
		selection--; //makes the value of selection = to the index of the option selected
	}

	//if entry is ok, return the string from the menu
	if (numOk == true)
	{
		menuChoice = menu[selection];
		return menuChoice;
	}

}


void Functionality::displayVector(vector<string> vecToDisplay)
{
	//prints out a vector sent to  it in list form
		
	for (int i = 0; i < vecToDisplay.size(); i++)
	{
		int num = i;
		num++;
		cout << num << ": " << vecToDisplay[i] << endl;
	}

}

State::State(StateContext* Context)
{
	//instatiates its variables

	currentContext = Context;
	popTart = new PopTart();
}




void StateContext::setState(state newState)
{
	//sets the state

	this->currentState = availableStates[newState];
}

StateContext::~StateContext()
{
	//destructor

	for (int i = 0; i < availableStates.size(); i++)
	{
		delete availableStates[i];
	}
}

void StateContext::setStateParameter(stateParameter stateParam, int value)
{
	//sets one of the parameters

	this->stateParameters[stateParam] = value;
}

int StateContext::getStateParameter(stateParameter stateParam)
{
	//returns one of the parameters

	return this->stateParameters[stateParam];
}


