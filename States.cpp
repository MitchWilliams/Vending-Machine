#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <time.h>
//#include "StateSetup.h"
#include "States.h"
//#include "PopTart.h"


using namespace std;



//Transitions for when the machine is out of pop tarts

void OutOfPopTarts::insertMoney()
{
	cout << "No Pop Tarts remaining! Returning money!" << endl;
}

void OutOfPopTarts::makeSelection()
{
	cout << "No Pop Tarts remaining! No selection made!" << endl;
}

void OutOfPopTarts::moneyRejected(void)
{
	cout << "Returning!" << endl; 
}

void OutOfPopTarts::addPopTarts(int number)
{
	this->currentContext->setStateParameter(No_Of_Pop_Tarts, number);
	this->currentContext->setState(No_Credit);
}

void OutOfPopTarts::dispense(void)
{
	cout << "No Pop Tarts remaining! Nothing to dispense!" << endl;
}




//Transitions for when the machine has no credit
void NoCredit::insertMoney()
{
	int money ;
	string userEntry;
	bool numOk;

	//asks the user to enter money
	cout << "Please enter money in pence format (e.g. '120')" << endl << "(Cheapest product is 120, this machine accepts no more than 500): ";
	getline(cin,userEntry);
	money = stringToInt(userEntry);

	//checks that they have entered a valid number
	numOk = validateNumber(money, 500, 120);
	while (numOk == false)
	{
		cout << "That is not a valid amount of money. The total credit must be between 120 & 500. It is currently: " 
			<< this->currentContext->getStateParameter(Credit) << endl;
		getline(cin,userEntry);
		money = stringToInt(userEntry);
		numOk = validateNumber(money,500,120);
	}

	cout << money << " inserted!" << endl;
	cout << "Total credit is " << money << endl;

	//updates the Credit paramater and then changes the state
	this->currentContext->setStateParameter(Credit, money);
	this->currentContext->setState(Has_Credit);
		
}

void NoCredit::makeSelection()
{
	cout << "You have no credit! No selection made" << endl;
}

void NoCredit::moneyRejected(void)
{
	cout << "There is no money to reject!" << endl; 
}

void NoCredit::addPopTarts(int number)
{
	cout << "There are already Pop Tarts in the machine!";
}

void NoCredit::dispense(void)
{
	cout << "No credit! Cannot dispense!" << endl;
}



//Transitions for when the machine has credit
void HasCredit::insertMoney()
{
	bool numOk;
	int money ;
	string userEntry;
	int newCredit;

	cout << "Please enter money in pence format (e.g. '120')" << endl;
	cout << "(Cheapest product is 120, this machine accepts no more than 500): ";
	getline(cin,userEntry);
	money = stringToInt(userEntry);
	//adds the value entered by the user to th amount of credit they already have
	newCredit = money + this->currentContext->getStateParameter(Credit);

	numOk =validateNumber(newCredit, 500, 120);
	while (numOk == false)
	{
		cout << "That is not a valid amount of money. The total credit must be between 120 & 500. It is currently: " 
				<< this->currentContext->getStateParameter(Credit) << endl;

		getline(cin,userEntry);
		money = stringToInt(userEntry);
		newCredit = money + this->currentContext->getStateParameter(Credit);
	}

		
	cout << money << " inserted!" << endl;
	cout << "Total credit is now " << newCredit << endl;

	//updates the credit
	this->currentContext->setStateParameter(Credit, newCredit);
		
}

void HasCredit::makeSelection()
{
	//allows user to select their pop tart filling & coatings

	string selection;
	string yesOrNo = "Y";

		

	//Display filling menu

	displayVector(this->popTart->getFillings());

	cout << "Please choose a filling (Enter the number that corresponds to your choice)" << endl;

	//Validate Answer
		
	selection = handleUserEntry(this->popTart->getFillings());
		
	this->popTart->setChosenFilling(selection);
		
	//Output choice

	cout << "You have selected a Pop Tart with " << selection << " filling." << endl;

	while (yesOrNo == "Y" || yesOrNo == "y")
	{

		//Display coating menu

		displayVector(this->popTart->getCoatings());

		cout << "Please choose a coating (Enter the number that corresponds to your choice)" << endl;

		//Validate answer

		selection = handleUserEntry(this->popTart->getCoatings());

		//add to popTart

		decoratePopTart(selection);

		//add to coating vector
		this->popTart->addCoating(selection);

		//Output choice

		cout << "You have chosen to add a coating of " << selection << " ." << endl;

		//ask if want another coating

		cout << "Do you want to add another coating?(y/n)" << endl;

		getline(cin, yesOrNo);
		//validate y/n

		yesOrNo = validateYesNo(yesOrNo);
	}

	//display price 
	this->currentContext->setStateParameter(Cost_Of_Pop_Tart, this->popTart->getCost());
	cout << "The price of your Pop Tart will be " << this->currentContext->getStateParameter(Cost_Of_Pop_Tart) << endl;

	this->currentContext->setState(Dispenses_Pop_Tart);

}

