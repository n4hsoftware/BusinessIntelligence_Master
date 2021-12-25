#include "OMSHandler.h" 
#include "ExchngConnector.h"
using namespace ExchngConnector;
int OMSHandler::OMSStart()
{
        int iRetVal = 0 ;
	NSEConnector ObjOfNSEConnector;
	iRetVal = ObjOfNSEConnector.ConnectToNSE();
	return iRetVal;       
}
bool OMSHandler::OMSStop()
{
	return 0;
}

