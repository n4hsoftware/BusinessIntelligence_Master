#include "OMSHandler.h"
#include "OMSConstants.h"
int main()
{
	int iRetVal = 0;
	OMSHandler objOfOMSHandler;
        iRetVal = objOfOMSHandler.OMSStart();
	if (iRetVal != SUCCESS)
	{
		std::cout<<"Failed To Start OMS"<<std::endl;
		return iRetVal;
	}
	return iRetVal;
}
