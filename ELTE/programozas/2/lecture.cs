namespace s_to_hms
{

    class App
    {
        static void Main(string[] args)
        {
            ConvertToHMS(36610);

            System.Console.WriteLine(Fact(4));
            
            System.Console.WriteLine(WhichQuarter((1, 1)));
            System.Console.WriteLine(WhichQuarter((1, -1)));
            System.Console.WriteLine(WhichQuarter((-1, -1)));
            System.Console.WriteLine(WhichQuarter((-1, 1)));

        }

        static void ConvertToHMS(int s)
        {
            int h = s / 3600;
            s = s % 3600;

            int m = s / 60;
            s = s % 60;

            System.Console.WriteLine($"{h} ora, {m} perc, {s} masodperc\n");
        }

        static int Fact(int n)
        {
            int fact = 1;

            while (n > 1)
                fact *= n--;

            return fact;
        }

        static int WhichQuarter((int, int) point)
        {
            if (point.Item1 == 0 || point.Item2 == 0)
                return 0;

            int q = point.Item1 > 0 ? 0 : 3;
            q += point.Item2 > 0 ? 1 : q == 0 ? 2 : 0;

            return q;
        }
    }
}