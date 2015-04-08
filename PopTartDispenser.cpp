#include <iostream>
#include <string>
#include <vector>
#include "States.h"
#include "StateSetup.h"


using namespace std;

class PopTartDispenser: public StateContext, Transition, Functionality
{
protected:
	vector<string> userOptions;
	bool machineOn;
public:
	PopTartDispenser(int numOfProducts)
	{
		//turns the machine on
		machineOn = true;

		//adds the states the to the available states vector
		this->availableStates.push_back(new OutOfPopTarts(this));
		this->availableStates.push_back(new NoCredit(this));
		this->availableStates.push_back(new HasCredit(this));
		this->availableStates.push_back(new DispensesPopTart(this));

		//adds the state paramaters to the vector
		this->stateParameters.push_back(0); //No of Pop Tarts
		this->stateParameters.push_back(0); //Available Credit
		this->stateParameters.push_back(0); //Cost of Pop Tart (modified at later date)

		//adds user options to the vector
		this->userOptions.push_back("Insert Money");
		this->userOptions.push_back("Eject Money");
		this->userOptions.push_back("Make Selection");

		//sets the initial state
		this->setState(Out_Of_Pop_Tarts);

		//calls the first method
		if (numOfProducts > 0)
		{
			this->addPopTarts(numOfProducts);
		}

	}

	//calls the transition methods for the current state the dispenser is in
	void insertMoney()
	{
		this->currentState->insertMoney();

	}
	void makeSelection()
	{	
		this->currentState->makeSelection();
	}
	void moneyRejected(void) 
	{
		this->currentState->moneyRejected();
	}
	void addPopTarts(int amount)
	{
		this->currentState->addPopTarts(amount);
	}
	void dispense(void) 
	{
		this->currentState->dispense();
	}


	void displayMenu()
	{
		//main loop
		string selection;
	
		while(machineOn == true)
		{
			cout << "______________________________________________________" << endl;
			cout << "Current Credit: " << this->getStateParameter(Credit) << endl;
			cout << "Stock: " << this->getStateParameter(No_Of_Pop_Tarts) << endl;
			cout << "______________________________________________________" << endl;
			
			//Displays the user options
			this->displayVector(userOptions);


			cout << "Please choose an option. (Enter the number that corresponds to your choice)" << endl;
			selection = handleUserEntry(userOptions);
		
			//calls the relevant transition function depending on user selection
			if (selection == "Make Selection")
			{
				this->makeSelection();
				this->dispense();
				
			}
			else if (selection == "Insert Money")
			{
				this->insertMoney();
			}
			else if (selection == "Eject Money")
			{
				this->moneyRejected();
			}
		}

	}

};