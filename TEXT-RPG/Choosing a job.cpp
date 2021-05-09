//직업 고르기 using System;

namespace CSharp
{
    class Program
    {
        enum ClassType
        {
            None = 0,
            Knight = 1,
            Archer = 2,
            Mage = 3
        }

        static ClassType ChooseClass()
        {
            Console.WriteLine("직업을 선택하세요");
            Console.WriteLine("[1] 기사");
            Console.WriteLine("[2] 궁수");
            Console.WriteLine("[3] 법사");

            ClassType choice = ClassType.None;
            string input = Console.ReadLine(); 
            switch (input)
            {
                case "1":
                    choice = ClassType.Knight;
                    break;
                case "2":
                    choice = ClassType.Archer;
                    break;
                case "3":
                    choice = ClassType.Mage;
                    break;
            }

            return choice;
        }

        static void Main(string[] args)
        {
            while (true)
            {
                ClassType choice;   // 초기화 하지 않으면 자동으로 첫 번째 상수인 ClassType.None 으로 초기화 된다.
                choice = ChooseClass(); // static함수라 클래스 이름으로 호출하는 Program.ChooseClass(); 와도 같다. 
                if (choice != ClassType.None)  // 함수 내부에서 switch 문에 걸리지 않았다면, 즉 123 입력을 하지 않았다면 다시 반복. 제대로 123 중 하나 입력 했다면 직업 선택 그만함.
                    break; 
            }
        }
    }
}