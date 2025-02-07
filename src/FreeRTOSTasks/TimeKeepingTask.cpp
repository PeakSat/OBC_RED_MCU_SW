#include "TimeKeepingTask.hpp"

void TimeKeepingTask::execute() {
    LOG_DEBUG << "Runtime init: " << this->TaskName;
    static tm dateTime;
    setEpoch(dateTime);
    RTC_TimeSet(&dateTime);

    while (true) {
//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        RTC_TimeGet(&dateTime);
        setTimePlatformParameters(dateTime);
        printOnBoardTime();
//        LOG_DEBUG << "Runtime exit: " << this->TaskName;
        vTaskDelay(pdMS_TO_TICKS(DelayMs));
        
    }
}

void TimeKeepingTask::printOnBoardTime() {
    UTCTimestamp timestamp = CommonParameters::time.getValue().toUTCtimestamp();
    etl::string<29> printTime = "Time:";
    etl::to_string(timestamp.hour, printTime, true);
    printTime += "-";
    etl::to_string(timestamp.minute, printTime, true);
    printTime += "-";
    etl::to_string(timestamp.second, printTime, true);
    printTime += " -- ";
    etl::to_string(timestamp.day, printTime, true);
    printTime += "/";
    etl::to_string(timestamp.month, printTime, true);
    printTime += "/";
    etl::to_string(timestamp.year, printTime, true);
    LOG_DEBUG << printTime.data();
}

void TimeKeepingTask::setTimePlatformParameters(tm &dateTime) {
    UTCTimestamp timeUTC(dateTime.tm_year + yearBase, dateTime.tm_mon + 1, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec);
    Time::DefaultCUC timeCUC(timeUTC);
    CommonParameters::time.setValue(timeCUC);
}

void TimeKeepingTask::setEpoch(tm &dateTime) {
    dateTime.tm_sec = EpochTime.tm_sec;
    dateTime.tm_min = EpochTime.tm_min;
    dateTime.tm_hour = EpochTime.tm_hour;
    dateTime.tm_mday = EpochTime.tm_mday;
    dateTime.tm_mon = EpochTime.tm_mon;
    dateTime.tm_year = EpochTime.tm_year - yearBase;
}
