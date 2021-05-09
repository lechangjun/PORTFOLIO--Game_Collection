// ���� ����
enum MonsterType
        {
            None = 0,
            Slime = 1,
            Orc = 2,
            Skeleton = 3
        }

        struct Monster
        {
            public int hp;
            public int attack;
        }

        static void CreateRandomMonster(out Monster monster)
        {
            Random rand = new Random();
            int randMonster = rand.Next(1, 4); // 1 ~ 3 �� ���� ���� ����

            switch(randMonster)
            {
                case (int)MonsterType.Slime:
                    Console.WriteLine("�������� ���� �Ǿ����ϴ�!");
                    monster.hp = 20;
                    monster.attack = 2;
                    break;
                case (int)MonsterType.Orc:
                    Console.WriteLine("��ũ�� ���� �Ǿ����ϴ�!");
                    monster.hp = 40;
                    monster.attack = 4;
                    break;
                case (int)MonsterType.Skeleton:
                    Console.WriteLine("���̷����� ���� �Ǿ����ϴ�!");
                    monster.hp = 30;
                    monster.attack = 3;
                    break;
                default:
                    monster.hp = 0;
                    monster.attack = 0;
                    break;
            }
        }

        static void EnterField()
        {
            Console.WriteLine("�ʵ忡 �����߽��ϴ�.");

            // �������� 1~3 ���� �� �ϳ��� ������
            Monster monster;
            CreateRandomMonster(out monster);
        }

        static void EnterGame()
        {
            while(true)
            {
                Console.WriteLine("������ �����߽��ϴ�.");
                Console.WriteLine("[1] ����� ����.");
                Console.WriteLine("[2] �κ�� ���ư���.");

                String input = Console.ReadLine();

                switch (input)
                {
                    case "1":
                        EnterField();
                        break;
                    case "2":
                        return;
                }
            }
        }

        static void Main(string[] args)
        {
            while (true)
            {
                // ���� ����
                ClassType choice;
                choice = ChooseClass(); // Program.ChooseClass();
                if (choice != ClassType.None)
                {
                    // �÷��̾� ĳ���� ����
                    Player player;
                    CreatePlayer(choice, out player);
                    Console.WriteLine($"HP{player.hp}, Attack{player.attack}");

                    // ���� ����! ���� ���� �� ����
                    EnterGame();
                }
            }
        }
    }