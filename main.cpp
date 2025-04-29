#include <bits/stdc++.h>
//#include <conio.h>
#include <ncurses.h>
#include <string.h>
#include <thread>    // Include for std::this_thread::sleep_for
#include <chrono>
using namespace std;

// 0 for AI(COMPUTER), 1 dor HUMAN

// Game constants
const int MaxHealth=5;
const int MaxBullets=4;
const int Items = 4;
const int NextBulletItem=1, DoubleDamItem=2, ChainItem=3, HealItem=4;
int MaxChamber=6;
int* Gun = NULL; // Changed to pointer for dynamic allocation
int Bullets=2;
int nowBullet;
int nowSpot;
int Reload=Bullets;
int PlayerDamage=1;
int Difficulty='1';
bool AIChained=false;

int scrLine, scrCol; // 获取屏幕 行 列 数
int my_energy = 4, ai_energy = 4; // 初始生命值为 4
char str[1024];

int msg; // 显示信息的行数

// Game structures
struct Player {
    int items[Items + 1]; //item counts 1:next bullet  2:double damage  3:chained  4:++hp
    int hp = MaxHealth;
} Players[3]; //Players[0] is AI and Players[1] is the person playing

void smileface(){
    mvprintw(scrLine / 2 -3, scrCol/ 4 - 20 , "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol/ 4 - 20, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol/ 4 - 20, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol/ 4 - 20, "|           |");
    mvprintw(scrLine / 2 +1, scrCol/ 4 - 20, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol/ 4 - 20, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol/ 4 - 20, "  '._____.'  ");
    mvprintw(scrLine / 2 +4, scrCol/ 4 - 20, "   /     \\   ");
    mvprintw(scrLine / 2 +5, scrCol/ 4 - 20, "  |  YOU  |   ");

    mvprintw(scrLine / 2 -3, scrCol /4 * 3 + 7, "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol /4 * 3 + 7, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol /4 * 3 + 7, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol /4 * 3 + 7, "|           |");
    mvprintw(scrLine / 2 +1, scrCol /4 * 3 + 7, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol /4 * 3 + 7, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol /4 * 3 + 7, "  '._____.'  ");
    mvprintw(scrLine / 2 +4, scrCol /4 * 3 + 7, "   /     \\   ");
    mvprintw(scrLine / 2 +5, scrCol /4 * 3 + 7, "  |  bot  |   ");

    mvhline(scrLine / 2 -5, 0, '_', scrCol);
    mvhline(scrLine / 2 +8, 0, '_', scrCol);


    refresh();
}

void gunright(){
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, "                     ________________________________, "); //length 56
    mvprintw(scrLine / 2 , scrCol / 2 - 28, "'===-----...__  __,-""  ]____[ _.----------,__________|  "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "|             ""   \\___________)||||||||||||)_)          ");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28, "|               /`-'(( ]        '----------`           ");
    mvprintw(scrLine / 2 +3, scrCol / 2 - 28, "|  ___...--,_ /`    ''                                 ");
    mvprintw(scrLine / 2 +4, scrCol / 2 - 28, "'''          \\`                                        ");

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mvprintw(scrLine / 2 -1, scrCol / 2 + 29, "/");
    mvprintw(scrLine / 2 , scrCol / 2 + 29, "-"); 
    mvprintw(scrLine / 2 +1, scrCol / 2 + 29, "\\");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //Animation for gun shooting

    //int dbt = 20; // distance_bullet_travel
    //for (int i = 0; i < dbt; i++){
    //    mvprintw(scrLine / 2 -2, scrCol / 2 + 30 + i, "-"); 
    //    mvprintw(scrLine / 2 -2, scrCol / 2 + 29 + i, " "); 
    //    refresh();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //}
    //mvprintw(scrLine / 2 -2, scrCol / 2 + 30 + dbt - 1, " ");
    mvprintw(scrLine / 2 -1, scrCol / 2 + 29, " ");
    mvprintw(scrLine / 2 , scrCol / 2 + 29, " "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 + 29, " ");
    refresh();
}

void gunleft(){
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, " ,________________________________                     ");
    mvprintw(scrLine / 2 , scrCol / 2 - 28, "|__________,----------._ [____]  ""-,__  __...-----==='  ");
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "        (_(||||||||||||)___________/   ''             |");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28,   "           `----------'        [ ))'-,                |");
    mvprintw(scrLine / 2 +3, scrCol / 2 - 28, "                                ''    `,  _,--...___  |");
    mvprintw(scrLine / 2 +4, scrCol / 2 - 28, "                                        `/          '''");

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mvprintw(scrLine / 2 -1, scrCol / 2 - 29, "\\");
    mvprintw(scrLine / 2 , scrCol / 2 - 30, "--"); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 29, "/");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    mvprintw(scrLine / 2 -1, scrCol / 2 - 29, " ");
    mvprintw(scrLine / 2 , scrCol / 2 - 30, "  "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 29, " ");
    refresh();
}

