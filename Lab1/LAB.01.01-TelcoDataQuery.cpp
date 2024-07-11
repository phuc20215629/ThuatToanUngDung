//C++ 
#include <bits/stdc++.h>
using namespace std;

map<string, pair<int, int>> call_from;

bool check_phone_num(const string& num) {
    if (num.length() != 10)
        return false;
    for (char c : num) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int toSec(string time) {
    int h = stoi(time.substr(0,2));
    int m = stoi(time.substr(3,2));
    int s = stoi(time.substr(6,2));
    return h * 3600 + m * 60 + s;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string fromNum, toNum;
    int fromH, fromM, fromS, toH, toM, toS;
    int checkPhoneNum = 1;

    while (true) {
        string tmp, fromTime, toTime;
        cin >> tmp;
        if (tmp == "#") break;
        cin >> fromNum >> toNum >> tmp >> fromTime >> toTime;
       
        if (check_phone_num(fromNum) && check_phone_num(toNum)) {
            int timeCalled = toSec(toTime) - toSec(fromTime);
            call_from[fromNum].first++;
            call_from[fromNum].second += timeCalled;    
        } else {
            checkPhoneNum = 0;
        }
    }
    while (true) {
        string order;
        cin >> order;
        if(order == "#") break;
        
        if(order == "?check_phone_number") {
            cout << checkPhoneNum << "\n";
        }
        if(order == "?number_calls_from") {
            string phone;
            cin >> phone;
            cout << call_from[phone].first <<  "\n";
        }
        if(order == "?number_total_calls") {
            int total = 0;
            for(auto call : call_from) total += call.second.first;
            cout << total << "\n";
        }
        if(order == "?count_time_calls_from") {
            string phone;
            cin >> phone;
            cout << call_from[phone].second << "\n";
        }
    }
    return 0;
}