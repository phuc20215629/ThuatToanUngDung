#include <bits/stdc++.h>
using namespace std;

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
            // assign customers to vehicle j
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

            // assign next vehicle
            curVehicle++;
            if (curVehicle <= K)
            {
                // check for no collision (2 trucks serves the same customer)
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