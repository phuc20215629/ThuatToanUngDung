/*
Description
Data about submission of a programming contest consists a sequence of lines, each line has the following information:
                                                      <UserID> <ProblemID> <TimePoint> <Status> <Point>
in which the user <UserID> submits his/her code to solve the problem <ProblemID> at time-point <TimePoint>, and gets status <Status> and point <Point>
<UserID>: string of length from 3 to 10
<ProblemID>: string under the format Pxy where x, y are digits 0,1,...,9 (for example P03, P10)
<TimePoint>: string representing time-point with the format HH:MM:SS (for example, 09:45:20 means the time-point 9 hour 45 minutes 20 seconds)
<Status>: string with two cases (ERR, OK)
<Point>: integer from {0, 1, 2, ..., 10}

A user can submit the code for solving each problem several time. The point that the user gets for a problem is the maximal point among the submissions for that problem.

Perform a sequence of queries of following types:
?total_number_submissions: return the number of submissions of the contest
?number_error_submission: return the number of submissions having status ERR
?number_error_submission_of_user <UserID>: return the number of submission having status ERR of user <UserID>
?total_point_of_user <UserID>: return the total point of user <UserID>
?number_submission_period <from_time_point> <to_time_point>: return the number of submissions in the period from <from_time_point> to <to_time_point> (inclusive)

Input
The input consists of two blocks of data:
The first block is the operational data, which is a sequence of lines (number of lines can be up to 100000), each line contains the information of a submission with above format .The first block is terminated with a line containing the character #
The second block is the query block, which is a sequence of lines (number of lines can be up to 100000), each line is a query described above. The second block is terminated with a line containing the character #

Output
Write in each line, the result of the corresponding query

Example
Input
U001 P01 10:30:20 ERR 0
U001 P01 10:35:20 OK 10
U001 P02 10:40:20 ERR 0
U001 P02 10:55:20 OK 7
U002 P01 10:40:20 ERR 0
U001 P01 11:35:20 OK 8
U002 P02 10:40:20 OK 10
#
?total_number_submissions
?number_error_submision
?number_error_submision_of_user U002
?total_point_of_user U001
?number_submission_period 10:00:00 11:30:45
#


Output
7
3
1
17
6
*/

#include <bits/stdc++.h>
using namespace std;

int total_number_submissions = 0;
int number_error_submission = 0;
unordered_map<string, int> number_error_submission_of_user;
unordered_map<string, unordered_map<string, int>> total_point_of_user_per_problem;
unordered_map<string, int> total_point_of_user;
map<string, int> number_submission_period;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string UserID, ProblemID, TimePoint, Status;
    int Point;

    while (1)
    {
        cin >> UserID;
        if (UserID == "#")
            break;
        cin >> ProblemID >> TimePoint >> Status >> Point;

        total_number_submissions++;
        number_submission_period[TimePoint]++;

        if (Status == "ERR")
        {
            number_error_submission_of_user[UserID]++;
            number_error_submission++;
        }
        else
        {
            if (total_point_of_user_per_problem[UserID][ProblemID] < Point)
            {
                total_point_of_user[UserID] += Point - total_point_of_user_per_problem[UserID][ProblemID];
                total_point_of_user_per_problem[UserID][ProblemID] = Point;
            }
        }
    }

    number_submission_period["00:00:00"] = 0;
    number_submission_period["24:00:00"] = 0;
    int pre = 0;
    for (auto &period : number_submission_period)
    {
        pre = period.second += pre;
    }

    string order;
    while (1)
    {
        cin >> order;
        if (order == "#")
            break;
        else if (order == "?total_number_submissions")
            cout << total_number_submissions << endl;
        else if (order == "?number_error_submision")
            cout << number_error_submission << endl;
        else if (order == "?number_error_submision_of_user")
        {
            string userID;
            cin >> userID;
            cout << number_error_submission_of_user[userID] << endl;
        }
        else if (order == "?total_point_of_user")
        {
            string userID;
            cin >> userID;

            cout << total_point_of_user[userID] << endl;
        }
        else if (order == "?number_submission_period")
        {
            string fromTime, toTime;
            cin >> fromTime >> toTime;

            auto itFromTime = number_submission_period.lower_bound(fromTime);
            auto itToTime = number_submission_period.upper_bound(toTime);
            cout << (--itToTime)->second - (--itFromTime)->second << endl;
        }
    }
    return 0;
}
