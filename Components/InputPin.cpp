#include "InputPin.h"
#include "Connection.h"
InputPin::InputPin()
{
	IsConnected = false;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}
void InputPin::SetConnectionStat(bool x)
{
	IsConnected = x;
}
bool InputPin::GetConnectionStat()
{
	return IsConnected;
}
void InputPin::SetConnection(Connection *r_pIn)
{
	pIn = r_pIn;

}

int InputPin::GetCompID() const
{
	int ID=pComp->GetID();
	return ID;
}

