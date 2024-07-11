#include <bits/stdc++.h>
using namespace std;

int number_of_submission = 0;

struct Submission
{
    string user_id, problem_id, status;
    int time, point;
};

int timeStringToInt(const string &time)
{
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    int second = stoi(time.substr(6, 2));
    return hour * 3600 + minute * 60 + second;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    map<int, vector<Submission>> submissions;

    int point;
    string user_id, problem_id, status, time, line;
    while (cin >> user_id && user_id != "#")
    {
        cin >> problem_id >> time >> status >> point;
        int time_int = timeStringToInt(time);
        Submission submission = {user_id, problem_id, status, time_int, point};
        submissions[time_int].push_back(submission);
        ++number_of_submission;
    }

    while (cin >> line && line != "#")
    {
        if (line == "?total_number_submissions")
        {
            cout << number_of_submission << "\n";
        }
        else if (line == "?number_error_submision")
        {
            int count = 0;
            for (const auto &submission : submissions)
            {
                for (const auto &s : submission.second)
                {
                    if (s.status == "ERR")
                        ++count;
                }
            }
            cout << count << "\n";
        }
        else if (line == "?number_error_submision_of_user")
        {
            string user;
            cin >> user;
            int count = 0;
            for (const auto &submission : submissions)
            {
                for (const auto &s : submission.second)
                {
                    if (s.status == "ERR" && s.user_id == user)
                        ++count;
                }
            }
            cout << count << "\n";
        }
        else if (line == "?total_point_of_user")
        {
            string user;
            cin >> user;
            int point = 0;
            unordered_map<string, int> maxPointsForProblem;
            for (const auto &submission : submissions)
            {
                for (const auto &s : submission.second)
                {
                    if (s.user_id == user)
                    {
                        if (s.status == "ERR")
                            continue;
                        string pid = s.problem_id;
                        if (maxPointsForProblem.find(pid) == maxPointsForProblem.end() ||
                            s.point > maxPointsForProblem[pid])
                        {
                            maxPointsForProblem[pid] = s.point;
                        }
                    }
                }
            }
            for (const auto &p : maxPointsForProblem)
                point += p.second;
            cout << point << "\n";
        }
        else if (line == "?number_submission_period")
        {
            string start_time, end_time;
            cin >> start_time >> end_time;
            int start_time_int = timeStringToInt(start_time);
            int end_time_int = timeStringToInt(end_time);
            int count = 0;
            for (auto it = submissions.lower_bound(start_time_int); it != submissions.upper_bound(end_time_int); ++it)
                count += it->second.size();
            cout << count << "\n";
        }
    }

    return 0;
}