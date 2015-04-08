#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "StateSetup.h"

using namespace std;

class OutOfPopTarts: public State
{
public:

	OutOfPopTarts(StateContext* Context) : State(Context){}

	void insertMoney();
	void makeSelection();
	void moneyRejected();
	void addPopTarts(int number);
	void dispense();

};

class NoCredit: public State
{
public:

	NoCredit(StateContext* Context) : State(Context){}

	void insertMoney();
	void makeSelection();
	void moneyRejected();
	void addPopTarts(int number);
	void dispense();

};

class HasCredit: public State
{
public:

	HasCredit(StateContext* Context) : State(Context){}

	void insertMoney();
	void makeSelection();
	void moneyRejected();
	void addPopTarts(int number);
	void dispense();

	void decoratePopTart(string selection);

};

class DispensesPopTart: public State
{
public:

	//seeds random number function with the time
	DispensesPopTart(StateContext* Context) : State(Context){srand(static_cast <unsigned> (time(NULL)));}

	void insertMoney();
	void makeSelection();
	void moneyRejected();
	void addPopTarts(int number);
	void dispense();

	float generateNumber(float max);

};