void energy(int my_energy, int ai_energy){
    for (int i = 0; i < 5; i++){
        move(scrLine / 2 - 7 - i, 0);
        clrtoeol();
    }
    refresh();
    for(int i = 0; i < my_energy; i++){
        mvprintw(scrLine / 2 -11, scrCol /4 - 20 + 8*i,"  /|   ");
        mvprintw(scrLine / 2 -10, scrCol /4 - 20 + 8*i," / |___");
        mvprintw(scrLine / 2 -9, scrCol /4 - 20 + 8*i,"/__   /");
        mvprintw(scrLine / 2 -8, scrCol /4 - 20 + 8*i,"   | / ");
        mvprintw(scrLine / 2 -7, scrCol /4 - 20 + 8*i,"   |/  ");
    }
    for(int i = 0; i < 41; i++){
        mvprintw(scrLine / 2 -12, scrCol/4 -21 + i, "_");
        mvprintw(scrLine / 2 -6, scrCol/4 -21 + i, "_");
        mvprintw(scrLine / 2 -12, scrCol/4 * 3 -21 + i, "_");
        mvprintw(scrLine / 2 -6, scrCol/4 * 3 -21 + i, "_");
        }
    for(int i = 0; i < 6; i++){
        mvprintw(scrLine / 2 -11 + i, scrCol/4 -21, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 -21 + 41, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 * 3 -21, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 * 3 -21 + 41, "|");
    }
    mvprintw(scrLine / 2 - 6, scrCol /4 - 20,"You have %d energy left", my_energy);
    for(int i = 0; i < ai_energy; i++){
        mvprintw(scrLine / 2 -11, scrCol /4 * 3 - 20 + 8*i,"  /|   ");
        mvprintw(scrLine / 2 -10, scrCol /4 * 3 - 20 + 8*i," / |___");
        mvprintw(scrLine / 2 -9, scrCol /4 * 3 - 20 + 8*i,"/__   /");
        mvprintw(scrLine / 2 -8, scrCol /4 * 3 - 20 + 8*i,"   | / ");
        mvprintw(scrLine / 2 -7, scrCol /4 * 3 - 20 + 8*i,"   |/  ");
    }
    mvprintw(scrLine / 2 - 6, scrCol /4 * 3 - 20,"Bot has %d energy left", ai_energy);
    
    refresh();
}

void DrawItem(){
    mvprintw(scrLine / 2 + 9, scrCol/ 4 - 20,"_ _  ___ _  _ __    ___ ___ ___ _  _");
    mvprintw(scrLine / 2 + 10, scrCol/ 4 - 20,"\\_/ |  | |  | |_|    |   |  |_  |\\/|");
    mvprintw(scrLine / 2 + 11, scrCol/ 4 - 20," |  |__| |__| | \\   _|_  |  |__ |  |");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 - 20,"__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 - 20, "|   __   |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 - 20, "|  /  \\  |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 - 20, "|    _/  |");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 - 20, "|    o   |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 - 20, "|_______%d|", Players[1].items[1]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 - 20, "[1]  Sharp");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 - 20, "       Eye");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 - 8, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 - 8, "|    __  |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 - 8, "|   /  \\ |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 - 8, "|--  __/ |");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 - 8, "|   /___ |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 - 8, "|_______%d|", Players[1].items[2]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 - 8, "[2] Double");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 - 8, "    Damage");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 + 4, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 + 4, "|  ____  |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 + 4, "| /\\   \\ |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 + 4, "||  \\   ||");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 + 4, "| \\__\\_/ |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 + 4, "|_______%d|", Players[1].items[3]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 + 4, "[3]    Ban");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 + 16, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 + 16, "|   /|   |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 + 16, "|  / |___|");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 + 16, "| /__+1 /|");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 + 16, "|    | / |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 + 16, "|____|/_%d|", Players[1].items[4]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 + 16, "[4] Re-");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 + 16, "    charge");
    
    mvvline(scrLine / 2 + 9, scrCol/ 4 + 28, '|', scrLine - (scrLine / 2 + 9));

    mvvline(scrLine / 2 + 9, scrCol/ 4 * 3 + 7, '|', scrLine - (scrLine / 2 + 9));

    mvprintw(scrLine / 2 + 11, scrCol/ 4 * 3 + 9, "Bot's item    Num");
    mvprintw(scrLine / 2 + 12, scrCol/ 4 * 3 + 9, "_________________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 * 3 + 9, "Sharp Eye      %d",Players[0].items[1]);
    mvprintw(scrLine / 2 + 14, scrCol/ 4 * 3 + 9, "Double Damage  %d",Players[0].items[2]);
    mvprintw(scrLine / 2 + 15, scrCol/ 4 * 3 + 9, "Chain          %d",Players[0].items[3]);
    mvprintw(scrLine / 2 + 16, scrCol/ 4 * 3 + 9, "Healing        %d",Players[0].items[4]);

    refresh();
}

// These two function are for testing
void Printtest(int Code){  // int Code: 1 for HUMAN, 0 for AI(COMPUTER)

    DrawItem();

    mvprintw(scrLine / 2 + 9, scrCol/ 4 + 30, "     ___ _  _ ___");
    mvprintw(scrLine / 2 + 10, scrCol/ 4 + 30,"|__|  |  |\\ |  |");
    mvprintw(scrLine / 2 + 11, scrCol/ 4 + 30,"|  | _|_ | \\|  |");

    mvprintw(scrLine / 2 + 13, scrCol/ 4 + 30,"[A] shoot yourself");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 + 30,"[D] shoot opponent");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 + 30,"[H] View the Introduction Paper");
    mvprintw(scrLine / 2 + 18, scrCol/ 4 + 30,"[I] View the Item Manual");

    refresh();


    energy(Players[1].hp, Players[0].hp); //Output the energy of both players
    //cout << endl << Players[0].hp << " " << Players[1].hp << " " << nowSpot << " " << nowBullet << endl;
    mvprintw(scrLine / 2 + 6, scrCol / 2 - 26, "Bullet number:     %d out of %d", nowSpot, MaxChamber);
    mvprintw(scrLine / 2 + 7, scrCol / 2 - 26, "Real bullets left: %d", nowBullet);
    refresh();

}  //Output current status including health and gun progress

