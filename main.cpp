//前面不用管，直接跳到Line84
//gcc ncurses-1.c -o a.out -lncurses
#include <ncurses.h>
#include <string.h>
#include <thread>    // Include for std::this_thread::sleep_for
#include <chrono>

void smileface(int scrLine, int scrCol){
    mvprintw(scrLine / 2 -3, scrCol / 4 -7, "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol / 4 -7, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol / 4 -7, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol / 4 -7, "|           |");
    mvprintw(scrLine / 2 +1, scrCol / 4 -7, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol / 4 -7, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol / 4 -7, "  '._____.'  ");

    mvprintw(scrLine / 2 -3, scrCol / 4 * 3 -7, "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol / 4 * 3 -7, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol / 4 * 3 -7, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol / 4 * 3 -7, "|           |");
    mvprintw(scrLine / 2 +1, scrCol / 4 * 3 -7, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol / 4 * 3 -7, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol / 4 * 3 -7, "  '._____.'  ");

    refresh();
}

void gunright(int scrLine, int scrCol){
    mvprintw(scrLine / 2 -3, scrCol / 2 - 28, "                     ________________________________, ");
    mvprintw(scrLine / 2 -2, scrCol / 2 - 28, "'===-----...__  __,-""  ]____[ _.----------,__________|");
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, "|             ""   /___________)||||||||||||)_)        ");
    mvprintw(scrLine / 2 , scrCol / 2 - 28,   "|                `-'(( ]        '----------`           ");
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "|  ___...--,_  `    ''                                 ");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28, "'''          \\`                                        ");

    refresh();
}

void gunleft(int scrLine, int scrCol){
    mvprintw(scrLine / 2 -3, scrCol / 2 - 28, " ,________________________________                     ");
    mvprintw(scrLine / 2 -2, scrCol / 2 - 28, "|__________,----------._ [____]  ""-,__  __...-----==='");
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, "        (_(||||||||||||)___________/   ''             |");
    mvprintw(scrLine / 2 , scrCol / 2 - 28,   "           `----------'        [ ))'-,                |");
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "                                ''    `,  _,--...___  |");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28, "                                        `/          '''");

    refresh();
}


int main()
{
    int scrLine, scrCol;
    char str[1024];

    initscr();
    raw();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, scrLine, scrCol);       // 获取标准屏幕的行/列数
    //move(scrLine / 2 - 1, scrCol / 2 - 1);   // 将光标移至屏幕中央
    //printw("Hello World!");

    //The title of our game is "Roulette" 我们的游戲名爲「輪盤賭」
    mvprintw(scrLine / 2 - 5, scrCol / 2 - 31, "__________                .__             __     __           ");
    mvprintw(scrLine / 2 - 4, scrCol / 2 - 31, "\\______   \\  ____   __ __ |  |    ____  _/  |_ _/  |_   ____  ");
    mvprintw(scrLine / 2 - 3, scrCol / 2 - 31, " |       _/ /  _ \\ |  |  \\|  |  _/ __ \\ \\   __\\   __\\_/ __ \\ ");
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 31, " |    |   \\(  <_> )|  |  /|  |__\\  ___/  |  |   |  |  \\  ___/ ");
    mvprintw(scrLine / 2 - 1, scrCol / 2 - 31, " |____|_  / \\____/ |____/ |____/ \\___  > |__|   |__|   \\___  >");
    mvprintw(scrLine / 2    , scrCol / 2 - 31, "        \\/                           \\/                    \\/ ");

    refresh();
    //1s
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mvprintw(scrLine / 2 + 3, scrCol / 2 - 10, "Press any key to start");
    refresh();
    getch();
    clear();
    refresh();

    smileface(scrLine, scrCol);
    std::this_thread::sleep_for(std::chrono::seconds(1));

//玩家操作（84-144行）， 你把这部分代码按自己的想法重新写一遍也可以， 我把输出改了就行
//
// User input for gun direction (Towards left (you) or right (AI) )


    mvprintw(scrLine /5 *4, scrCol /2 -24, "Please press [A] or [D] to pick and move the gun");//游戏前提示玩家选择左或右方向的枪
    mvprintw(scrLine /5 *4 + 2, scrCol /2 -24, "press [E] to shoot");
    refresh();
    



    char user_input = getch(); //获取玩家指令， 按下A或D表示选择左或右方向的枪，按下E表示射击

    while (user_input != 'a' && user_input != 'A' && user_input != 'd' && user_input != 'D'){ //判错用， 若玩家指令不为A或D，则提示重新输入
        for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
            mvprintw(scrLine /5 *4, scrCol /2 -24, "                                                ");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(scrLine /5 *4, scrCol /2 -24, "Please press [A] or [D] to pick and move the gun");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        user_input = getch();
    }
    
    while (true){//循环， 直到玩家输入指令为E， 则射击
        if(user_input == 'a' || user_input == 'A')//选择左方向（玩家）
        {
            gunleft(scrLine, scrCol);
        }
        else if(user_input == 'd' || user_input == 'D')//选择右方向（AI）
        {
            gunright(scrLine, scrCol);
        }
        else if(user_input == 'e' || user_input == 'E')//射击
        {
            mvprintw(scrLine / 2 + 5, scrCol / 2 - 10, "shoot!");
            refresh();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            clear();
            refresh();
            smileface(scrLine, scrCol);
            //Your code here to shoot the AI
            break; //输入E（射击）后中断循环
        }
        else{
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine /5 *4, scrCol /2 -24, "                                                ");
                mvprintw(scrLine /5 *4 + 2, scrCol /2 -24, "                  ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine /5 *4, scrCol /2 -24, "Please press [A] or [D] to pick and move the gun");
                mvprintw(scrLine /5 *4 + 2, scrCol /2 -24, "press [E] to shoot");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));

            }
        }
        user_input = getch();//获取玩家指令， 按下A或D表示选择左或右方向的枪，按下E表示射击
    }

//以上为玩家操作， 以下为AI操作
//
// AI code here to move the gun towards the player and shoot
//
//

    char comm = getch();
    if (comm == 'q')
    {
        mvprintw(scrLine / 2 + 5, scrCol / 2 - 10, "Goodbye!");
    }

    
    refresh();

    getch();
    endwin();
    return 0;
}
