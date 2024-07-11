#include <bits/stdc++.h>
using namespace std;

/*
A fleet of K identical trucks having capacity Q need to be scheduled to delivery pepsi packages from a central depot 0 to clients 1,2,…,n.
Each client i requests d[i] packages. The distance from location i to location j is c[i,j], 0≤i,j≤n.
A delivery solution is a set of routes: each truck is associated with a route, starting from depot,
visiting some clients and returning to the depot for deliverying requested pepsi packages such that:
Each client is visited exactly by one route
Total number of packages requested by clients of each truck cannot exceed its capacity
Goal
Find a solution having minimal total travel distance
Note that:
There might be the case that a truck does not visit any client (empty route)
The orders of clients in a route is important, e.g., routes 0 -> 1 -> 2 -> 3 -> 0 and 0 -> 3-> 2 -> 1 -> 0 are different.
*/

int n, K, Q, sol = INT_MAX, cmin = INT_MAX, sum = 0;
int visited[100], firstCustomerOfTruck[100];
int trace[100], load[100], d[100], c[100][100];

void Try(int k, int vehicle)
{
    // loop for all customers
    for (int customer = 1; customer <= n; customer++)
    {
        if (!visited[customer])
        {
            // try to assign customers to vehicle
            int curVehicle = vehicle;
            if (load[curVehicle] - d[customer] >= 0)
            {
                if (k == 1)
                    firstCustomerOfTruck[curVehicle] = customer;

                visited[customer] = 1;
                trace[k] = customer;
                sum += c[trace[k - 1]][customer];
                load[curVehicle] -= d[customer];

                if (k == n)
                {
                    sol = min(sol, sum + c[customer][0]);
                }
                else
                {
                    if (sum + cmin * (n - k + 1) < sol)
                        Try(k + 1, curVehicle);
                }

                visited[customer] = 0;
                sum -= c[trace[k - 1]][customer];
                load[curVehicle] += d[customer];
            }

            // if vehicle is not capable of transferring anymore -> assign next vehicle
            curVehicle++;
            if (curVehicle <= K)
            {
                // check for no collision (2 trucks serves the same customer)
                // only need to check for the first customer because the other customers is in ascending order so there wouldn't be a collision
                if (load[curVehicle] - d[customer] >= 0 && customer > firstCustomerOfTruck[curVehicle - 1])
                {
                    firstCustomerOfTruck[curVehicle] = customer;
                    visited[customer] = 1;
                    trace[k] = customer;
                    sum += c[trace[k - 1]][0] + c[0][customer]; // send previous vehicle back home and assign next vehicle to the customer
                    load[curVehicle] -= d[customer];

                    if (k == n)
                    {
                        sol = min(sol, sum + c[customer][0]);
                    }
                    else
                    {
                        if (sum + cmin * (n - k + 1) < sol)
                            Try(k + 1, curVehicle);
                    }

                    visited[customer] = 0;
                    sum -= c[trace[k - 1]][0] + c[0][customer];
                    load[curVehicle] += d[customer];
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> K >> Q; //(2≤n≤12,1≤K≤5,1≤Q≤50)

    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }

    for (int i = 1; i <= K; i++)
        load[i] = Q;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cin >> c[i][j];
            if (i != j && cmin > c[i][j])
                cmin = c[i][j];
        }
    }

    Try(1, 1);

    cout << sol;
    return 0;
}