void HasCredit::moneyRejected(void)
{
	//rejects the users money & resets credit to 0

	cout << "Your money has been rejected! Ejecting money!" << endl; 
	this->currentContext->setStateParameter(Credit, 0);
	this->currentContext->setState(No_Credit);
}

void HasCredit::addPopTarts(int number)
{
	cout << "There are already Pop Tarts in the machine!" << endl;
}

void HasCredit::dispense(void)
{
	cout << "You have not yet made your selection! Cannot dispense!" << endl;
}

	


void HasCredit::decoratePopTart(string selection)
{
	//decorates the pop tart with the coating selected

	CoatingDecorator* currentCoating;
	CoatingFactory* factory = new CoatingFactory;

	//uses the factory to create a coating of the type selected
	//then adds that coating to the popTart
	currentCoating = factory->createCoating(selection);
	currentCoating->addToTart(this->popTart);

	//sets the chosen filling & chosen coating of the currentCoating to those of the currentCoating
	//so that they carry over when you make popTart = currentCoating
	currentCoating->setChosenFilling(this->popTart->getChosenFilling());
	
	for (int i = 0; i < this->popTart->getChosenCoatings().size(); i++)
	{
		currentCoating->addCoating(this->popTart->getChosenCoatings()[i]);
	}

	this->popTart = currentCoating;

	
}


//Transition for when the machine dispenses pop tarts
void DispensesPopTart::insertMoney()
{
	cout << "Cannot enter money while dispensing!" << endl;
		
}

void DispensesPopTart::makeSelection()
{
	cout << "Selection has already been made!" << endl;
}

void DispensesPopTart::moneyRejected(void)
{
	cout << "Cannot reject money while dispensing!" << endl; 
}

void DispensesPopTart::addPopTarts(int number)
{
	cout << "There are already Pop Tarts in the machine!" << endl;
}

void DispensesPopTart::dispense(void)
{
	float chance;

	//checks if the user has enough money to pay for their pop tart
	if(this->currentContext->getStateParameter(Credit) >= this->currentContext->getStateParameter(Cost_Of_Pop_Tart))
	{
		//if they do..

		//call the popTart prepare method
		this->popTart->prepare();
		//dispense the popTart
		cout << "Dispensing Pop Tart" << endl;
		//decrease the number of pop tarts in the machine)
		this->currentContext->setStateParameter(No_Of_Pop_Tarts, this->currentContext->getStateParameter(No_Of_Pop_Tarts)-1);

		//generates a random number between 0 & 1
		chance = generateNumber(1);

		//checks if the user has won their pop tart for free
		if (chance < 0.9)
		{
			cout << "Congratulations! You have won your Pop Tart for free!" << endl;
		}
		else
		{
			//if they haven't, reduce their credit by the cost of the pop tart
			this->currentContext->setStateParameter(Credit, this->currentContext->getStateParameter(Credit)-this->currentContext
				->getStateParameter(Cost_Of_Pop_Tart));
		}
			
	}

	else
	{
		//if they don't have enough money for the pop tart...

		cout << "You do not have enough credit for this Pop Tart!" << endl;
	}
		
	//sets the new state of the vending machine depending on credit and stock level
	if (this->currentContext->getStateParameter(Credit) > 0)
	{
		this->currentContext->setState(Has_Credit);
	}
	else
	{
		this->currentContext->setState(No_Credit);
	}

	if (this->currentContext->getStateParameter(No_Of_Pop_Tarts)==0)
	{
		cout << "The machine is out of stock. Please refill" << endl;
		this->currentContext->setState(Out_Of_Pop_Tarts);
	}


	
}

float DispensesPopTart::generateNumber(float max)
{
	//generates a random float number

	float num;

	//float generation from: http://stackoverflow.com/questions/686353/c-random-float-number-generation
	num = static_cast <float> (rand())/ static_cast <float> (RAND_MAX/max);

	return num;

}

