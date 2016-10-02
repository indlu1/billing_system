#include "Subscriber.h"

Subscriber::Subscriber( const std::string firstName,const  std::string lastName,
					   const  std::string phoneNumber, const std::string lastCreditDate):
mFirstName(firstName),
mLastName (lastName),
mPnoneNumber(phoneNumber),
mLastCreditDate(lastCreditDate)
{

}

std::string Subscriber::GetLastCreditDate()const
{
	return mLastCreditDate;
}

std::string Subscriber::GetSubscriberNumber()const
{
	return mPnoneNumber;
}

void Subscriber::AttachPhoneCall(PhoneCall* pPhoneCall) 
{
	mCallsVec.push_back(pPhoneCall);
}

void Subscriber:: SetTotalPayment(float totalPayment)
{
    mTotalPayment = totalPayment;
}
void Subscriber::ShowReport() const 
{
	std::cout<<"First name: "<<mFirstName<<" Last name: "<<mLastName<<" PhoneNumber: "<<mPnoneNumber<<" Last credit date:"<<mLastCreditDate <<std::endl;
	for(int i = 0; i<mCallsVec.size(); i++)
	{
	   mCallsVec[i]->ShowReport();
	}
	std::cout<<"Total cost = "<<mTotalPayment<<std::endl<<std::endl;
}
Subscriber::~Subscriber()
{
	 
}


