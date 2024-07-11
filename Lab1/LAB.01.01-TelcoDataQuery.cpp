// C++
#include <bits/stdc++.h>
using namespace std;

/*
Write a C program to perform some queries on a telco data (comming from stdin) with the following format:
The first block of data consists of lines (terminated by a line containing #), each line (number of lines can be up to 100000) is under the form:
        call <from_number> <to_number> <date> <from_time> <end_time>
which is a call from the phone number <from_number> to a phone number <to_number> on <date>, and starting at time-point <from_time>, terminating at time-point <end_time>
<from_number> and <to_number> are string of 10 characters (a phone number is correct if it contains only digits 0,1,...,9, otherwise, the phone number is incorrect)
<date> is under the form YYYY-MM-DD (for example 2022-10-21)
<from_time> and <to_time> are under the form hh:mm:ss (for example, 10:07:23)

The second block consists of queries (terminated by a line containing #), each query in a line (number of lines can be up to 100000) and belongs to one of the following types:
?check_phone_number: print to stdout (in a new line) value 1 if no phone number is incorrect
?number_calls_from <phone_number>: print to stdout (in a new line) the number of times a call is made from <phone_number>
?number_total_calls: print to stdout (in a new line) the total number of calls of the data
?count_time_calls_from <phone_number>: print to stdout (in a new line) the total time duration (in seconds) the calls are made from <phone_number>
*/

map<string, pair<int, int>> call_from;

bool check_phone_num(const string &num)
{
    if (num.length() != 10)
        return false;
    for (char c : num)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int toSec(string time)
{
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    int s = stoi(time.substr(6, 2));
    return h * 3600 + m * 60 + s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string fromNum, toNum;
    int fromH, fromM, fromS, toH, toM, toS;
    int checkPhoneNum = 1;

    while (true)
    {
        string tmp, fromTime, toTime;
        cin >> tmp;
        if (tmp == "#")
            break;
        cin >> fromNum >> toNum >> tmp >> fromTime >> toTime;

        if (check_phone_num(fromNum) && check_phone_num(toNum))
        {
            int timeCalled = toSec(toTime) - toSec(fromTime);
            call_from[fromNum].first++;
            call_from[fromNum].second += timeCalled;
        }
        else
        {
            checkPhoneNum = 0;
        }
    }
    while (true)
    {
        string order;
        cin >> order;
        if (order == "#")
            break;

        if (order == "?check_phone_number")
        {
            cout << checkPhoneNum << "\n";
        }
        if (order == "?number_calls_from")
        {
            string phone;
            cin >> phone;
            cout << call_from[phone].first << "\n";
        }
        if (order == "?number_total_calls")
        {
            int total = 0;
            for (auto call : call_from)
                total += call.second.first;
            cout << total << "\n";
        }
        if (order == "?count_time_calls_from")
        {
            string phone;
            cin >> phone;
            cout << call_from[phone].second << "\n";
        }
    }
    return 0;
}