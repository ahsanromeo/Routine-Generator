using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Console_Test
{
    class Course
    {
        public string ID, teacher, second_teacher;
        public double Credit;
        public Course()
        {
            ID = teacher = second_teacher = "";
            Credit = 0.0;
        }
        public Course(string id, double credit)
        {
            ID = id;
            Credit = credit;
        }
    }
}
