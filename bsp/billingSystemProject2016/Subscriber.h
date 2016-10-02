#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <string>
#include <vector>
#include "PhoneCall.h"
class ISubscriber
{
public:
	virtual std::string GetSubscriberNumber() const = 0;
	virtual std::string GetLastCreditDate  () const = 0;
};

class Subscriber : public ISubscriber
{
public:
	Subscriber( const std::string firstName, const std::string lastName,
		const std::string phoneNumber, const std::string lastCreditDate);
	~Subscriber();
	std::string GetSubscriberNumber()const;
	std::string GetLastCreditDate  ()const;
	void AttachPhoneCall(PhoneCall* pPhoneCall);
	void SetTotalPayment(float totalPayment);
	void ShowReport()const;
	std::vector<PhoneCall*> mCallsVec;
private:
	std::string mFirstName;
	std::string mLastName;
	std::string mPnoneNumber;
	std::string mLastCreditDate;
	float       mTotalPayment;
};

#endif// SUBSCRIBER_H