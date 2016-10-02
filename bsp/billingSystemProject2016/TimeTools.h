#include<iostream>
#include<sstream>
#include<ctime>

static const int SecInDay = 86400;

class TimeTools
{
public:

	static time_t GetTimeFromString(const std::string strTime)
	{
		std::string day_time, mon_time, year_time, hr_time, min_time, sec_time;
		int timein_dy, timein_mt, timein_yr, timein_hr, timein_min, timein_sec;
		std::stringstream parsedtime;
		std::time_t nowTime=time(0);
		tm *info = gmtime (&nowTime);
		parsedtime<<strTime;

		getline(parsedtime, day_time, ':' );
		getline(parsedtime, mon_time, ':' );
		getline(parsedtime, year_time,':' );
		getline(parsedtime, hr_time,  ':' );
		getline(parsedtime, min_time, ':' );
		getline(parsedtime, sec_time, ':' );

		timein_dy=atoi(day_time.c_str());
		timein_mt=atoi(mon_time.c_str());
		timein_yr=atoi(year_time.c_str());
		timein_hr=atoi(hr_time.c_str());
		timein_min=atoi(min_time.c_str());
		timein_sec=atoi(sec_time.c_str());

		info->tm_mday=timein_dy;
		info->tm_mon=timein_mt -1;
		info->tm_year = timein_yr - 1900;
		info->tm_hour=timein_hr;
		info->tm_min=timein_min;
		info->tm_sec=timein_sec;

		parsedtime.clear();
		return mktime(info);
	}
	static float const GetTimeDifferenceInMinutes(const std::string first, const std::string second)
	{  
		time_t firstTime  = GetTimeFromString(first);
		time_t secondTime = GetTimeFromString(second);
		std::time_t diff = firstTime - secondTime  ;

		if(diff < 0)
		{
			diff *= -1;
		}
		float timeInMinutes = diff/60.0f;
		return timeInMinutes;
	}
	static bool IsThirtyDaysExpired(const std::string first, const std::string second)
	{  
		time_t firstTime  = GetTimeFromString(first);
		time_t secondTime = GetTimeFromString(second);
		std::time_t diff =firstTime - secondTime  ;
        int SecInThirtyDays = SecInDay*30;
		bool ThirtyDaysExpired =  diff > SecInThirtyDays;
		return ThirtyDaysExpired;
	}
	static bool IsWeekend(const std::string first)
	{  
		time_t firstTime  = GetTimeFromString(first);
		struct tm * timeinfo;
		timeinfo = gmtime ( &firstTime );
		return (timeinfo->tm_wday == 0);
	}
};