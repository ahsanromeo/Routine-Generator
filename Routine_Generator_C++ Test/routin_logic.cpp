
/// /* Bismillahir Rahmanir Rahim *\

/// S. M. Shakir Ahsan Romeo
/// Khulna University
/// CSE Discipline
#include <bits/stdc++.h>
using namespace std;
typedef long long lng;
#define     rt             return
#define     PI             acos(-1.0)
#define     eps            1e-9
#define     inf            (1<<30)
#define     FAST           ios_base::sync_with_stdio(0);cin.tie(0);
#define     endl           '\n'
#define     pb             push_back
#define     sf             scanf
#define     pf             printf
#define     bin_sea        binary_search
#define     dbg(x)         cout << x << " came here\n";
#define     all(x)         x.begin(), x.end()
#define     mem(x, y)      memset(x, y, sizeof(x));
#define     rep(i, x)      for(int i = 0; i < x; ++i)
#define     rep1(i, x)     for(int i = 1; i <= x; ++i)
#define     pmat2(A, x, y) rep(i, x) { rep(j, y) cout << A[i][j] << ' '; cout << endl; }
#define     smat2(A, x, y) rep(i, x) rep(j, y) cin >> A[i][j];
#define     RAD_TO_DEG     180.0/PI
struct Course
{
    string ID;
    double credit;
    string teach_name;
    string course_type;
    Course()
    {
        ID = teach_name = course_type = "";
        credit = 0.0;
    }
    bool operator < (const Course& CC) const
    {
        if(credit == CC.credit)
        {
            return ID < CC.ID;
        }
        else
        {
            return credit < CC.credit;
        }
    }
};
struct Period
{
    bool used;
    Course C;
    Period()
    {
        used = false;
    }
};
vector<string> Teachers;
vector<Course> VC;
vector<Period> Days[5];
vector<string> Durations;
vector<string> Daynames;
void init()
{
    VC.clear();
    Teachers.clear();
    rep(i, 5)
    {
        Days[i].clear();
        rep(j, 9)
        {
            Period PP;
            PP.used = false;
            Days[i].pb(PP);
        }
    }
    Durations.clear();
    Durations.pb("08:00");
    Durations.pb("08:50");
    Durations.pb("09:40");
    Durations.pb("10:50");
    Durations.pb("11:40");
    Durations.pb("12:30");
    Durations.pb("02:30");
    Durations.pb("03:20");
    Durations.pb("04:10");

    Daynames.clear();
    Daynames.pb("Sun");
    Daynames.pb("Mon");
    Daynames.pb("Tue");
    Daynames.pb("Wed");
    Daynames.pb("Thu");
}
void Process()
{
    sort(VC.begin(), VC.end());
    bool lab_day[5];
    memset(lab_day, false, sizeof(lab_day));
    for(int i = 0; i < VC.size(); ++i)
    {
        if(VC[i].credit == 3.0 || VC[i].credit == 2.0)
        {
            int e = VC[i].credit;
            bool day_used[5];
            memset(day_used, false, sizeof(day_used));
            for(int j = 0; j < e;)
            {
                for(int k = 0; k < 5; ++k)
                {
                    if(day_used[k])
                        continue;
                    bool bb = false;
                    for(int l = 0; l < Days[k].size(); ++l)
                    {
                        if(!Days[k][l].used)
                        {
                            Days[k][l].used = true;
                            Days[k][l].C = VC[i];
                            day_used[k] = true;
                            ++j;
                            bb = true;
                            break;
                        }
                    }
                    if(bb)
                        break;
                }
            }
        }
        else
        {
            for(int j = 0; j < 5; ++j)
            {
                if(!lab_day[j])
                {
                    if(!Days[j][3].used)
                    {
                        Days[j][3].used = Days[j][4].used = Days[j][5].used = true;
                        Days[j][3].C = Days[j][4].C = Days[j][5].C = VC[i];
                        lab_day[j] = true;
                        break;
                    }
                    else if(!Days[j][6].used)
                    {
                        Days[j][6].used = Days[j][7].used = Days[j][8].used = true;
                        Days[j][6].C = Days[j][7].C = Days[j][8].C = VC[i];
                        lab_day[j] = true;
                        break;
                    }
                }
            }
        }
    }
}
void Display()
{
    cout << endl << endl << "Periods ";
    for(int i = 0; i < Durations.size(); ++i)
    {
        cout << Durations[i] << "\t";
    }
    cout << endl << endl;
    for(int i = 0; i < 5; ++i)
    {
        cout << Daynames[i] << "\t";
        for(int j = 0; j < Days[i].size(); ++j)
        {
            if(!Days[i][j].used)
            {
                cout << "Blank\t";
            }
            else
            {
                cout << Days[i][j].C.ID << "\t";
            }
        }
        cout << endl;
    }
}
int main()
{
    //freopen("in.txt", "r", stdin);
    init();
    int num_of_course;
    cout << "Enter number of course: ";
    cin >> num_of_course;
    rep(i, num_of_course)
    {
        Course CT;
        cout << "Enter " << i + 1 << "'th course's ID: ";
        cin >> CT.ID;
        cout << "Enter " << i + 1 << "'th course's Credit: ";
        cin >> CT.credit;
        cout << "Enter " << i + 1 << "'th course's Teacher name: ";
        cin >> CT.teach_name;
        VC.pb(CT);
    }
    Process();
    Display();
    return 0;
}
/*int num_of_teachers;
    cout << "Enter Number of Teachers: ";
    cin >> num_of_teachers;
    rep(i, num_of_teachers)
    {
        string sst;
        cout << "Enter " << i + 1 << "'th teacher name: ";
        cin >> sst;
        Teachers.pb(sst);
    }*/
