#include <bits/stdc++.h>
using namespace std;

int number_of_orders = 0;
int number_orders_in_period = 0;
int number_orders_at_time = 0;

struct Order
{
    string id;
    int time;
};

int timeStringToInt(const string &time)
{
    string timeStr = time.substr(0, 2) + time.substr(3, 2) + time.substr(6, 2);
    return stoi(timeStr);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    map<int, vector<string>> orders;

    string id, time, line;
    cin >> id;
    while (id != "#")
    {
        cin >> time;
        int time_int = timeStringToInt(time);
        orders[time_int].push_back(id);
        ++number_of_orders;
        cin >> id;
    }

    cin >> line;
    while (line != "###")
    {
        if (line == "?number_orders")
        {
            cout << number_of_orders << endl;
        }
        else if (line == "?number_orders_in_period")
        {
            string start_time, end_time;
            cin >> start_time >> end_time;
            int start_time_int = timeStringToInt(start_time);
            int end_time_int = timeStringToInt(end_time);
            int count = 0;
            for (auto it = orders.lower_bound(start_time_int); it != orders.upper_bound(end_time_int); ++it)
            {
                count += it->second.size();
            }
            cout << count << endl;
        }
        else if (line == "?number_orders_at_time")
        {
            string time;
            cin >> time;
            int time_int = timeStringToInt(time);
            auto it = orders.find(time_int);
            if (it != orders.end())
            {
                cout << it->second.size() << "\n";
            }
            else
                cout << 0 << "\n";
        }
        cin >> line;
    }

    return 0;
}
