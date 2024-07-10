#include <bits/stdc++.h>
using namespace std;

int n = 4;
string s;

void tryBinary(int k)
{
    for (int i = 0; i <= 1; i++)
    {
        s.append(to_string(i));
        if (k == n)
            cout << s << "\n";
        else
            tryBinary(k + 1);
        s = s.substr(0, s.length() - 1);
    }
}

int main()
{
    // tryBinary(1);
    stack<string> st;
    st.push("");

    while (!st.empty())
    {
        string curr = st.top();
        st.pop();

        if (curr.length() == n)
        {
            cout << curr << "\n";
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                st.push(curr + to_string(i));
            }
        }
    }

    return 0;
}