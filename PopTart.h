#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class CoatingDecorator;
class CoatingFactory;


class PopTart{
protected:
	vector<string> fillingTypes;
	vector<string> coatingTypes;
	string chosenFilling;
	vector<string> chosenCoatings;
	vector<CoatingDecorator*> coatingsOnTart;
	CoatingFactory* factory;
public:
	PopTart();
	void prepare();
	virtual void bake(){};
	void bakeCoatings();
	void warmCenter();
	vector<string> getFillings();
	vector<string> getCoatings();
	vector<string> getChosenCoatings();
	string getChosenFilling();
	void setChosenFilling(string fillingChoice);
	void addCoating(string coatingChoice);
	virtual int getCost();

};

class CoatingDecorator : public PopTart{
protected:
	PopTart* popTart;
public:
	void addToTart(PopTart* customerPopTart);
	~CoatingDecorator();
};

template<typename T> CoatingDecorator * createInstance() { return new T; }

typedef map<string, CoatingDecorator*(*)()> map_type;

class CoatingFactory{
protected:
	map_type map;
public:
	CoatingFactory();
	CoatingDecorator* createCoating(string type);


};
class Frosted;
class Wildlicious;
class Smarties;
class Chocolate;
class HundredsAndThousands;
class BrownSugar;
class JellyBeans;
class WildBerry;
class ChocolateChip;