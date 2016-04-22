#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("first_semester.txt", "r", stdin);
    int s = 0;
    for(int i = 0; i < 4; ++i)
    {
        int n;
        cin >> n;
        for(int j = 0; j < n; ++j)
        {
            string sss;
            int xx;
            cin >> sss >> xx;
            if(xx >= 2)
                s += xx;
        }
    }
    cout << s << endl;
    return 0;
}
