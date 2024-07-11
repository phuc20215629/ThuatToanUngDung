#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

struct Segment
{
    string id;
    string point1;
    string point2;
};

unordered_map<string, Point> points;
unordered_map<string, vector<string>> graph;
unordered_set<string> visited;

int getNumberConnectedComponents()
{
    int components = 0;

    for (const auto &point : points)
    {
        if (visited.count(point.first) == 0)
        {
            components++;
            queue<string> q;
            q.push(point.first);
            visited.insert(point.first);

            while (!q.empty())
            {
                string curr = q.front();
                q.pop();

                for (const auto &neighbor : graph[curr])
                {
                    if (visited.count(neighbor) == 0)
                    {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                }
            }
        }
    }

    return components;
}

void dfs(const string &curr, const string &startPoint, int cycleSize, unordered_set<string> &currentPath, int &maxCycle)
{
    visited.insert(curr);
    currentPath.insert(curr);

    for (const auto &neighbor : graph[curr])
    {
        if (neighbor == startPoint && cycleSize >= 2)
        {
            maxCycle = max(maxCycle, cycleSize + 1);
            continue;
        }

        if (currentPath.count(neighbor) == 0)
        {
            dfs(neighbor, startPoint, cycleSize + 1, currentPath, maxCycle);
        }
    }

    currentPath.erase(curr);
}

int getLongestCycleFrom(const string &startPoint)
{
    int maxCycle = 0;
    visited.clear();
    unordered_set<string> currentPath;

    dfs(startPoint, startPoint, 0, currentPath, maxCycle);

    return maxCycle;
}

int main()
{
    string line;
    int number_points = 0, number_segments = 0;
    while (getline(cin, line) && line != "#")
    {
        string id, xStr, yStr;
        int x, y;
        istringstream iss(line);
        iss >> id >> xStr >> yStr;
        x = stoi(xStr);
        y = stoi(yStr);
        points[id] = {x, y};
        number_points++;
    }

    while (getline(cin, line) && line != "#")
    {
        string id, point1, point2;
        istringstream iss(line);
        iss >> id >> point1 >> point2;
        graph[point1].push_back(point2);
        graph[point2].push_back(point1);
        number_segments++;
    }

    while (getline(cin, line) && line != "###")
    {
        if (line == "?number_points")
        {
            cout << number_points << endl;
        }
        else if (line == "?number_segments")
        {
            cout << number_segments << endl;
        }
        else if (line == "?connected_components")
        {
            cout << getNumberConnectedComponents() << endl;
        }
        else if (line.substr(0, 19) == "?longest_cycle_from")
        {
            string startPoint = line.substr(20);
            cout << getLongestCycleFrom(startPoint) << endl;
        }
    }

    return 0;
}