#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "TimeTools.h"
class Accounting 
{
private:
	std::vector < class Subscriber* > mSubscribersVec;
	std::vector < class PhoneCall* > mCallsVec;
public:
	void  AttachPhoneCall  ( PhoneCall*  pPhoneCall);
	void  AttachSubscriber ( Subscriber* pSubscriber);
	void  CalculateSubscriberPayment( );
	void  CalculateSubscriberPayment( Subscriber* pSubscriber);
	void  DistributeCallsToSubscribers( );
	float GetCallDuration  (Subscriber* pSubscriber, int index);
	void  SetCallPayment   (Subscriber* pSubscriber, int index, float callPayment);
	void  CalculatePaymentInsideNetwork (float& payment,float duration);
	void  CalculatePaymentOutsideNetwork(float& payment,float duration);
	bool  IsThirtyDaysExpired(Subscriber* pSubscriber, int index);
    bool  IsWeekend(Subscriber* pSubscriber, int index );
	bool  IsHomeNetwork(Subscriber* pSubscriber, int index, const std::string& prefix);
	void  LoadingFromFile(const std::string fileName);
	~Accounting();
};
#endif// ACCOUNTING_H