void centerclear(int line){
    mvhline(line, scrCol / 4 - 6, ' ', scrCol /4 * 3 + 7 - scrCol /4 + 5);
    refresh();
}

void continuefunc(int line, int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    mvprintw(line, scrCol / 2 - 12, "Press [C] to continue...");
    int temp1 = getch();
    while (temp1 != 'c' && temp1 != 'C'){
        temp1 = getch();
    }
    refresh();
    clear();
    refresh();
}

void ItemManual(){
    int height = scrLine, width = scrCol;
    int starty = 0, startx = 0;
    WINDOW* new_win = newwin(height, width, starty, startx);
    mvwprintw(new_win, 1, 1, "[ Item Manual ]");
    mvwprintw(new_win, 3, 1, "Key Item Name      Description                                       Brief Description");
    mvwprintw(new_win, 5, 1, "[1] Sharp Eye      You have a sharp eye to see if next bullet is     next bullet REAL or FAKE");
    mvwprintw(new_win, 6, 1, "                   real or fake.");
    mvwprintw(new_win, 8, 1, "[2] Double Damage  After using the Double Damage Item, your next     -2 energy point on opponent");
    mvwprintw(new_win, 9, 1, "                   bullet will deal 2 damage if it is real.");
    mvwprintw(new_win, 11, 1,"[3] Ban            After using the Ban Item, your opponent will      ban 1 round");
    mvwprintw(new_win, 12, 1,"                   not opponent will not be able to take the next");
    mvwprintw(new_win, 13, 1,"                   round regardless of the result of this round.");
    mvwprintw(new_win, 15, 1,"[4] Recharge       After using the Recharge Item, your energy will   +1 energy point on yourself");
    mvwprintw(new_win, 16, 1,"                   add by 1.");

    mvwprintw(new_win, height-1, 1, "Press [ANY KEY] to close the Item Manual.");

    wrefresh(new_win);
    wgetch(new_win);
    delwin(new_win);
    clear();
}

void IntroductionPaper(){
    clear();
    refresh();

    mvprintw(msg - 2, scrCol / 2 - 15, "Welcome to the game Roulette!");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg, scrCol / 2 - 11, "The game is not hard.");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg + 2, scrCol / 2 - 32, "In this game, you will be facing a bot, which is your opponent.");
    refresh();
    continuefunc(scrLine / 2 + 6, 400);

    mvprintw(msg - 2, scrCol / 2 - 24, "You have a gun with a limited number of bullets.");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg, scrCol / 2 - 35, "Yor goal is to kill the bot by shooting the bullets at the bot's head.");
    refresh();
    continuefunc(scrLine / 2 + 6, 400);

    smileface();
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg - 1, scrCol / 2 - 25, "<- You sit at the leftside of the table");
    mvprintw(msg + 1, scrCol / 2 - 10, "Your opponent sit at the rightside ->");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg + 4, scrCol / 2 - 25, "Each of you have 5 energy points at the beginning.");
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    energy(5,5);
    refresh();
    continuefunc(scrLine / 2 + 6, 400);

    smileface();
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, "                     ________________________________, "); //length 56
    mvprintw(scrLine / 2 , scrCol / 2 - 28, "'===-----...__  __,-""  ]____[ _.----------,__________|  "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "|             ""   \\___________)||||||||||||)_)          ");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28, "|               /`-'(( ]        '----------`           ");
    mvprintw(scrLine / 2 +3, scrCol / 2 - 28, "|  ___...--,_ /`    ''                                 ");
    mvprintw(scrLine / 2 +4, scrCol / 2 - 28, "'''          \\`                                        ");
    energy(5,5);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    mvprintw(msg, scrCol / 2 - 25, "There is a gun on the table, loaded with bullets.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0);
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 40, "However, there are some FAKE bullets loaded in the gun, which casue no damage.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 31, "If one is shoot by real bullet, they will lose 1 energy point.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 25, "One will die if they lose all their energy points.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 30, "Hence, if the next bullet is FAKE, you should shoot yourself");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 40, "If you shoot your opponet with real bullet or shoot yourself with fake bullet,");
    mvprintw(msg + 2, scrCol / 2 - 30, "you will win this round and take the next round.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg+1);
    centerclear(msg);

    mvprintw(msg, scrCol / 2 - 40, "Otherwise, you will lose this round and your opponent will take the next round.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 
    centerclear(msg);

    mvprintw(msg - 1, scrCol / 2 - 25, "Let's have a try, suppose the next bullet is real.");
    mvprintw(msg + 1, scrCol / 2 - 20, "[A] shoot yourself  [D] shoot opponent");
    smileface();
    energy(5,5);
    refresh();
    int temp1 = getch();
    while (temp1 != 'a' && temp1 != 'A' && temp1 != 'd' && temp1 != 'D'){
        temp1 = getch();
    }
    centerclear(msg-1);
    centerclear(msg);
    if (temp1 == 'a' || temp1 == 'A'){
        mvprintw(msg-1, scrCol / 2 - 33, "You shoot yourself with real bullet, and you lose 1 energy point.");
        gunleft();
        mvprintw(msg, scrCol / 2 - 20, "Your opponents will take the next round.");
        mvprintw(scrLine / 2 +6, scrCol / 4 * 3 + 11, " /\\ ");
        mvprintw(scrLine / 2 +7, scrCol / 4 * 3 + 11, "/__\\");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        energy(4,5);
        continuefunc(scrLine / 2 + 5, 0);
    }
    else if (temp1 == 'd' || temp1 == 'D'){
        mvprintw(msg-1, scrCol / 2 - 33, "You shoot opponent with real bullet, and he loses 1 energy point.");
        gunright();
        mvprintw(msg, scrCol / 2 - 15, "You will take the next round.");
        mvprintw(scrLine / 2 +6, scrCol / 4 - 15, " /\\ ");
        mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "/__\\");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        energy(5,4);
        continuefunc(scrLine / 2 + 5, 0);
    }

    mvprintw(msg , scrCol / 2 - 10, "In this game,");
    mvprintw(msg +2, scrCol / 2 - 36, "You will have chance to choose the chamber with size ranges from 6 to 9,");
    mvprintw(msg +4, scrCol / 2 - 25, "as well as the number of REAL bullets in the chamber.");
    refresh();
    continuefunc(scrLine / 2 + 6, 0); 

    DrawItem();
    mvprintw(msg -2, scrCol / 2 - 33, "You will also have items to use, which may enhance your gameplay.");
    mvprintw(msg +2, scrCol / 2 - 35, "Your items will be displayed on the bottom-left corner of the screen.");
    mvprintw(msg +4, scrCol / 2 - 36, "In some situations, you may also need to notice your opponent's items.");
    
    mvprintw(msg , scrCol / 2 - 23, "If you wish to see the Item Manual, press [I].");

    mvprintw(scrLine / 2 + 6, scrCol / 2 - 12, "Press [C] to continue...");
    refresh();

    int temp2 = getch();
    while (temp2 != 'c' && temp2 != 'C' && temp2 != 'i' && temp2 != 'I'){
        temp2 = getch();
    }
    if (temp2 == 'i' || temp2 == 'I'){
        ItemManual();
    }
    clear();
    refresh();

    mvprintw(scrLine / 2 - 3, scrCol / 2 - 31,"    _        ______  _____     ____  ____  ________      _    ");
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 31," .-| |-.   .' ___  ||_   _|   |_   ||   _||_   __  |  .-| |-. ");
    mvprintw(scrLine / 2 - 1, scrCol / 2 - 31," \\     /  / .'   \\_|  | |       | |__| |    | |_ \\_|  \\     / ");
    mvprintw(scrLine / 2 , scrCol / 2 - 31,"|_     _| | |   ____  | |   _   |  __  |    |  _|    |_     _|");
    mvprintw(scrLine / 2 + 1, scrCol / 2 - 31," /     \\  \\ `.___]  |_| |__/ | _| |  | |_  _| |_      /     \\ ");
    mvprintw(scrLine / 2 + 2, scrCol / 2 - 31," '-|_|-'   `._____.'|________||____||____||_____|     '-|_|-' ");
    mvprintw(scrLine / 2 + 4, scrCol / 2 - 12,"\"Good Luck, Have Fun!\"");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    continuefunc(scrLine / 2 + 6, 0); 
    smileface();
    Printtest(1);
}

