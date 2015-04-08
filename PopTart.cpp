#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "PopTart.h"

using namespace std;

PopTart::PopTart()
{
	//populates the list of filling types
	fillingTypes.push_back("Chocolate");
	fillingTypes.push_back("Fudge");
	fillingTypes.push_back("Chocolate Fudge");
	fillingTypes.push_back("Vanilla Cream");
	fillingTypes.push_back("Wild Berry");
	fillingTypes.push_back("Blueberry");
	fillingTypes.push_back("Cherry");
	fillingTypes.push_back("Raspberry");
	fillingTypes.push_back("Strawberry");
	fillingTypes.push_back("Peanut Butter");
	fillingTypes.push_back("Cookies & Cream");
	fillingTypes.push_back("Cookie Dough");

	//populates the list of coatings
	coatingTypes.push_back("Frosted");
	coatingTypes.push_back("Wildlicious");
	coatingTypes.push_back("Smarties");
	coatingTypes.push_back("Chocolate");
	coatingTypes.push_back("Hundreds & Thousands");
	coatingTypes.push_back("Jelly Bean");
	coatingTypes.push_back("Wild Berry");
	coatingTypes.push_back("Brown Sugar");
	coatingTypes.push_back("Chocolate Chip");

	factory = new CoatingFactory;
}

void PopTart::prepare()
{
	//prepares the pop tart for dispensing

	bakeCoatings();
	warmCenter();
}

void PopTart::bakeCoatings()
{
	//bakes coatings on to the pop tart

	

	//takes the coating strings from the chosingCoatings vector and creates objects of them using the coating factory
	//then adds them to coatingsOnTart vector
	for (int i = 0; i < chosenCoatings.size(); i++)
	{
		coatingsOnTart.push_back(factory->createCoating(chosenCoatings[i]));
	}

	//calls the overridden bake method for each coating
	for (int i = 0; i < coatingsOnTart.size(); i++)
	{
		coatingsOnTart[i]->bake();
	}
}

void PopTart::warmCenter()
{
	//warms the center of the pop tart

	cout << "Warming " << chosenFilling << " center of Pop Tart" << endl;
}

vector<string> PopTart::getFillings()
{
	//returns the vector of filling types

	return fillingTypes;
}

vector<string> PopTart::getCoatings()
{
	//returns the vector of coating types

	return coatingTypes;
}

vector<string> PopTart::getChosenCoatings()
{
	//returns the vector of coatings chosen by the user

	return chosenCoatings;
}

string PopTart::getChosenFilling()
{
	//returns the filling chosen by the user

	return chosenFilling;
}

void PopTart::setChosenFilling(string fillingChoice)
{
	//sets the filling chosen by the user

	chosenFilling = fillingChoice;
}


void PopTart::addCoating(string coatingChoice)
{
	//adds a coating chosen by the user to the vector

	chosenCoatings.push_back(coatingChoice);
}

int PopTart::getCost()
{
	//returns the cost of a Pop Tart without a filling

	return 100;
}


CoatingDecorator::~CoatingDecorator()
{
	//Destructor

	delete popTart;
}

void CoatingDecorator::addToTart(PopTart* customerPopTart)
{
	//sets the popTart to the popTart sent to the method

	popTart = customerPopTart;
}

CoatingFactory::CoatingFactory()
{

	//adds coatings to the map along with their key
	map["Frosted"] = &createInstance<Frosted>;
	map["Wildlicious"] = &createInstance<Wildlicious>;
	map["Smarties"] = &createInstance<Smarties>;
	map["Chocolate"] = &createInstance<Chocolate>;
	map["Hundreds & Thousands"] = &createInstance<HundredsAndThousands>;
	map["Jelly Bean"] = &createInstance<JellyBeans>;
	map["Wild Berry"] = &createInstance<WildBerry>;
	map["Brown Sugar"] = &createInstance<BrownSugar>;
	map["Chocolate Chip"] = &createInstance<ChocolateChip>;
}

CoatingDecorator* CoatingFactory::createCoating(string type)
{	
	//takes the string 'type' and sends it to the map which then calls the relevant createInstance function
	//and returns an object of 'type'

	return map[type]();	
}

class Frosted : public CoatingDecorator
{
	//adds the cost of the coating on to the pop tart
	int getCost()
	{
		return (20+popTart->getCost());
	}

	//bakes the coating on to the pop tart
	void bake()
	{
		cout << "Baking Frosted coating on to Pop Tart" << endl;
	}
};

class Wildlicious : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Wildlicious coating on to Pop Tart" << endl;
	}
};

class Smarties : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Smarties coating on to Pop Tart" << endl;
	}

};

class Chocolate : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Chocolate coating on to Pop Tart" << endl;
	}

};

class HundredsAndThousands : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Hundreds & Thousands coating on to Pop Tart" << endl;
	}

};

class JellyBeans : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Jelly Beans coating on to Pop Tart" << endl;
	}

};

class WildBerry : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Wild Berry coating on to Pop Tart" << endl;
	}

};

class BrownSugar : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Brown Sugar coating on to Pop Tart" << endl;
	}

};

class ChocolateChip : public CoatingDecorator
{
	int getCost()
	{
		return (20+popTart->getCost());
	}

	void bake()
	{
		cout << "Baking Chocolate Chip coating on to Pop Tart" << endl;
	}

};

