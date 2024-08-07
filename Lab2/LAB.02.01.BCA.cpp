#include <bits/stdc++.h>
using namespace std;

/*
At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way.
The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}.
Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization.
We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher
as these courses have been already scheduled in the same slot of the timetable.
The load of a teacher is the number of courses assigned to her/him.
How to assign nn courses to  teacher such that each course assigned to a teacher is in his/her preference list,
no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
*/

int m, n, sol = INT_MAX;
vector<vector<bool>> confCourse;
vector<vector<int>> prefList;
vector<int> load;
vector<int> teacher_for_course;

bool check(int course, int teacher)
{
    // find course k in teacher's i prefList
    bool found = false;
    for (auto x : prefList[teacher])
    {
        if (course == x)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        for (int i = 1; i < course; i++)
        {
            // if appears conflict
            if (teacher == teacher_for_course[i] && (confCourse[course][i] || confCourse[i][course]))
            {
                return false;
            }
        }
        return true;
    }
    // if course is not found in the prefList[teacher]
    return false;
}

void tryCourse(int k)
{
    if (k == n + 1) // if all courses have been assigned
    {
        int maxLoad = INT_MIN;
        for (auto l : load)
        {
            maxLoad = max(maxLoad, l);
        }
        sol = min(sol, maxLoad);
        return;
    }

    for (int i = 1; i <= m; i++)
    {
        if (check(k, i))
        {
            load[i]++; // add course k to teacher's i load
            teacher_for_course[k] = i;

            if (load[i] < sol) // lower bound to reduce unnecessary cases
                tryCourse(k + 1);

            teacher_for_course[k] = 0;
            load[i]--;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n;
    prefList.resize(m + 1);
    load.resize(m + 1);
    teacher_for_course.resize(n + 1);

    int k;
    for (int i = 1; i <= m; i++)
    {
        cin >> k;
        prefList[i].resize(k, 0);
        for (int j = 0; j < k; j++)
        {
            cin >> prefList[i][j];
        }
    }
    cin >> k;
    confCourse.resize(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < k; i++)
    {
        int a, b;
        cin >> a >> b;
        confCourse[a][b] = true;
    }

    tryCourse(1);
    if (sol == INT_MAX)
        sol = -1;
    cout << sol << endl;
    return 0;
}