void DrawBullet(int num){ //Draw the bullet on the screen
    for(int i = 0; i < 9; i++){
        mvprintw(scrLine / 2 + 5, scrCol/ 2 + 29 - i * 3 ,"  ");
        mvprintw(scrLine / 2 + 6, scrCol/ 2 + 29 - i * 3 ,"  ");
        mvprintw(scrLine / 2 + 7, scrCol/ 2 + 29 - i * 3 ,"  ");
    }
    for(int i = 0; i < num; i++){ //Draw for Player1
        mvprintw(scrLine / 2 + 5, scrCol/ 2 + 29 - i * 3 ,"/\\");
        mvprintw(scrLine / 2 + 6, scrCol/ 2 + 29 - i * 3 ,"||");
        mvprintw(scrLine / 2 + 7, scrCol/ 2 + 29 - i * 3 ,"||");
    }
    refresh();
}

void PrintGun(){ //Output Gun Configuration
    for(int i=0;i<MaxChamber;i++){
            //cout << Gun[i] <<" ";
            mvprintw(scrLine /4*3 , scrCol / 2 - 8 + i*2, "%d ", Gun[i]);
        }
        //cout << endl;
    refresh();
}

void Real(){
    centerclear(msg);
    mvprintw(msg, scrCol / 2 - 3, "REAL!");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    centerclear(msg);
}

void Fake(){
    centerclear(msg);
    mvprintw(msg, scrCol / 2 - 3, "FAKE!");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    centerclear(msg);
}

void Damage(int Code, int Num){ //Account for the damage done
    Players[Code].hp-=Num; // Num Damage done to Players[Code] 
    nowSpot+=1; //Move to next bullet
    nowBullet-=1; //Remaining Bullet -1
    PlayerDamage=1; //Reset damage incase DoubleDamItem was used
    if (Code == 1){
        for (int i = 0; i < 3; i++){
        mvprintw(scrLine / 2 - 4 + i, scrCol/ 4 - 6 ,"-%d", Num);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mvprintw(scrLine / 2 - 4 + i, scrCol/ 4 - 6 ,"  ");
        refresh();
        }
    }
    else if(Code == 0){
        for (int i = 0; i < 3; i++){
        mvprintw(scrLine / 2 - 4 + i, scrCol/ 4 * 3 + 5 ,"-%d", Num);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mvprintw(scrLine / 2 - 4 + i, scrCol/ 4 * 3 + 5 ,"  ");
        refresh();
        }
    }
}

