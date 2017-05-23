using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_4
{
    class Program
    {
       
        public static int xGCD(int a, int b, out int x, out int y )
        {
            if (b == 0)
            {
                x = 1; y = 0;
                return a;
            }
            int x1, y1, gcd = xGCD(b, a % b, out x1, out y1);
            x = y1;
            y = x1 - (a / b) * y1;
            return gcd;
        }

        private static int Mod(int a, int b)
        {
            return (a % b + b) % b;
        }

        static int GCD(int a, int b)
        {
            int r;
            while (b != 0) { r = a % b; a = b; b = r; }
            return a;
        }

        private static int rGCD(int a,int b, int m)
        {
            int d = GCD(a, m), k = Mod(b, d);
            if (k != 0) throw new ArgumentException();
            m /= d;
            int x, y;
            int f = xGCD(a / d, m, out x, out y);
            return Mod(x * (b / d), m);
        }
        public static void Swap<T>(ref T obj1, ref T obj2)
        {
            var temp = obj1;
            obj1 = obj2;
            obj2 = temp;
        }

        
        static void Main(string[] args)
        {
            int a, b, x, y, gcd,rgcd;
            int k, m, l;
            Console.Write("a: ");
            a = int.Parse(Console.ReadLine());
            Console.Write("b: ");
            b = int.Parse(Console.ReadLine());

            if (a < b)
                Swap(ref a, ref b);
            gcd = xGCD(a, b,out x, out y);
            Console.WriteLine("GCD: " + gcd);
            Console.WriteLine("x = " + x);
            Console.WriteLine("y = " + y);

            Console.Write("a: ");
            k = int.Parse(Console.ReadLine());
            Console.Write("b: ");
            l = int.Parse(Console.ReadLine());
            Console.Write("m: ");
            m = int.Parse(Console.ReadLine());
            rgcd = rGCD(k,l, m);
            Console.WriteLine("b: " + rgcd);

            Console.ReadLine();

        }
        


    }
  
}
