#include<time.h>
#include<stdio.h>
#include "time_conv.h"
#include "app_defs.h"

//A function that converts EPOCH from 1970 standard to ITC and UTC
void EPOCH1970ToNormal(time_t *tm, char *timestamp_op, char *UTC_time, char *IST_time)
{
	struct tm ts, ts1;
	
	//Getting the localzone time
	ts = *localtime(tm);
	//Getting the UTC time
	ts1 = *gmtime(tm);

	//Formating the output timestamps
	strftime(IST_time, 100, "%a %Y-%m-%d %H:%M:%S \n %d/%m/%Y %H:%M:%S", &ts);
	strftime(UTC_time, 100, "%a %Y-%m-%d %H:%M:%S \n %d/%m/%Y %H:%M:%S", &ts1);
	snprintf(timestamp_op, 200, "%s %s\n\n%s %s\n", IST_time, "[IST]", UTC_time, "[UTC]");
	snprintf(IST_time,100,"%s %s", IST_time, "IST");
	snprintf(UTC_time, 100, "%s %s", UTC_time, "UTC");


}

//A function that converts EPOCH from 1980 standard to ITC and UTC
void EPOCH1980ToNormal(time_t *tm, char *timestamp_op, char *UTC_time, char *IST_time)
{
	// Adding offset seconds to input EPOCH to compensate the addition of 10 years
	(*tm) += TIME_OFFSET_SECONDS;

	struct tm ts, ts1;

	//Getting the localzone time
	ts = *localtime(tm);
	//Getting the UTC time
	ts1 = *gmtime(tm);

	//Formating the output timestamps
	strftime(IST_time, 100, "%a %Y-%m-%d %H:%M:%S \n %d/%m/%Y %H:%M:%S", &ts);
	strftime(UTC_time, 100, "%a %Y-%m-%d %H:%M:%S \n %d/%m/%Y %H:%M:%S", &ts1);
	snprintf(timestamp_op, 200, "%s %s\n\n%s %s\n", IST_time, "[IST]", UTC_time, "[UTC]");
	snprintf(IST_time, 100, "%s %s", IST_time, "IST");
	snprintf(UTC_time, 100, "%s %s", UTC_time, "UTC");

}