bool GameOver(){ //bool to check whether to end game
    if (Players[0].hp==0 || Players[1].hp==0) //If any player has zero health then game over
        return 0;//return false and stop the game
    return 1; //true then continue
}

double Probability(){ //Probability for our AI to judge its next move
    double probability=nowBullet/(double)(MaxChamber-nowSpot);
    return probability;
}

bool useHealItem(int Code){ //Checks whether Players[Code] has HealItems and use one is available
    if(Players[Code].items[HealItem]!=0 && Players[Code].hp<5){ //Cannot have health over 5
        Players[Code].items[HealItem]-=1;
        Players[Code].hp+=1;
        centerclear(msg);
        if (Code == 1){
            mvprintw(msg, scrCol / 2 - 12, "You have Recharged. (4)");
        }
        else if(Code == 0){
            mvprintw(msg, scrCol / 2 - 16, "Your opponent has Recharged. (4)");
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        centerclear(msg);
        if (Code == 1){
            for (int i = 0; i < 3; i++){
            mvprintw(scrLine / 2 - 2 - i, scrCol/ 4 - 6 ,"+1");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(scrLine / 2 - 2 - i, scrCol/ 4 - 6 ,"  ");
            refresh();
            }
        }
        else if(Code == 0){
            for (int i = 0; i < 3; i++){
            mvprintw(scrLine / 2 - 2 - i, scrCol/ 4 * 3 + 5 ,"+1");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(scrLine / 2 - 2 - i, scrCol/ 4 * 3 + 5 ,"  ");
            refresh();
            }
        }
        energy(Players[1].hp, Players[0].hp);
        return true;
    }
    return false;
}

bool useDoubleDamItem(int Code){ //Checks whether Players[Code] has DoubleDamItem
    if(Players[Code].items[DoubleDamItem]!=0){
        Players[Code].items[DoubleDamItem]-=1;
        centerclear(msg);
        if (Code == 1){
            mvprintw(msg, scrCol / 2 - 19, "You have used Double Damage Item. (2)");
        }
        else if(Code == 0){
            mvprintw(msg, scrCol / 2 - 23, "Your opponent has used Double Damage Item. (2)");
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        centerclear(msg);
        return true;
    }
    return false;
}

bool useChainItem(int Code){ //Checks whether Players[Code] has ChainItem
    if(Players[Code].items[ChainItem]!=0){
        Players[Code].items[ChainItem]-=1;
        centerclear(msg);
        if (Code == 1){
            mvprintw(msg, scrCol / 2 - 17, "You Ban your oppenet a round. (3)");
        }
        else if(Code == 0){
            mvprintw(msg, scrCol / 2 - 18, "Your opponent Ban you a round. (3)");
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        centerclear(msg);
        return true;
    }
    return false;
}

bool useNextBulletItem(int Code){ //Checks whether Players[Code] has NextBulletItem
    if(Players[Code].items[NextBulletItem]!=0){
        Players[Code].items[NextBulletItem]-=1;
        centerclear(msg);
        if (Code == 1){
            mvprintw(msg, scrCol / 2 - 15, "You have used Sharp Eye. (1)");
        }
        else if(Code == 0){
            mvprintw(msg, scrCol / 2 - 19, "Your opponent has used Sharp Eye. (1)");
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        centerclear(msg);
        return true;
    }
    return false;
}

bool isNextBullet(){ //Check if the next bullet is real
    if(Gun[nowSpot]==1) //Next is real
        return true;
    else
        return false;
}

void RandomItem(){ //For random generated items for Players
    int r1=rand()%4;
    Players[0].items[r1+1]+=1;
    int r2=rand()%4;
    Players[1].items[r2+1]+=1;
}

void InitializeItems(){ //To Initialize the array with 0s
    for(int j=1;j<=4;j++){
        Players[0].items[j]=0;
        Players[1].items[j]=0;
    }
    RandomItem(); //Each player starts with one item
}

void InitializeGun(int Num){ //Dynamic Array Allocation for Gun Configuration because Player can choose the chamber and bullet number
    if (Gun == NULL) { // Allocate gun chamber if not already allocated
        Gun = new int[MaxChamber];
    }
    for(int i=0;i<MaxChamber;i++){ // Initialize all chambers to 0s
        Gun[i]=0;
    }
    while(Num>0){ // Load bullets randomly
        int r=rand()%MaxChamber; 
        if(Gun[r]==0){
            Gun[r]=1;
            Num-=1;
        }
    }
}

void CleanupGun() { //Free the Dynamic Array Momeries
    if (Gun != NULL) {
        delete[] Gun;
        Gun = NULL;
    }
}

// int MediumAI() made by Zhang Yang
int MediumAI(){ //Game's Medium AI
    //Printtest(0);
    useHealItem(0); //Use HealItem whenever possible
    if (useNextBulletItem(0)){ //Use NextBulletItem whenever possible
        if (isNextBullet()){ //Check next Bullet, If Real
            gunleft(); // gun to left, shoot player
            Real();
            if (useDoubleDamItem(0)){ //If DoubleDamItem is present
                Damage(1,2); //Shoot Players[1] (Human) with two damage
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            else
                Damage(1,1); //Shoot Player[1] with one damage if no DoubleDamItem
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 1; //AI keeps shooting until return 0
        }
        else{ //Next bullet is fake
            gunright();
            Fake();
            nowSpot+=1; //AI shoot itself and move on to next bullet
            return 1;
        }
    }
    else if (useChainItem(0) && Probability()>=0.5){ //Use ChainItem when probability of the next bullet being real is greater or equal 50%
        gunleft(); 
        if (isNextBullet()){
            Real();
            Damage(1,1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 1;
        }
        else{
            Fake();
            nowSpot+=1;
            return 1;
        }
    }
    else{
        if (Probability()==1){ //All remaining bullets are real (Shoot Human)
            gunleft(); 
            if (useDoubleDamItem(0)){
                Real();
                Damage(1,2);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            else{
                Real();
                Damage(1,1);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            return 1;
        }
        if (Probability()>=0.5){ //Probability Greater or Equal to 50% (Shoot Human)
            gunleft(); // gun to left, shoot player.
            if (isNextBullet()){
                Real();
                Damage(1,1);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                return 1;
            }
            else{
                Fake();
                nowSpot+=1;
                return 0;
            }
        }
        else{
            gunright(); // gun to right, shoot AI.
            if (isNextBullet()){ //Probability lower than 50% (AI Shoot Itself)
                Real();
                Damage(0,1);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                return 0;
            }
            else{
                Fake();
                nowSpot+=1;
                return 1;
            }
        }
    }
}
// int easyAI() Made by Yap Ern Lynn & Liew Amanda Nicole Ann
int easyAI() {
	int randomItemToUse = rand() % 4;
	bool UsedDoubleDamage = false;
	bool UsedChainItem = false;
	switch(randomItemToUse) { //use a random weapon
		case 0: 
			if (useNextBulletItem(0)) {
				if (isNextBullet()) {
                    gunleft();
                    Real();
					Damage(1, 1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
					return 1; //shoot player
				}
				else {
                    gunright();
                    Fake();
					nowSpot += 1;
					return 1;
				}
			}
			break;
		case 1: 
			useDoubleDamItem(0); 
			UsedDoubleDamage = true;
			break;
		case 2: 
			useChainItem(0); 
			UsedChainItem = true;
			break;
		case 3: 
			useHealItem(0); 
			break;
	}
	
	if (Probability() < 0.5) { //shoot itself
        gunright();
		if (isNextBullet()) {
            Real();
			Damage(0, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
			if (UsedChainItem) {
				return 1; //skips player's turn
			}
			else{
				return 0; //back to player's turn
			}
		}
		else {
            Fake();
			nowSpot += 1;
			return 1;
		}
	}
	else { //shoot player
        gunleft();
		if (isNextBullet()) {
			Real();
			if (UsedDoubleDamage) {
				Damage(1, 2); //double damage
			}
			else {
				Damage (1, 1); //normal damage
			}
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
			return 1;
		}
		else {
            Fake();
			nowSpot += 1;
			if (UsedChainItem) {
				return 1; //skips player's turn
			}
			else {
				return 0; //back to player's turn
			}
		}
	}
}
// int HardAI() made by Lu Ho Tin
int HardAI(){
    int accuracy[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
    int random = rand() % 100;
    int currentaccuracy = accuracy[nowSpot];
    bool shoot;
    if(random < currentaccuracy) {
        shoot=isNextBullet();
    } else {
        shoot!=isNextBullet();
    }
    if(shoot){
        gunleft(); // gun to left, shoot player.
        if(isNextBullet()){
            Real();
            Damage(1,1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 1; //打中玩家继续回合
        }
        else{
            Fake();
            nowSpot++;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            return 0;
        }
    }
    else{
        gunright(); // gun to right, shoot AI.
        if(isNextBullet()){
            Real();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            Damage(0,1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 0;
        }
        else{
            Fake();
            nowSpot++;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            return 1;
        }
    }
}

int Human(){
    char userInput;
    nodelay(stdscr, TRUE);
    while(true){
        userInput = getch();
        if (userInput != ERR) {
            break;
        }
        mvprintw(scrLine / 2 +6, scrCol / 4 - 15, " /\\ ");
        mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "/__\\");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        userInput = getch();
        if (userInput != ERR) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        mvprintw(scrLine / 2 +6, scrCol / 4 - 15, "    ");
        mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "    ");
        refresh();
        userInput = getch();
        if (userInput != ERR) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        userInput = getch();
        if (userInput != ERR) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    nodelay(stdscr, FALSE);
    if(userInput=='d' || userInput=='D'){ //ShootAI
        gunright();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if(isNextBullet()){
            Real();
            Damage(0,PlayerDamage);
            AIChained=false;
            return 1;
        }
        else{
            Fake();
            nowSpot+=1;
            PlayerDamage=1;
            if (AIChained){
                AIChained=false;
                return 1;
            }
            return 0;
        }
    }
    else if(userInput=='a' || userInput=='A'){ //ShootYourself
        gunleft();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if(isNextBullet()){
            Real();
            Damage(1,PlayerDamage);
            if (AIChained){
                AIChained=false;
                return 1;
            }
            return 0;
        }
        else{
            Fake();
            nowSpot+=1;
            PlayerDamage=1;
            AIChained=false;
            return 1;
        }
    }
    else if(userInput=='1'){ //Use Item[1] NextBulletItem
        if(!useNextBulletItem(1)){
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(msg, scrCol / 2 - 6, "No Sharp Eye");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(msg, scrCol / 2 - 6, "            ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        else{
            if(isNextBullet()){
                mvprintw(msg, scrCol / 2 - 10, "Next Bullet is REAL!");
                refresh();
            }
            else{
                mvprintw(msg, scrCol / 2 - 10, "Next Bullet is FAKE!");
                refresh();
            }
        }
        return 1;
    }
    else if(userInput=='2'){ //Use Item[2] DoubleDamItem
        if(!useDoubleDamItem(1)){
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(msg, scrCol / 4 - 8, "No Double Damage Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(msg, scrCol / 4 - 8, "                     ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        else{
            PlayerDamage=2;
        }
        return 1;
    }
    else if(userInput=='3'){ //Use Item[3] ChainItem
        if(!useChainItem(1)){
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(msg, scrCol / 2 - 6, "No Ban Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(msg, scrCol / 4 - 6, "            ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        AIChained=true;
        return 1;
    }
    else if(userInput=='4'){ //Use Item[4] HealItem
        if(!useHealItem(1)){
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine / 2 + 22, scrCol / 2 - 8, "No Recharge Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine / 2 + 22, scrCol / 2 - 8, "                ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        return 1;
    }
    else if (userInput=='h' || userInput=='H'){
        IntroductionPaper();
        return 2;
    }
    else if (userInput=='i' || userInput=='I'){
        ItemManual();
        smileface();
        Printtest(1);
        return 2;
    }
    else
        return 2;
}

void ChangeChamber(){ //Player choose their own Chamber Size and Bullet Number
//Choose Chamber Size
    centerclear(msg);
    mvprintw(msg, scrCol / 2 - 15, "Choose Chamber Size (6-9):");
    refresh();
	int temp = getch()-'0';

    while(temp<6 || temp>9){
        if (temp == 'i' || temp == 'I'){
            IntroductionPaper();
        }
        else if (temp == 'h' || temp == 'H'){
            ItemManual();
        }
        else{
            centerclear(msg);
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(msg, scrCol / 2 - 4, "Invalid");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(msg, scrCol / 2 - 4, "       ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            mvprintw(msg, scrCol / 2 - 15, "Choose Chamber Size (6-9):");
            refresh();
        }
        temp = getch()-'0';
    }
	if (temp>=6 && temp<=9){ //Min 6 and Max 9
		MaxChamber = temp;
		//cout << MaxChamber << endl;
        mvprintw(msg, scrCol / 2 - 15, "Choose Chamber Size (6-9): %d", MaxChamber);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        centerclear(msg);
        refresh();
	}

//Choose Bullets Number
    centerclear(msg);
    mvprintw(msg, scrCol / 2 - 15, "Choose REAL Bullets Number (2-5):");
    refresh();
	temp = getch()-'0';

    while(temp<2 || temp>5){
        centerclear(msg);
        for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
            mvprintw(msg, scrCol / 2 - 4, "Invalid");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(msg, scrCol / 2 - 4, "       ");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        mvprintw(msg, scrCol / 2 - 15, "Choose REAL Bullets Number (2-5):");
        refresh();
        temp = getch()-'0';
    }

	if (temp>=2 && temp<=5){ //Min 2 and Max 5
		Bullets = temp;
		//cout << Bullets << endl;
        mvprintw(msg, scrCol / 2 -15, "Choose REAL Bullets Number (2-5): %d", Bullets);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        centerclear(msg);
        refresh();
	}
}

int main(){

    //设置渲染画面
    initscr();
    raw();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, scrLine, scrCol);       // 获取标准屏幕的行/列数
    msg = scrLine / 2 -2;
    mvprintw(scrLine / 2 - 5, scrCol / 2 - 31, "__________                .__             __     __           ");
    mvprintw(scrLine / 2 - 4, scrCol / 2 - 31, "\\______   \\  ____   __ __ |  |    ____  _/  |_ _/  |_   ____  ");
    mvprintw(scrLine / 2 - 3, scrCol / 2 - 31, " |       _/ /  _ \\ |  |  \\|  |  _/ __ \\ \\   __\\   __\\_/ __ \\ ");
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 31, " |    |   \\(  <_> )|  |  /|  |__\\  ___/  |  |   |  |  \\  ___/ ");
    mvprintw(scrLine / 2 - 1, scrCol / 2 - 31, " |____|_  / \\____/ |____/ |____/ \\___  > |__|   |__|   \\___  >");
    mvprintw(scrLine / 2    , scrCol / 2 - 31, "        \\/                           \\/                    \\/ ");

    refresh();
    //1s
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mvprintw(scrLine / 2 + 3, scrCol / 2 - 12, "Press [ANY KEY] to start");
    refresh();
    getch();

    clear();
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 12, "Watch the introduction?");
    mvprintw(scrLine / 2, scrCol / 2 - 28, "(It teaches you how to play, press Y for yes, N for no)");
    mvprintw(scrLine / 2 + 2, scrCol / 2 - 12, "[Y] Yes");
    mvprintw(scrLine / 2 + 4, scrCol / 2 - 12, "[N] No");
    refresh();
    int temp3 = getch();
    while(temp3!='Y' && temp3!='y' && temp3!='N' && temp3!='n'){
        temp3 = getch();
    }
    if (temp3=='Y' || temp3=='y'){
        IntroductionPaper();
    }

    clear();
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 20, "Choose the difficulty you want to play:");
    mvprintw(scrLine / 2 - 1, scrCol / 2 - 20, "(Please press corresponding key)");
    mvprintw(scrLine / 2 + 1, scrCol / 2 - 20, "[1] Easy");
    mvprintw(scrLine / 2 + 2, scrCol / 2 - 20, "[2] Moderate");
    mvprintw(scrLine / 2 + 3, scrCol / 2 - 20, "[3] Hard");
    refresh();
    Difficulty=getch();
    while (Difficulty!= '1' && Difficulty!= '2' && Difficulty!= '3'){
        for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
            move(scrLine / 2 + 4, 0);
            clrtoeol();
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(scrLine / 2 + 4, scrCol / 2 - 10, "Invalid input, please press corresponding key (1~3)");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        refresh();
        Difficulty=getch();
    }
    clear();
    refresh();
    switch(Difficulty){ // just trying to use switch case, yet can be replaced by if-else
        case '1':
            mvprintw(scrLine / 2, scrCol / 2 - 10, "You choose Easy mode");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case '2':
            mvprintw(scrLine / 2, scrCol / 2 - 12, "You choose Moderate mode");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case '3':
            mvprintw(scrLine / 2, scrCol / 2 - 10, "You choose Hard mode");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
    }
    clear();
    smileface();

    srand(time(NULL)); //Random Time Seed
    InitializeItems();
    while(GameOver()){
        RandomItem();
        ChangeChamber();
        DrawBullet(MaxChamber);
        Reload=Bullets;
        nowBullet=Bullets;
        nowSpot=0;
        InitializeGun(Reload);
        //PrintGun();
        //game logic
        while(nowBullet>0 && nowSpot<MaxChamber){
            int Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                if(Move==1)
                    //cout << "HUMAN:";
                    mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                    mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOUR round");
                    mvprintw(scrLine / 2 +6, scrCol / 4 * 3 + 11, "    ");
                    mvprintw(scrLine / 2 +7, scrCol / 4 * 3 + 11, "    ");
                    refresh();
                    Printtest(1);
                Move=Human();
                DrawBullet(MaxChamber-nowSpot);
            }
            Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                //cout << "AI:";
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "Bot's round");
                mvprintw(scrLine / 2 +6, scrCol / 4 - 15, "    ");
                mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "    ");
                mvprintw(scrLine / 2 +6, scrCol / 4 * 3 + 11, " /\\ ");
                mvprintw(scrLine / 2 +7, scrCol / 4 * 3 + 11, "/__\\");
                refresh();
                if (Difficulty == '1'){
                    Move=easyAI();
                }
                else if (Difficulty == '2'){
                    Move=MediumAI();
                }
                else if (Difficulty == '3'){
                    Move=HardAI();
                }
                DrawBullet(MaxChamber-nowSpot);
                Printtest(0);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            if(Players[0].hp<=0){
                //cout << "You win!";
                DrawBullet(MaxChamber-nowSpot);
                Printtest(0);
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOU WIN!");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                clear();
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOU WIN!");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                mvprintw(scrLine / 2 -4, scrCol / 2 - 14, "We have a surprise for you!");
                refresh();
                continuefunc(scrLine + 2, 0);
                int starttxt = 1;
                int endtxt = 21;

                for (int ii = 0; ii < 4; ++ii){
                    if (ii == 1) {
                        starttxt = 19;
                        endtxt = 21;
                    }
                    if (ii == 3) {
                        starttxt = 19;
                        endtxt = 19;
                    }
                    for (int i = starttxt; i <= endtxt; ++i) {
                        // Specify the path to the file
                        std::string filePath = "txt/t" + std::to_string(i) + ".txt";
                        
                        // Create an ifstream object to read from the file
                        std::ifstream inputFile(filePath);
                        
                        // Check if the file opened successfully
                        if (!inputFile) {
                            mvprintw(scrLine / 2 + 3, scrCol / 2 - 10, "Unable to open");
                            refresh();
                            getch();
                            clear();
                            endwin();
                            return 1; // Return an error code
                        }
                        
                        // Read from the file
                        std::string line;
                        int j = 0;
                        while (std::getline(inputFile, line)) {
                            mvprintw(scrLine / 2 - 17 + j, scrCol/ 2 - 25, line.c_str());
                            refresh();
                            j++;
                        }

                        
                        // Close the file
                        inputFile.close();
                        std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                clear();
                mvprintw(scrLine / 2 , scrCol/ 2 - 16,"Thank you for playing our game!");
                mvprintw(scrLine / 2 + 6 , scrCol/ 2 - 13,"Press [ANY KEY] to quit...");
                refresh();
                getch();
                endwin();
                return 1;
            }
            if(Players[1].hp<=0){
                //cout  << "You lose!";
                
                Printtest(0);
                mvprintw(scrLine / 2 -4, scrCol / 2 - 5, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 5, "YOU LOSE!");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                clear();
                mvprintw(scrLine / 2 -4, scrCol / 2 - 5, "YOU LOSE!");
                refresh();
                mvprintw(scrLine / 2 - 2, scrCol / 2 - 25, "However if you win, you will receive a surprise!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                mvprintw(scrLine / 2 , scrCol / 2 - 35, "You may first quit and play again, if you want to see the surprise :)");
                mvprintw(scrLine / 2 + 6 , scrCol/ 2 - 13,"Press [ANY KEY] to quit...");
                refresh();
                getch();
                endwin();
                return 0;
            }
        }
        Printtest(1);
        //cout << "Bullets Finished, Reload The Next Gun" << endl;
        for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
            mvprintw(msg, scrCol / 2 - 20, "Bullets Finished, Reload The Next Gun");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mvprintw(msg, scrCol / 2 - 20, "                                     ");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        mvprintw(msg, scrCol / 2 - 20, "Bullets Finished, Reload The Next Gun");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        mvprintw(msg, scrCol / 2 - 20, "                                     ");
        refresh();
        CleanupGun();   
    }
    getch();
    endwin();
    return 0;
}

// g++ -o 3 main.cpp -lncurses
