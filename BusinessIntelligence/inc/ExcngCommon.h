#ifndef _OMSTOEXCNG_H_
#define _OMSTOEXCNG_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
namespace ExchngCommon
{
	class MsgHdr
	{
		public:
			short sTxnCode;
			long lLogTime;
			char caAlphaChar[2];
			long lTraderID;
			short sErrorCode;
			long long llTimeStamp;
			char caTimeStamp[8];
			char caTimeStamp1[8];
			short sMsgLength;
	};
}
#endif
