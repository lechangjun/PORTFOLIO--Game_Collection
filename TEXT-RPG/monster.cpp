// 몬스터 생성
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
            int randMonster = rand.Next(1, 4); // 1 ~ 3 중 랜덤 정수 리턴

            switch(randMonster)
            {
                case (int)MonsterType.Slime:
                    Console.WriteLine("슬라임이 스폰 되었습니다!");
                    monster.hp = 20;
                    monster.attack = 2;
                    break;
                case (int)MonsterType.Orc:
                    Console.WriteLine("오크가 스폰 되었습니다!");
                    monster.hp = 40;
                    monster.attack = 4;
                    break;
                case (int)MonsterType.Skeleton:
                    Console.WriteLine("스켈레톤이 스폰 되었습니다!");
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
            Console.WriteLine("필드에 접속했습니다.");

            // 랜덤으로 1~3 몬스터 중 하나를 리스폰
            Monster monster;
            CreateRandomMonster(out monster);
        }

        static void EnterGame()
        {
            while(true)
            {
                Console.WriteLine("마을에 접속했습니다.");
                Console.WriteLine("[1] 월드로 간다.");
                Console.WriteLine("[2] 로비로 돌아가기.");

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
                // 직업 고르기
                ClassType choice;
                choice = ChooseClass(); // Program.ChooseClass();
                if (choice != ClassType.None)
                {
                    // 플레이어 캐릭터 생성
                    Player player;
                    CreatePlayer(choice, out player);
                    Console.WriteLine($"HP{player.hp}, Attack{player.attack}");

                    // 게임 시작! 몬스터 생성 및 전투
                    EnterGame();
                }
            }
        }
    }