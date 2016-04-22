using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Console_Test
{
    class Program
    {

        public static List<Course>[] Lab, Theory;
        public static List<Period>[] Days;
        public static Dictionary<string, List<String>> Prerequisite_List;
        public static Dictionary<string, int[,]> teacher_is_busy;
        public static Dictionary<string, int> Failed_List;
        static void Main(string[] args)
        {
            //string s = Console.ReadLine();
            //Console.WriteLine(s);
            init();
            StreamReader reader = null;
            try
            {
                reader = new StreamReader("first_sem.txt");
                for (int i = 0; i < 4; ++i)
                {
                    int nc = Convert.ToInt32(reader.ReadLine());
                    for (int j = 0; j < nc; ++j)
                    {
                        Course CT = new Course(reader.ReadLine(), Convert.ToDouble(reader.ReadLine()));
                        if(Convert.ToInt32(reader.ReadLine()) == 1)
                        {
                            CT.teacher = reader.ReadLine();
                            if(!teacher_is_busy.ContainsKey(CT.teacher))
                                teacher_is_busy.Add(CT.teacher, new int[5, 9]);
                            CT.second_teacher = "";
                                teacher_is_busy[CT.second_teacher] = new int[5, 9];
                        }
                        else
                        {
                            CT.teacher = reader.ReadLine();
                            if(!teacher_is_busy.ContainsKey(CT.teacher))
                                teacher_is_busy.Add(CT.teacher, new int[5, 9]);
                            CT.second_teacher = reader.ReadLine();
                            if (!teacher_is_busy.ContainsKey(CT.second_teacher))
                                teacher_is_busy.Add(CT.second_teacher, new int[5, 9]);
                        }
                        if (CT.Credit == 0.75 || CT.Credit == 1.5)
                        {
                            Lab[i].Add(CT);
                        }
                        else
                        {
                            Theory[i].Add(CT);
                        }
                    }
                }
                int prs = Convert.ToInt32(reader.ReadLine());
                for(int i = 0; i < prs; ++i)
                {
                    string ids = reader.ReadLine();
                    if(!Prerequisite_List.ContainsKey(ids))
                    {
                        Prerequisite_List.Add(ids, new List<string>());
                    }
                    int n = Convert.ToInt32(reader.ReadLine());
                    for(int j = 0; j < n; ++j)
                    {
                        Prerequisite_List[ids].Add(reader.ReadLine());
                    }
                }
                Process();
                Display();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                if (reader != null)
                    reader.Close();
            }
            Console.WriteLine("\nreturn 0;");
            Console.ReadLine();
        }
        public static void init()
        {
            try
            {
                teacher_is_busy = new Dictionary<string, int[,]>();
                teacher_is_busy.Add("", new int[5, 9]);
                Prerequisite_List = new Dictionary<string, List<string>>();
                Failed_List = new Dictionary<string, int>();
                Lab = new List<Course>[4];
                Theory = new List<Course>[4];
                Days = new List<Period>[5];
                for (int i = 0; i < 4; i++)
                {
                    Lab[i] = new List<Course>();
                    Theory[i] = new List<Course>();
                }
                for (int i = 0; i < 5; i++)
                {
                    Days[i] = new List<Period>();
                    for (int j = 0; j < 9; j++)
                    {
                        Days[i].Add(new Period());
                    }
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message + "   init");
            }
        }
        public static void Process()
        {
            Process_Lab();
            Process_Theory();
        }
        public static void Display()
        {
            StreamWriter sr = null;
            try
            {
                sr = new StreamWriter("output.txt");
                for(int i = 0; i < 5; ++i)
                {
                    for(int j = 0; j < 4; ++j)
                    {
                        string line = "";
                        for(int k = 0; k < Days[i].Count; ++k)
                        {
                            if(j == 0 && k == 0)
                            {
                                if(Days[i][k].used[j])
                                {
                                    line += (" " + Days[i][k].C[j].ID);
                                }
                                else
                                {
                                    line += ("   Blank");
                                }
                            }
                            else
                            {
                                if(Days[i][k].used[j])
                                {
                                    line += (" " + Days[i][k].C[j].ID);
                                }
                                else
                                {
                                    line += ("   Blank");
                                }
                            }
                        }
                        sr.WriteLine(line);
                    }
                    sr.WriteLine();
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message + "   Display");
            }
            finally
            {
                if (sr != null)
                    sr.Close();
            }
            try
            {
                sr = new StreamWriter("Failed_List");
                foreach(var pair in Failed_List)
                {
                    sr.WriteLine(pair.Key + " " + pair.Value);
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message + "   Failed list");
            }
            finally
            {
                if (sr != null)
                    sr.Close();
            }
        }
        public static void Process_Lab()
        {
            for(int i = 0; i < 4; ++i)
            {
                Lab[i] = Sort(Lab[i]);
                int[] lab_day_used = new int[5];
                for (int xx = 0; xx < 5; ++xx)
                    lab_day_used[xx] = 0;
                for(int j = 0; j < Lab[i].Count; ++j)
                {
                    int len = 0;
                    if(Prerequisite_List.ContainsKey(Lab[i][j].ID))
                    {
                        len = Prerequisite_List[Lab[i][j].ID].Count;
                    }
                    int ef = 1;
                    if(i == 0 || len > 0)
                    {
                        for(int k = 0; k < 5; ++k)
                        {
                            if (lab_day_used[k] == 1)
                                continue;
                            if (!Days[k][3].used[i] && teacher_is_busy[Lab[i][j].teacher][k, 3] == 0 && teacher_is_busy[Lab[i][j].second_teacher][k, 3] == 0)
                            {
                                Days[k][3].C[i] = Days[k][4].C[i] = Days[k][5].C[i] = Lab[i][j];
                                Days[k][3].used[i] = Days[k][4].used[i] = Days[k][5].used[i] = true;
                                lab_day_used[k] = 1;
                                ef = 0;
                                teacher_is_busy[Lab[i][j].teacher][k, 3] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 4] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 5] = 1;

                                if(!Lab[i][j].second_teacher.Equals(""))
                                {
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 3] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 4] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 5] = 1;
                                }
                                break;
                            }
                            else if (!Days[k][6].used[i] && teacher_is_busy[Lab[i][j].teacher][k, 6] == 0 && teacher_is_busy[Lab[i][j].second_teacher][k, 6] == 0)
                            {
                                Days[k][6].C[i] = Days[k][7].C[i] = Days[k][8].C[i] = Lab[i][j];
                                Days[k][6].used[i] = Days[k][7].used[i] = Days[k][8].used[i] = true;
                                lab_day_used[k] = 1;
                                ef = 0;
                                teacher_is_busy[Lab[i][j].teacher][k, 6] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 7] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 8] = 1;
                                if (!Lab[i][j].second_teacher.Equals(""))
                                {
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 6] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 7] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 8] = 1;
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; ++k)
                        {
                            if (!Days[k][3].used[i] && !Days[k][3].used[i - 1] && !Days[k][4].used[i - 1] && !Days[k][5].used[i - 1] && teacher_is_busy[Lab[i][j].teacher][k, 3] == 0 && teacher_is_busy[Lab[i][j].second_teacher][k, 3] == 0)
                            {
                                Days[k][3].C[i] = Days[k][4].C[i] = Days[k][5].C[i] = Lab[i][j];
                                Days[k][3].used[i] = Days[k][4].used[i] = Days[k][5].used[i] = true;
                                lab_day_used[k] = 1;
                                ef = 0;
                                teacher_is_busy[Lab[i][j].teacher][k, 3] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 4] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 5] = 1;
                                if (!Lab[i][j].second_teacher.Equals(""))
                                {
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 3] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 4] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 5] = 1;
                                }
                                break;
                            }
                            else if (!Days[k][6].used[i] && !Days[k][6].used[i - 1] && !Days[k][7].used[i - 1] && !Days[k][8].used[i - 1] && teacher_is_busy[Lab[i][j].teacher][k, 6] == 0 && teacher_is_busy[Lab[i][j].second_teacher][k, 6] == 0)
                            {
                                Days[k][6].C[i] = Days[k][7].C[i] = Days[k][8].C[i] = Lab[i][j];
                                Days[k][6].used[i] = Days[k][7].used[i] = Days[k][8].used[i] = true;
                                lab_day_used[k] = 1;
                                ef = 0;
                                teacher_is_busy[Lab[i][j].teacher][k, 6] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 7] = 1;
                                teacher_is_busy[Lab[i][j].teacher][k, 8] = 1;
                                if (!Lab[i][j].second_teacher.Equals(""))
                                {
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 6] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 7] = 1;
                                    teacher_is_busy[Lab[i][j].second_teacher][k, 8] = 1;
                                }
                                break;
                            }
                        }
                    }
                    if(ef > 0)
                    {
                        Failed_List.Add("Lab    " + Lab[i][j].ID, ef);
                    }
                }
            }
        }
        public static void Process_Theory()
        {
            for(int i = 0; i < 4; ++i)
            {
                Theory[i] = Sort(Theory[i]);
                for(int j = 0; j < Theory[i].Count; ++j)
                {
                    int len = 0;
                    if(Prerequisite_List.ContainsKey(Theory[i][j].ID))
                    {
                        len = Prerequisite_List[Theory[i][j].ID].Count;
                    }
                    int e = Convert.ToInt32((Theory[i][j].Credit));
                    if(len > 0 || i == 0)
                    {
                        int[] day_used = new int[5];
                        for (int xx = 0; xx < 5; ++xx)
                            day_used[xx] = 0;
                        if(i == 0 || i == 1)
                        {
                            for (int k = 0; k < 5 && e > 0; ++k)
                            {
                                if (day_used[k] == 1)
                                    continue;
                                for (int l = 0; l < Days[k].Count; ++l)
                                {
                                    if (!Days[k][l].used[i] && teacher_is_busy[Theory[i][j].teacher][k, l] == 0 && teacher_is_busy[Theory[i][j].second_teacher][k, l] == 0)
                                    {
                                        Days[k][l].used[i] = true;
                                        Days[k][l].C[i] = Theory[i][j];
                                        --e;
                                        day_used[k] = 1;
                                        teacher_is_busy[Theory[i][j].teacher][k, l] = 1;
                                        if (!Theory[i][j].second_teacher.Equals(""))
                                        {
                                            teacher_is_busy[Theory[i][j].second_teacher][k, l] = 1;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (int k = 4; k >= 0 && e > 0; --k)
                            {
                                if (day_used[k] == 1)
                                    continue;
                                for (int l = 0; l < Days[k].Count; ++l)
                                {
                                    if (!Days[k][l].used[i] && teacher_is_busy[Theory[i][j].teacher][k, l] == 0 && teacher_is_busy[Theory[i][j].second_teacher][k, l] == 0)
                                    {
                                        Days[k][l].used[i] = true;
                                        Days[k][l].C[i] = Theory[i][j];
                                        --e;
                                        day_used[k] = 1;
                                        teacher_is_busy[Theory[i][j].teacher][k, l] = 1;
                                        if (!Theory[i][j].second_teacher.Equals(""))
                                        {
                                            teacher_is_busy[Theory[i][j].second_teacher][k, l] = 1;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        int[] day_used = new int[5];
                        for(int xx = 0; xx < 5; ++xx)
                            day_used[xx] = 0;
                        if(i == 0 || i == 1)
                        {
                            for (int k = 0; k < 5 && e > 0; ++k)
                            {
                                if (day_used[k] == 1)
                                    continue;
                                for (int l = 0; l < Days[k].Count; ++l)
                                {
                                    //if(!Days[k][l].used[i] && !Days[k][l].used[i - 1])
                                    if (!Days[k][l].used[i] && teacher_is_busy[Theory[i][j].teacher][k, l] == 0 && teacher_is_busy[Theory[i][j].second_teacher][k, l] == 0)
                                    {
                                        Days[k][l].used[i] = true;
                                        Days[k][l].C[i] = Theory[i][j];
                                        --e;
                                        day_used[k] = 1;
                                        teacher_is_busy[Theory[i][j].teacher][k, l] = 1;
                                        if (!Theory[i][j].second_teacher.Equals(""))
                                        {
                                            teacher_is_busy[Theory[i][j].second_teacher][k, l] = 1;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (int k = 4; k >= 0 && e > 0; --k)
                            {
                                if (day_used[k] == 1)
                                    continue;
                                for (int l = 0; l < Days[k].Count; ++l)
                                {
                                    //if(!Days[k][l].used[i] && !Days[k][l].used[i - 1])
                                    if (!Days[k][l].used[i] && teacher_is_busy[Theory[i][j].teacher][k, l] == 0 && teacher_is_busy[Theory[i][j].second_teacher][k, l] == 0)
                                    {
                                        Days[k][l].used[i] = true;
                                        Days[k][l].C[i] = Theory[i][j];
                                        --e;
                                        day_used[k] = 1;
                                        teacher_is_busy[Theory[i][j].teacher][k, l] = 1;
                                        if (!Theory[i][j].second_teacher.Equals(""))
                                        {
                                            teacher_is_busy[Theory[i][j].second_teacher][k, l] = 1;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(e > 0)
                    {
                        Failed_List.Add("Theory " + Theory[i][j].ID, e);
                    }
                }
            }
        }
        public static List<Course> Sort(List<Course> LS)
        {
            LS.Sort(delegate(Course a, Course b)
            {
                int len1 = 0;
                if (Prerequisite_List.ContainsKey(a.ID))
                {
                    len1 = Prerequisite_List[a.ID].Count;
                }
                int len2 = 0;
                if (Prerequisite_List.ContainsKey(b.ID))
                {
                    len1 = Prerequisite_List[b.ID].Count;
                }
                if (len1 == len2)
                {
                    string s = "", t = "";
                    for (int i = 0; i < a.ID.Length; ++i)
                    {
                        if (a.ID[i] >= '0' && a.ID[i] <= '9')
                        {
                            for (int j = i; j < a.ID.Length; ++j)
                            {
                                s += a.ID[i];
                            }
                            break;
                        }
                    }
                    for (int i = 0; i < b.ID.Length; ++i)
                    {
                        if (b.ID[i] >= '0' && b.ID[i] <= '9')
                        {
                            for (int j = i; j < b.ID.Length; ++j)
                            {
                                t += b.ID[i];
                            }
                            break;
                        }
                    }
                    return s.CompareTo(t);
                }
                else
                {
                    return len2.CompareTo(len1);
                }
            });
            return LS;
        }
    }
}
