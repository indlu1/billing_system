#include "Accounting.h"
#include "PhoneCall.h"
#include "Subscriber.h"

static const float MinutesFreeWeekend   = 5.00f;
static const float MinutesFreeInside    = 30.0f;
static const float DaysSinceLastCredit  = 5.00f;
static const float MoneyInside          = 0.50f;
static const float MoneyOutside         = 0.95f;
static const float ConnectionFee		= 0.33f;
static const std::string Prefix         = "050066095099";

void Accounting::AttachPhoneCall(PhoneCall* pPhoneCall) 
{
	mCallsVec.push_back(pPhoneCall);
}

void Accounting::AttachSubscriber(Subscriber* pSubscriber) 
{
	mSubscribersVec.push_back(pSubscriber);
}

void Accounting::DistributeCallsToSubscribers() 
{
	for (int i = 0; i < mSubscribersVec.size(); i++)
	{
		for (int j = 0; j < mCallsVec.size(); j++)
		{
			if((mSubscribersVec[i]->GetSubscriberNumber()).find(mCallsVec[j]->GetSubscriberNumber())!=-1)
			{
				mSubscribersVec[i]->AttachPhoneCall(mCallsVec[j]);
			}
		}
	}
}

void Accounting::CalculateSubscriberPayment()
{
	LoadingFromFile( "Subscribers.dat" ); 
	LoadingFromFile( "PhoneCalls.dat" );
	DistributeCallsToSubscribers();
	typedef std::vector< Subscriber* >::iterator subscriberIter;
	for( subscriberIter subIter = mSubscribersVec.begin(); subIter != mSubscribersVec.end(); ++subIter )
	{
		CalculateSubscriberPayment((*subIter));
		(*subIter)->ShowReport( );
	}
}
void Accounting::CalculateSubscriberPayment( Subscriber* pSubscriber )
{ 
	float minutesFreeInsideCurrent = MinutesFreeInside;
	float totalPayment = 0.0f;
	float localPayment = 0.0f;
	for(int curPhoneCallIndex = 0; curPhoneCallIndex < pSubscriber->mCallsVec.size();curPhoneCallIndex++)
	{
		localPayment = ConnectionFee;
		float duration       = GetCallDuration (pSubscriber,curPhoneCallIndex) + 1;
		bool  isWeekend      = IsWeekend       (pSubscriber,curPhoneCallIndex);
		bool  isHomeNetwork  = IsHomeNetwork   (pSubscriber,curPhoneCallIndex,Prefix);

		if(isWeekend)
		{
			duration -= MinutesFreeWeekend;
		}
		if( duration > 0.0f ) //weekend free minutes are over 
		{
			if(isHomeNetwork)
			{
				if(( minutesFreeInsideCurrent > 0.0f) && (!IsThirtyDaysExpired(pSubscriber,curPhoneCallIndex)))
				{
					if(duration <= minutesFreeInsideCurrent) 
					{
						minutesFreeInsideCurrent -= duration;
					}
					else      //free minutes are over
					{
						duration -= minutesFreeInsideCurrent;
						minutesFreeInsideCurrent = 0.0f;
						CalculatePaymentInsideNetwork(localPayment,duration);
					}
				}
				else
				{
					CalculatePaymentInsideNetwork(localPayment,duration);
				}
			}
			else
			{
				CalculatePaymentOutsideNetwork(localPayment,duration);
			}
			pSubscriber->mCallsVec[curPhoneCallIndex]->SetCallPayment(localPayment);
		}
		totalPayment += localPayment;
		pSubscriber->SetTotalPayment(totalPayment);
	}
}

void Accounting::CalculatePaymentInsideNetwork(float& payment,float duration)
{
	payment += duration * MoneyInside;
}

void Accounting::CalculatePaymentOutsideNetwork(float& payment,float duration)
{
	payment += duration * MoneyOutside;
}

float Accounting::GetCallDuration(Subscriber* pSubscriber, int index)
{
	return TimeTools::GetTimeDifferenceInMinutes( pSubscriber->mCallsVec[index]->GetTimeCallStart(),
		pSubscriber->mCallsVec[index]->GetTimeCallFinish());
}

void  Accounting::SetCallPayment(Subscriber* pSubscriber, int index, float callPayment)
{
	pSubscriber->mCallsVec[index]->SetCallPayment(callPayment);
}

bool  Accounting::IsThirtyDaysExpired(Subscriber* pSubscriber, int index)
{
	return TimeTools::IsThirtyDaysExpired( (pSubscriber->mCallsVec[index]->GetTimeCallStart()),pSubscriber->GetLastCreditDate() );
}

bool  Accounting::IsWeekend(Subscriber* pSubscriber, int index )
{
	return TimeTools::IsWeekend(pSubscriber->mCallsVec[index]->GetTimeCallStart() );
}

bool Accounting::IsHomeNetwork(Subscriber* pSubscriber, int index, const std::string& prefix) 
{
	bool isHomeNetwork =
		((pSubscriber->mCallsVec[index]->GetCalledNumber()).substr(0,3).find(prefix.substr(0,3))!=-1)||
		((pSubscriber->mCallsVec[index]->GetCalledNumber()).substr(0,3).find(prefix.substr(3,3))!=-1)||
		((pSubscriber->mCallsVec[index]->GetCalledNumber()).substr(0,3).find(prefix.substr(6,3))!=-1)||
		((pSubscriber->mCallsVec[index]->GetCalledNumber()).substr(0,3).find(prefix.substr(9,3))!=-1);
	return isHomeNetwork;
}

void Accounting::LoadingFromFile(const std::string fileName)
{
	std::ifstream myFile (fileName.c_str());

	
	if (myFile.is_open())
	{
		while ( myFile.good() )
		{
			std::string line;
	std::string strData1, strData2, strData3, strData4;
	std::stringstream parsedData;

			getline (myFile,line);
			parsedData<<line;
			getline(parsedData, strData1, ';' );
			getline(parsedData, strData2, ';' );
			getline(parsedData, strData3, ';' );
			getline(parsedData, strData4, ';' );	
			if(fileName.find("Subscribers.dat")!=-1)
			{
				AttachSubscriber(new Subscriber (strData1, strData2, strData3, strData4));
			}
			if(fileName.find("PhoneCalls.dat")!=-1)
			{
				AttachPhoneCall (new PhoneCall  (strData1, strData2, strData3, strData4));
			}
		}
		myFile.close();
	}
	else std::cout << "Unable to open file";
}

Accounting::~Accounting()
{
	typedef std::vector< Subscriber* >::iterator subscriberIter;
	typedef std::vector< PhoneCall* >::iterator  phoneCallIter;
	for( phoneCallIter callIter = mCallsVec.begin(); callIter != mCallsVec.end(); ++callIter )
	{
		delete(*callIter);
	}
	for( subscriberIter subIter = mSubscribersVec.begin(); subIter != mSubscribersVec.end(); ++subIter )
	{
		delete (*subIter);
	}
	mCallsVec.clear();
	mSubscribersVec.clear();
}