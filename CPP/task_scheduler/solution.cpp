#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define  INVALID_VAL    -1
#define  BASE_YEAR      1900
#define  DAYS_IN_A_WEEK 7


/* CLASS PARSER */
class Parser
{
    void convertStrToLower(string& str);
    int convertMonthToInt(string month);
    int convertDayOfTheWeekToInt(string day);
    tm getCurrentTime();

public:
    tm parseDateTime(string dateTime);
    tm parseTime(string time);
    set<int> parseDays(string days);
};

void Parser::convertStrToLower(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int Parser::convertMonthToInt(string month)
{
    convertStrToLower(month);

    vector<string> months = \
        {"january", "february", "march", "april", "may", "june", \
        "july", "august", "september", "october", "november", "december"};

    auto itr = find(months.begin(), months.end(), month);
    if (itr != months.end())
    {
        return itr - months.begin();
    }

    return INVALID_VAL;
}

int Parser::convertDayOfTheWeekToInt(string day)
{
    convertStrToLower(day);

    vector<string> daysOfTheWeek = {"sunday", "monday", "tuesday", \
        "wednesday", "thursday", "friday", "saturday", "sunday"};

    auto itr = find(daysOfTheWeek.begin(), daysOfTheWeek.end(), day);
    if (itr != daysOfTheWeek.end())
    {
        return itr - daysOfTheWeek.begin();
    }

    return INVALID_VAL;
}

tm Parser::getCurrentTime()
{
    time_t currentTime = time(0);
    tm timeinfo;

    localtime_s(&timeinfo, &currentTime);
    return timeinfo;
}

tm Parser::parseTime(string timeInput)
{
    tm parsedTime;
    memset(&parsedTime, 0, sizeof(parsedTime));
    parsedTime = getCurrentTime();

    /* Parse hours */
    std::size_t itr = timeInput.find(':');
    parsedTime.tm_hour = std::stoi(timeInput.substr(0, itr));
    timeInput.erase(0, itr + 1);

    /* Parse minutes */
    itr = timeInput.find(' ');
    parsedTime.tm_min = std::stoi(timeInput.substr(0, itr));
    timeInput.erase(0, itr + 1);

    /* Parse period */
    if (0 == timeInput.compare("PM"))
    {
        parsedTime.tm_hour += 12;
    }

    return parsedTime;
}

tm Parser::parseDateTime(string dateTime)
{
    int monthNum;
    tm parsedDateTime, parsedTime;
    memset(&parsedDateTime, 0, sizeof(parsedDateTime));
    memset(&parsedTime, 0, sizeof(parsedTime));

    /* Parse Month */
    std::size_t itr = dateTime.find(' ');
    monthNum = convertMonthToInt(dateTime.substr(0, itr));
    if (INVALID_VAL == monthNum)
    {
        cout << "Invalid month input" << endl;
        return parsedDateTime;
    }
    parsedDateTime.tm_mon = monthNum;
    dateTime.erase(0, itr + 1);

    /* Parse Day */
    itr = dateTime.find(',');
    parsedDateTime.tm_mday = std::stoi(dateTime.substr(0, itr));
    dateTime.erase(0, itr + 2);

    /* Parse Year */
    itr = dateTime.find(' ');
    parsedDateTime.tm_year = std::stoi(dateTime.substr(0, itr)) - BASE_YEAR;
    dateTime.erase(0, itr + 1);

    /* Parse Time */
    parsedTime = parseTime(dateTime);
    parsedDateTime.tm_hour = parsedTime.tm_hour;
    parsedDateTime.tm_min = parsedTime.tm_min;

    return parsedDateTime;
}

set<int> Parser::parseDays(string days)
{
    set<int> listOfDays;
    int dayNum = INVALID_VAL;
    std::size_t itrSpace = days.find(' ');
    std::size_t itrComma = days.find(',');

    while ((itrComma != string::npos) || (itrSpace != string::npos))
    {
        if(itrComma < itrSpace)
        {
            dayNum = convertDayOfTheWeekToInt(days.substr(0, itrComma));
            days.erase(0, itrComma + 2);
        }
        else
        {
            dayNum = convertDayOfTheWeekToInt(days.substr(0, itrSpace));
            days.erase(0, itrSpace + 1);
        }

        if (INVALID_VAL != dayNum)
        {
            listOfDays.insert(dayNum);
        }

        itrSpace = days.find(' ');
        itrComma = days.find(',');
    }

    /* Parse last day in the string */
    dayNum = convertDayOfTheWeekToInt(days);
    if (INVALID_VAL != dayNum)
    {
        listOfDays.insert(dayNum);
    }

    return listOfDays;
}


/* CLASS SCHEDULE */
class Schedule
{
public:
    set<int> days;
    tm time;
    tm startDate;
};


/* CLASS TASK_SCHEDULER */
class TaskScheduler
{
    vector<Schedule*> listOfSched;

    tm getPrevSched(tm& inputDate, Schedule* sched);
    tm getNextSched(tm& inputDate, Schedule* sched);
    void printDate(tm& date);
    void printResult(tm& prevSched, string& isScheduled, tm& nextSched);
    
public:
    void AddSchedule(string days, string time, string startDateTime);
    void QueryDateTime(string startDateTime);
    ~TaskScheduler();
};

TaskScheduler::~TaskScheduler()
{
    for (auto itr = listOfSched.rbegin(); itr != listOfSched.rend(); ++itr)
    {
        delete *itr;
    }
}

tm TaskScheduler::getNextSched(tm& inputDate, Schedule* sched)
{
    tm nextSched = inputDate;
    int addDay = 0;

    auto itr = sched->days.begin();
    for ( ;itr != sched->days.end(); ++itr)
    {
        if (*itr > inputDate.tm_wday)
        {
            addDay = (*itr) - inputDate.tm_wday;
            break;
        }
        else if (*itr == inputDate.tm_wday)
        {
            if ( (inputDate.tm_hour < sched->time.tm_hour) || //
                ((inputDate.tm_hour == sched->time.tm_hour) && (inputDate.tm_min < sched->time.tm_min)) )
            {
                    addDay = 0;
                    break;
            }
        }
    }

    if (itr == sched->days.end())
    {
        addDay = DAYS_IN_A_WEEK - inputDate.tm_wday + *sched->days.begin();
    }

    nextSched.tm_mday += addDay;
    nextSched.tm_hour = sched->time.tm_hour;
    nextSched.tm_min = sched->time.tm_min;

    return nextSched;
}

tm TaskScheduler::getPrevSched(tm& inputDate, Schedule* sched)
{
    tm prevSched = inputDate;
    int dayDiff = 0;

    auto itr = sched->days.rbegin();
    for (; itr != sched->days.rend(); ++itr)
    {
        if (*itr < inputDate.tm_wday)
        {
            dayDiff = inputDate.tm_wday - *itr;
            break;
        }
        else if(*itr == inputDate.tm_wday)
        {
            if ( (inputDate.tm_hour > sched->time.tm_hour) || //
                ((inputDate.tm_hour == sched->time.tm_hour) && (inputDate.tm_min > sched->time.tm_min)) )
            {
                    dayDiff = 0;
                    break;
            }
        }
    }

    if (itr == sched->days.rend())
    {
        dayDiff = DAYS_IN_A_WEEK - *sched->days.rbegin() + inputDate.tm_wday;
    }

    prevSched.tm_mday -= dayDiff;
    prevSched.tm_hour = sched->time.tm_hour;
    prevSched.tm_min = sched->time.tm_min;

    return prevSched;
}

void TaskScheduler::AddSchedule(string days, string time, string startDateTime)
{
    Parser *schedParser = new Parser;
    Schedule* newSched = new Schedule;

    newSched->days = schedParser->parseDays(days);
    newSched->time = schedParser->parseTime(time);
    newSched->startDate = schedParser->parseDateTime(startDateTime);

    listOfSched.push_back(newSched);
    delete schedParser;

    cout << "Schedule successfully added" << endl;
};

void TaskScheduler::printDate(tm& date)
{
    char buffer[80];
    strftime(buffer, 80, "%e %b %Y - %H:%M", &date);
    cout << buffer << endl;
}

void TaskScheduler::printResult(tm& prevSched, string& isScheduled, tm& nextSched)
{
    /* Print previous schedule */
    if (INVALID_VAL == mktime(&prevSched))
    {
        cout << "Previous schedule: NONE" << endl;
    }
    else
    {
        cout << "Previous schedule: ";
        printDate(prevSched);
    }

    /* Print isScheduled */
    cout << "Is scheduled now: " << isScheduled << endl;

    /* Print next schedule */
    if (INVALID_VAL == mktime(&nextSched))
    {
        cout << "Next schedule: NONE" << endl;
    }
    else
    {
        cout << "Next schedule: ";
        printDate(nextSched);
        cout << endl;
    }
}

void TaskScheduler::QueryDateTime(string startDateStr)
{
    cout << "<< QUERY DATE TIME >>" << endl << endl;
    Parser* schedParser = new Parser;

    tm prevSched;
    string isScheduled = "NO";
    tm nextSched;
    
    tm startDate = schedParser->parseDateTime(startDateStr);

    memset(&prevSched, 0, sizeof(prevSched));
    memset(&nextSched, 0, sizeof(nextSched));

    for (auto itr = listOfSched.begin(); itr != listOfSched.end(); ++itr)
    {
        cout << "Checking SCHEDULE #" << itr - listOfSched.begin() << "..." << endl;
        if (0 == difftime(mktime(&(*itr)->startDate), mktime(&startDate)))
        {
            /* Input is equal to start date */
            isScheduled = "YES";
            nextSched = getNextSched(startDate, (*itr));
        }
        else if (0 > difftime(mktime(&(*itr)->startDate), mktime(&startDate)))
        {
            /* Event started */
            //getPrevSched
            prevSched = getPrevSched(startDate, (*itr));

            // Check if isScheduled
            if ( (startDate.tm_hour == (*itr)->time.tm_hour) && (startDate.tm_min == (*itr)->time.tm_min) )
            {
                for (auto itrSched = (*itr)->days.begin(); itrSched != (*itr)->days.end(); ++itrSched)
                {
                    if (startDate.tm_wday == *itrSched)
                    {
                        isScheduled = "YES";
                    }
                }
            }

            //getNextSched
            nextSched = getNextSched(startDate, (*itr));
        }
        else
        {
            /* Event not yet started */
            nextSched = (*itr)->startDate;
        }

        printResult(prevSched, isScheduled, nextSched);

        /* Reset values */
        memset(&prevSched, 0, sizeof(prevSched));
        memset(&nextSched, 0, sizeof(nextSched));
        isScheduled = "NO";
    }

    delete schedParser;
}


int main()
{
    TaskScheduler* myScheduler = new TaskScheduler;

    /* TESTCASE#1 : Given test case */
    myScheduler->AddSchedule("Monday, Wednesday, and Friday", "9:00 AM", "June 22, 2020 9:00 PM");
    myScheduler->QueryDateTime("June 21, 2020 9:00 AM");

    /* TESTCASE#2 : Event2 not yet started */
    myScheduler->AddSchedule("Friday, Monday, and Sunday", "9:30 AM", "November 25, 2020 4:44 PM");
    myScheduler->QueryDateTime("November 09, 2020 9:00 AM");

    /* TESTCASE#3 : Event2 not yet started but same day as input  */
    myScheduler->QueryDateTime("November 25, 2020 4:04 AM");

    /* TESTCASE#4 : Input date same as event2 start date  */
    myScheduler->QueryDateTime("November 25, 2020 4:44 PM");

    /* TESTCASE#4 : Event has started already  */
    myScheduler->QueryDateTime("December 30, 2020 8:10 AM");

    delete myScheduler;
}