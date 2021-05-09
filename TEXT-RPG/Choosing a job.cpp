//���� ���� using System;

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
            Console.WriteLine("������ �����ϼ���");
            Console.WriteLine("[1] ���");
            Console.WriteLine("[2] �ü�");
            Console.WriteLine("[3] ����");

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
                ClassType choice;   // �ʱ�ȭ ���� ������ �ڵ����� ù ��° ����� ClassType.None ���� �ʱ�ȭ �ȴ�.
                choice = ChooseClass(); // static�Լ��� Ŭ���� �̸����� ȣ���ϴ� Program.ChooseClass(); �͵� ����. 
                if (choice != ClassType.None)  // �Լ� ���ο��� switch ���� �ɸ��� �ʾҴٸ�, �� 123 �Է��� ���� �ʾҴٸ� �ٽ� �ݺ�. ����� 123 �� �ϳ� �Է� �ߴٸ� ���� ���� �׸���.
                    break; 
            }
        }
    }
}