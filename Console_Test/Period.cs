using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Console_Test
{
    class Period
    {
        public Course[] C; 
        public bool[] used;
        public Period()
        {
            C = new Course[4];
            used = new bool[4];
            for(int i = 0; i < 4; i++)
            {
                C[i] = new Course();
                used[i] = false;
            }
        }
    }
}
