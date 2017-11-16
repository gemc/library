// gdata
#include "gobservables.h"

// the functions are overloaded instead of templated

void GObservables::addObservable(int var, string varName, string vunit, string saveAs)
{
	addObservableAndUnit(varName, vunit);
	
	if(saveAs == "int") {
		gTypeIndex.push_back((int) intVar.size()*GINTINDEXMULTIPLIER);
		gType.push_back(gint_t);
		intVar.push_back(var);
	} else {
		throw "Variable type does not match an int";
	}
}


void GObservables::addObservable(float var, string varName, string vunit, string saveAs)
{
	addObservableAndUnit(varName, vunit);
	
	if(saveAs == "float") {
		gTypeIndex.push_back((int) floatVar.size()*GFLOINDEXMULTIPLIER);
		gType.push_back(gfloat_t);
		floatVar.push_back(var);
	} else {
		throw "Variable type does not match a float";
	}
}

void GObservables::addObservable(double var, string varName, string vunit, string saveAs)
{
	addObservableAndUnit(varName, vunit);
	
	if(saveAs == "double") {
		gTypeIndex.push_back((int) doubleVar.size()*GDBLINDEXMULTIPLIER);
		gType.push_back(gdouble_t);
		doubleVar.push_back(var);
	} else {
		throw "Variable type does not match a double";
	}
}

void GObservables::addObservable(string var, string varName, string vunit, string saveAs)
{
	addObservableAndUnit(varName, vunit);
	
	if(saveAs == "string") {
		gTypeIndex.push_back((int) stringVar.size()*GSTRINDEXMULTIPLIER);
		gType.push_back(gstring_t);
		stringVar.push_back(var);
	} else {
		throw "Variable type does not match a string";
	}
}


void GObservables::addObservableAndUnit(string name, string vunit)
{
	// only add name, description if variable is not found
	if(!unitsAssigned) {
		varName.push_back(name);
		varUnit.push_back(vunit);
	}
}

void GObservables::clearNamesAndUnits()
{
	varName.clear();
	varUnit.clear();
	unitsAssigned = true;
}


int GObservables::getVariableIndex(int forIndex)
{
	int gindex = gTypeIndex[forIndex];
	
	switch(gType[forIndex]) {
	
	case gint_t:
		return gindex;
		break;
	case gfloat_t:
		return gindex/GFLOINDEXMULTIPLIER;
		break;
	case gdouble_t:
		return gindex/GDBLINDEXMULTIPLIER;
		break;
	case gstring_t:
		return gindex/GSTRINDEXMULTIPLIER;
		break;
	}
}




