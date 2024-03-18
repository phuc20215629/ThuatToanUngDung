#include<bits/stdc++.h>
using namespace std;

int m, n, sol = INT_MAX;
vector<vector<bool>> confCourse;
vector<vector<int>> prefList;
vector<int> load;
vector<int> teacher_for_course;

bool check(int course, int teacher) {
    //find course k in teacher's i prefList
    bool found = false;
    for (auto x : prefList[teacher]) {
        if (course == x) {
            found = true;
            break;
        }
    }
    if (found) {
        for (int i = 1; i <= m; i++) {
            //if appears conflict
            if (teacher == teacher_for_course[i] && (confCourse[course][i] || confCourse[i][course])) {
                return false;
            }
        }
        return true;
    }
    //if course is not found in the prefList[teacher]
    return false;
}

void tryCourse(int k) {
    for (int i = 1; i <= m; i++) {
        if (check(k, i)) {
            load[i]++; //add course k to teacher's i load
            teacher_for_course[k] = i;
            if (k == n) {
                int maxLoad = INT_MIN;
                for (auto l : load) {
                    maxLoad = max(maxLoad, l);
                }
                sol = min(sol, maxLoad);
            } else {
                if(load[i] < sol) tryCourse(k + 1);
            }
            teacher_for_course[k] = 0;
            load[i]--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> m >> n;
    prefList.resize(50);
    load.resize(50);
    teacher_for_course.resize(50);

    int k;
    for (int i = 1; i <= m; i++) {
        cin >> k;
        prefList[i].resize(50, 0);
        for (int j = 1; j <= k; j++) {
            cin >> prefList[i][j];
        }
    }
    cin >> k;
    confCourse.resize(50, vector<bool>(50, false));
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        confCourse[a][b] = true;
    }

    tryCourse(1);
    cout << sol << endl;
    return 0;
}