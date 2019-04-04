#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; //Forward class declaration
class Connection;	//Forward class declartion

class InputPin : public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	Connection *pIn;
	bool IsConnected;
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
	//void SetConnection(Connection *pIn);
	void SetConnectionStat(bool);
	bool GetConnectionStat();
	void SetConnection(Connection *r_pIn);
	int GetCompID() const;
};
#endif