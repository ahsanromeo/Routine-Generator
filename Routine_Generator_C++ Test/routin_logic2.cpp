
/// /* Bismillahir Rahmanir Rahim *\

/// S. M. Shakir Ahsan Romeo
/// Khulna University
/// CSE Discipline
#include <bits/stdc++.h>
using namespace std;
map<string, vector<string> > Prerequisite_List;
vector<string> fail_list;
struct Day_Period
{
    bool busy[5][9];
    Day_Period()
    {
        memset(busy, false, sizeof(busy));
    }
};
map<string, Day_Period> teacher_is_busy;
struct Course
{
    string ID;
    double credit;
    string teacher, second_teacher;
    Course()
    {
        ID = teacher = second_teacher = "";
        credit = 0.0;
    }
    bool operator < (const Course& CC) const /// Operator Overloading
    {
        int len1 = Prerequisite_List[ID].size(), len2 = Prerequisite_List[CC.ID].size();
        if(len1 == len2)
        {
            string aa = ID, bb = CC.ID;
            while(true)
            {
                if(aa[0] >= '0' && aa[0] <= '9')
                    break;
                aa.erase(aa.begin());
            }
            while(true)
            {
                if(bb[0] >= '0' && bb[0] <= '9')
                    break;
                bb.erase(bb.begin());
            }
            return aa < bb;
        }
        return len1 > len2;
    }
};
vector<Course> Lab[4], Theory[4];
struct Period
{
    Course C[4];
    bool used[4];
    Period()
    {
        memset(used, false, sizeof(used));
    }
};
vector<Period> Days[5];
void init();
void Process_Routine();
void Process_Labs();
void Process_Theories();
void Display();
int main() /// Main
{
    freopen("first_semester.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    init();
    //cout << "Course Lists for 4 semesters" << endl;
    for(int i = 0; i < 4; ++i)
    {
        int num_of_course;
        cin >> num_of_course;
        for(int j = 0; j < num_of_course; ++j)
        {
            Course CT;
            cin >> CT.ID >> CT.credit;
            int nt;
            cin >> nt;
            if(nt == 1)
            {
                cin >> CT.teacher;
                Day_Period dp;
                teacher_is_busy[CT.teacher] = dp;
            }
            else
            {
                cin >> CT.teacher >> CT.second_teacher;
                Day_Period dp;
                teacher_is_busy[CT.teacher] = teacher_is_busy[CT.second_teacher] = dp;
            }
            if(CT.credit == 0.75 || CT.credit == 1.5)
            {
                Lab[i].push_back(CT);
            }
            else
            {
                Theory[i].push_back(CT);
            }
        }
    }
    //cout << "Prerequisite" << endl;
    int num_of_pre_subs;
    cin >> num_of_pre_subs;
    for(int i = 0; i < num_of_pre_subs; ++i)
    {
        string ids;
        int n;
        cin >> ids >> n;
        for(int j = 0; j < n; ++j)
        {
            string prs;
            cin >> prs;
            Prerequisite_List[ids].push_back(prs);
        }
    }
    Process_Routine();
    //cout << fail_list.size();
    Display();
    cout << endl << endl << "Done!" << endl;
    return 0;
}
void Process_Routine()
{
    Process_Labs();
    Process_Theories();
}
void init()
{
    Prerequisite_List.clear();
    fail_list.clear();
    teacher_is_busy.clear();
    for(int i = 0; i < 4; ++i)
    {
        Lab[i].clear();
        Theory[i].clear();
    }
    for(int i = 0; i < 5; ++i)
    {
        Days[i].clear();
        Period P;
        for(int j = 0; j < 9; ++j)
        {
            Days[i].push_back(P);
        }
    }
}
void Process_Theories()
{
    for(int i = 0; i < 4; ++i) /// i'th semester
    {
        sort(Theory[i].begin(), Theory[i].end());
        for(int j = 0; j < Theory[i].size(); ++j) /// j'th theory
        {
            int len = Prerequisite_List[Theory[i][j].ID].size();
            int e = Theory[i][j].credit;
            if(len > 0 || i == 0)
            {
                bool day_used[5];
                memset(day_used, false, sizeof(day_used));
                if(i == 0 || i == 1)
                {
                    for(int k = 0; k < 5 && e > 0; ++k)
                    {
                        if(day_used[k])
                            continue;
                        for(int l = 0; l < Days[k].size(); ++l)
                        {
                            if(!Days[k][l].used[i]  &&  !teacher_is_busy[Theory[i][j].teacher].busy[k][l] && !teacher_is_busy[Theory[i][j].second_teacher].busy[k][l])
                            {
                                Days[k][l].used[i] = true;
                                Days[k][l].C[i] = Theory[i][j];
                                --e;
                                day_used[k] = true;
                                teacher_is_busy[Theory[i][j].teacher].busy[k][l] = true;
                                if(Theory[i][j].second_teacher != "")
                                {
                                    teacher_is_busy[Theory[i][j].second_teacher].busy[k][l] = true;
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(int k = 4; k >= 0 && e > 0; --k)
                    {
                        if(day_used[k])
                            continue;
                        for(int l = 0; l < Days[k].size(); ++l)
                        {
                            if(!Days[k][l].used[i]  &&  !teacher_is_busy[Theory[i][j].teacher].busy[k][l] && !teacher_is_busy[Theory[i][j].second_teacher].busy[k][l])
                            {
                                Days[k][l].used[i] = true;
                                Days[k][l].C[i] = Theory[i][j];
                                --e;
                                day_used[k] = true;
                                teacher_is_busy[Theory[i][j].teacher].busy[k][l] = true;
                                if(Theory[i][j].second_teacher != "")
                                {
                                    teacher_is_busy[Theory[i][j].second_teacher].busy[k][l] = true;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                bool day_used[5];
                memset(day_used, false, sizeof(day_used));
                if(i == 0 || i == 1)
                {
                    for(int k = 0; k < 5 && e > 0; ++k)
                    {
                        if(day_used[k])
                            continue;
                        for(int l = 0; l < Days[k].size(); ++l)
                        {
                            //if(!Days[k][l].used[i] && !Days[k][l].used[i - 1])
                            if(!Days[k][l].used[i]  &&  !teacher_is_busy[Theory[i][j].teacher].busy[k][l] && !teacher_is_busy[Theory[i][j].second_teacher].busy[k][l])
                            {
                                Days[k][l].used[i] = true;
                                Days[k][l].C[i] = Theory[i][j];
                                --e;
                                day_used[k] = true;
                                teacher_is_busy[Theory[i][j].teacher].busy[k][l] = true;
                                if(Theory[i][j].second_teacher != "")
                                {
                                    teacher_is_busy[Theory[i][j].second_teacher].busy[k][l] = true;
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(int k = 4; k >= 0 && e > 0; --k)
                    {
                        if(day_used[k])
                            continue;
                        for(int l = 0; l < Days[k].size(); ++l)
                        {
                            //if(!Days[k][l].used[i] && !Days[k][l].used[i - 1])
                            if(!Days[k][l].used[i]  &&  !teacher_is_busy[Theory[i][j].teacher].busy[k][l] && !teacher_is_busy[Theory[i][j].second_teacher].busy[k][l])
                            {
                                Days[k][l].used[i] = true;
                                Days[k][l].C[i] = Theory[i][j];
                                --e;
                                day_used[k] = true;
                                teacher_is_busy[Theory[i][j].teacher].busy[k][l] = true;
                                if(Theory[i][j].second_teacher != "")
                                {
                                    teacher_is_busy[Theory[i][j].second_teacher].busy[k][l] = true;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            if(e > 0)
                cout << e << " " << Theory[i][j].ID << endl;
        }
    }
}
void Process_Labs()
{
    for(int i = 0; i < 4; ++i) /// i'th semester
    {
        sort(Lab[i].begin(), Lab[i].end());
        bool lab_day_used[5];
        memset(lab_day_used, false, sizeof(lab_day_used));
        for(int j = 0; j < Lab[i].size(); ++j) /// j'th lab
        {
            int len = Prerequisite_List[Lab[i][j].ID].size();
            bool ef = true;
            if(i == 0 || len > 0)
            {
                for(int k = 0; k < 5; ++k)
                {
                    if(lab_day_used[k])
                        continue;
                    if(!Days[k][3].used[i] && !teacher_is_busy[Lab[i][j].teacher].busy[k][3] && !teacher_is_busy[Lab[i][j].second_teacher].busy[k][3])
                    {
                        Days[k][3].C[i] = Days[k][4].C[i] = Days[k][5].C[i] = Lab[i][j];
                        Days[k][3].used[i] = Days[k][4].used[i] = Days[k][5].used[i] = lab_day_used[k] = true;
                        ef = false;
                        teacher_is_busy[Lab[i][j].teacher].busy[k][3] = teacher_is_busy[Lab[i][j].teacher].busy[k][4] = teacher_is_busy[Lab[i][j].teacher].busy[k][5] = true;
                        if(Lab[i][j].second_teacher != "")
                        {
                            teacher_is_busy[Lab[i][j].second_teacher].busy[k][3] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][4] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][5] = true;
                        }
                        break;
                    }
                    else if(!Days[k][6].used[i] && !teacher_is_busy[Lab[i][j].teacher].busy[k][6] && !teacher_is_busy[Lab[i][j].second_teacher].busy[k][6])
                    {
                        Days[k][6].C[i] = Days[k][7].C[i] = Days[k][8].C[i] = Lab[i][j];
                        Days[k][6].used[i] = Days[k][7].used[i] = Days[k][8].used[i] = lab_day_used[k] = true;
                        ef = false;
                        teacher_is_busy[Lab[i][j].teacher].busy[k][6] = teacher_is_busy[Lab[i][j].teacher].busy[k][7] = teacher_is_busy[Lab[i][j].teacher].busy[k][8] = true;
                        if(Lab[i][j].second_teacher != "")
                        {
                            teacher_is_busy[Lab[i][j].second_teacher].busy[k][6] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][7] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][8] = true;
                        }
                        break;
                    }
                }
            }
            else
            {
                for(int k = 0; k < 5; ++k)
                {
                    if(!Days[k][3].used[i] && !Days[k][3].used[i - 1] && !Days[k][4].used[i - 1] && !Days[k][5].used[i - 1]  &&  !teacher_is_busy[Lab[i][j].teacher].busy[k][3] && !teacher_is_busy[Lab[i][j].second_teacher].busy[k][3])
                    {
                        Days[k][3].C[i] = Days[k][4].C[i] = Days[k][5].C[i] = Lab[i][j];
                        Days[k][3].used[i] = Days[k][4].used[i] = Days[k][5].used[i] = lab_day_used[k] = true;
                        ef = false;
                        teacher_is_busy[Lab[i][j].teacher].busy[k][3] = teacher_is_busy[Lab[i][j].teacher].busy[k][4] = teacher_is_busy[Lab[i][j].teacher].busy[k][5] = true;
                        if(Lab[i][j].second_teacher != "")
                        {
                            teacher_is_busy[Lab[i][j].second_teacher].busy[k][3] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][4] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][5] = true;
                        }
                        break;
                    }
                    else if(!Days[k][6].used[i] && !Days[k][6].used[i - 1] && !Days[k][7].used[i - 1] && !Days[k][8].used[i - 1]  &&  !teacher_is_busy[Lab[i][j].teacher].busy[k][6] && !teacher_is_busy[Lab[i][j].second_teacher].busy[k][6])
                    {
                        Days[k][6].C[i] = Days[k][7].C[i] = Days[k][8].C[i] = Lab[i][j];
                        Days[k][6].used[i] = Days[k][7].used[i] = Days[k][8].used[i] = lab_day_used[k] = true;
                        ef = false;
                        teacher_is_busy[Lab[i][j].teacher].busy[k][6] = teacher_is_busy[Lab[i][j].teacher].busy[k][7] = teacher_is_busy[Lab[i][j].teacher].busy[k][8] = true;
                        if(Lab[i][j].second_teacher != "")
                        {
                            teacher_is_busy[Lab[i][j].second_teacher].busy[k][6] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][7] = teacher_is_busy[Lab[i][j].second_teacher].busy[k][8] = true;
                        }
                        break;
                    }
                }
            }
            if(ef)
                cout << " Lab " << Lab[i][j].ID << endl;
            //fail_list.push_back(Lab[i][j].ID);
        }
    }
}
void Display()
{
    cout << endl << endl;
    for(int i = 0; i < 5; ++i)
    {
        cout << i + 1 << ": ";
        for(int j = 0; j < 4; ++j)
        {
            for(int k = 0; k < Days[i].size(); ++k)
            {
                if(j == 0 && k == 0)
                {
                    if(Days[i][k].used[j])
                    {
                        cout << " " << Days[i][k].C[j].ID;
                    }
                    else
                    {
                        cout << "  Blank ";
                    }
                }
                else
                {
                    if(Days[i][k].used[j])
                    {
                        cout << "    " << Days[i][k].C[j].ID;
                    }
                    else
                    {
                        cout << "     Blank ";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}
