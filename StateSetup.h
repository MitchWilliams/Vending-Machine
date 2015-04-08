#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "PopTart.h"

class StateFunctionality;
class StateContext;
enum state{Out_Of_Pop_Tarts, No_Credit, Has_Credit, Dispenses_Pop_Tart};
enum stateParameter{No_Of_Pop_Tarts, Credit, Cost_Of_Pop_Tart};

using namespace std;

class Transition
{
protected:

public:

	virtual void insertMoney() {}
	virtual void makeSelection() {}
	virtual void moneyRejected(void) {}
	virtual void addPopTarts(int amount){}
	virtual void dispense(void) {}
	
};

//class that adds extra functionality
class Functionality
{
protected:
	
public:
	string validateYesNo(string str);
	int stringToInt(string str);
	bool validateNumber(int num, int maxCorrect, int minCorrect);
	void displayVector(vector<string> vecToDisplay);
	string handleUserEntry(vector<string>menu);
};



class State: public Transition, public Functionality
{
protected:
	StateContext* currentContext;
	static PopTart* popTart;
public:
	State(StateContext* Context);
};

class StateContext
{
protected:
	State* currentState;
	vector<State*> availableStates;
	vector<int>stateParameters;

public:
	void setState(state newState);

	~StateContext();

	void setStateParameter(stateParameter stateParam, int value);

	int getStateParameter(stateParameter stateParam);


};

