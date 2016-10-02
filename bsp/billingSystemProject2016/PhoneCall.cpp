#include "PhoneCall.h"

const std::string& PhoneCall::GetSubscriberNumber()
{
	return mSubscriberNumber;
}

const std::string& PhoneCall::GetCalledNumber()
{
	return mCalledNumber;
}

const std::string& PhoneCall::GetTimeCallStart()
{
	return mTimeCallStart;
}

const std::string& PhoneCall::GetTimeCallFinish()
{
	return mTimeCallFinish;
}

void  PhoneCall::SetCallPayment(const float cost)
{
	mCost = cost;
}

void PhoneCall::ShowReport() const 
{
	std::cout<<"Time start: "<<mTimeCallStart<<"Time finish: "<<mTimeCallFinish<<" Phone number: "<<mCalledNumber<<" Call cost = "<<mCost<<std::endl;
}

PhoneCall::~PhoneCall()
{

} 
