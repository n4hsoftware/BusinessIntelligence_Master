#ifndef _OMSHANDLER_H_
#define _OMSHANDLER_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
class OMSHandler
{
	public:
		OMSHandler(){};
	        int  OMSStart();
		bool OMSStop();
		~OMSHandler(){};
};

#endif
