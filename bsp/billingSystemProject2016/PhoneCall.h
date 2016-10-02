#ifndef PHONE_CALL_H
#define PHONE_CALL_H
#include "Accounting.h"

class PhoneCall 
{
public:
	PhoneCall(  const std::string subscriberNumber,	const std::string timeCallStart, 
		const std::string timeCallFinish, const std::string calledNumber):
	mSubscriberNumber(subscriberNumber),
	mTimeCallStart(timeCallStart),
	mTimeCallFinish(timeCallFinish),
	mCalledNumber(calledNumber)
	{
	}
	~PhoneCall();
	const std::string& GetSubscriberNumber();
	const std::string& GetCalledNumber();
	const std::string& GetTimeCallStart();
	const std::string& GetTimeCallFinish();
	void  SetCallPayment(const float cost);
    void  ShowReport() const;

private:
	float             mCost;
	const std::string mSubscriberNumber;
	const std::string mTimeCallStart;
	const std::string mTimeCallFinish;
	const std::string mCalledNumber;

};
#endif// PHONE_CALL_H