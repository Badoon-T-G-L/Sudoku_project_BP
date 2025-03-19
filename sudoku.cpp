#include <iostream>
#include "clui.h"
#include <ctime>
#include <chrono>
#include <fstream>
#include <thread>
#include <iomanip>
#include <conio.h> 
#include <string.h>
#include <windows.h>
using namespace std;
using namespace this_thread;
using namespace chrono;
#define screen_rows get_window_rows()
#define screen_cols get_window_cols()
#define cursor_x_pos get_cursor_x()
#define cursor_y_pos get_cursor_y()


// sudoku tables

//easy
char sudoku_table_easy[13][13] = {'_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  '|', '5','0','0',' ','0','0','3',' ','0','6','0','|',
                                  '|', '0','3','0',' ','0','2','0',' ','0','0','5','|',
                                  '|', '0','0','4',' ','0','0','7',' ','0','0','5','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '0','9','7',' ','0','0','0',' ','0','0','3','|',
                                  '|', '0','0','3',' ','2','0','1',' ','9','0','0','|',
                                  '|', '8','0','0',' ','0','9','0',' ','0','7','0','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '0','0','9',' ','7','0','0',' ','6','0','0','|',
                                  '|', '8','0','0',' ','0','9','0',' ','0','7','0','|',
                                  '|', '0','8','0',' ','9','0','0',' ','0','0','4','|',
                                  '_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  };

// normal
char sudoku_table_normal[13][13] = {'_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  '|', '5','3','0',' ','0','7','0',' ','0','0','0','|',
                                  '|', '6','0','0',' ','1','9','5',' ','0','0','0','|',
                                  '|', '0','9','8',' ','0','0','0',' ','0','6','0','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '8','0','0',' ','0','6','0',' ','0','0','3','|',
                                  '|', '4','0','0',' ','8','0','3',' ','0','0','1','|',
                                  '|', '7','0','0',' ','0','2','0',' ','0','0','6','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '0','6','0',' ','0','0','0',' ','2','8','0','|',
                                  '|', '0','0','0',' ','4','1','9',' ','0','0','5','|',
                                  '|', '0','0','0',' ','0','8','0',' ','0','7','9','|',
                                  '_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  };

// hard
char sudoku_table_hard[13][13] = {'_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  '|', '0','0','5',' ','3','0','0',' ','0','0','0','|',
                                  '|', '8','0','0',' ','0','0','0',' ','0','2','0','|',
                                  '|', '0','7','0',' ','0','1','0',' ','5','0','0','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '0','0','0',' ','0','0','0',' ','0','0','0','|',
                                  '|', '4','0','0',' ','8','0','3',' ','0','0','1','|',
                                  '|', '0','0','0',' ','0','0','0',' ','0','0','0','|',
                                  '|','-','-','-','-','-','-','-','-','-','-','-','|',
                                  '|', '0','0','9',' ','0','2','0',' ','6','4','0','|',
                                  '|', '0','4','0',' ','0','0','0',' ','0','0','6','|',
                                  '|', '0','0','0',' ','0','0','5',' ','3','0','0','|',
                                  '_','_','_','_','_','_','_','_','_','_','_','_','_',
                                  };




bool haswon = false;
int difficulty_num;
static int diff_numbah = 0;
struct player_data
{
    
    string username;
    bool win_or_lose;
    int corrects = 0;
    int wrongs = 0;
    int wins = 0;
    int losses = 0;
    int score = 0;
    int time_elapsed; // needs some work (WORK)
};

player_data all_player_data[200];

//global variables
// keeps all the data of all players
fstream plr_dt("All_player_data.txt", ios::app);
// keeps the usernames
fstream plr_nms("player_usernames.txt", ios::app);
// file for saving
fstream svd_gm("Saved_game.txt", ios::app);
// file for saving the time mins
fstream time_sv_min("Saved_time_min.txt", ios::app);
// saving the time secs
fstream time_sv_sec("Saved_time_sec.txt", ios::app);

string current_username;
int corrects[100];
int wrongs[100];
int wins[100];
int losses[100];
// there needs to be one for time (WORK)
string player_usernames[100];


void put_in_array(player_data every_player[200], string CURRENT_USERNAME, int corrects, int wrongs, int score, int wins, int losses/* , time (WORK)*/)
{
   
}


void result_menu(string CURRENT_PLAYER)
{

    char c;
    c = getch();
    for(int i = 0; i < 8; i++)
    {
        delay(800);
        // need data to be entered here (WORK)
        switch (i)
        {
        
        case 0:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "--GAME STATUS--";
        break;
        case 1:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "Username:" << current_username;
            break;
        case 2:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            if (haswon)
            cout << "Status: " << "won";
            else
            cout << "Status: " << "lost";
            break;
        case 3:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "Score:";
            break;
        case 4:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "Correct Guesses:";
            break;
        case 5:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "Wrong Guesses:";
            break;
        case 6:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "Time elapsed:";
            break;
        case 7:
            delay(1000);
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2);
            cout << "thank you for playing!, press q to quit";
            break;
        }
        
    }

    c = getch();
    if(c == 109)
    {
        quit();
    }

}
void win()
{
    haswon = true;
    cursor_to_pos(screen_rows / 2, screen_cols / 2);
    change_color_rgb(0,255,10);
    cout << "You won!";
    delay(3000);
    clear_screen();
    result_menu(current_username);
}

void fail()
{
    haswon = false;
    cursor_to_pos(screen_rows / 2, screen_cols / 2);
    change_color_rgb(255,0,0);
    cout << "You failed!";
    delay(3000);
    clear_screen();
    result_menu(current_username);
}

void print_table()
{
    
    switch (diff_numbah)
    {
    case 1:
        for(int i = 0; i < 13; i++)
        {
            cursor_to_pos(screen_rows / 2 - 7 + i, screen_cols / 2);
            for(int j = 0; j < 13; j++)
            {   
                cout << sudoku_table_easy[i][j];
            }
            cout << endl;
        }
        break;
    case 2:
        for(int i = 0; i < 13; i++)
        {
            cursor_to_pos(screen_rows / 2 - 7 + i, screen_cols / 2);
            for(int j = 0; j < 13; j++)
            {   
                cout << sudoku_table_normal[i][j];
            }
            cout << endl;
        }
        break;
    case 3:
        for(int i = 0; i < 13; i++)
        {
            cursor_to_pos(screen_rows / 2 - 7 + i, screen_cols / 2);
            for(int j = 0; j < 13; j++)
            {   
                cout << sudoku_table_hard[i][j];
            }
            cout << endl;
        }
        break;
    }

}


void save_game(char Copy_table_save[13][13],int size, int minuets, int seconds)
{
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            svd_gm << Copy_table_save[i][j];
        }
        svd_gm << "\n";
    }
    time_sv_min << minuets;
    time_sv_sec << seconds;
    
}


bool breakout = false;
void sudoku(int diff_num, int mins, int secs)
{
    char copy_table[13][13];
    switch (diff_num)
    {
    case 1:
        for(int i = 0; i < 13; i++)
        {
            for(int j = 0; j < 13; j++)
            {
                copy_table[i][j] = sudoku_table_easy[i][j];
            }
        }
        break;
    
    case 2:
        for(int i = 0; i < 13; i++)
        {
            for(int j = 0; j < 13; j++)
            {
                copy_table[i][j] = sudoku_table_normal[i][j];
            }
        }
    break;

    case 3:
        for(int i = 0; i < 13; i++)
        {
            for(int j = 0; j < 13; j++)
            {
                copy_table[i][j] = sudoku_table_hard[i][j];
            }
        }
    break;
    }

    bool is_in_loop = true;



    if(_kbhit())
    {

        switch (_getch())
        {
        case 'q':
            breakout = true;
            break;
        
        case 's':
        save_game(copy_table,13,mins,secs);
        break;

        case 27:
        // pausing
        break;

        // input
        case '1':
        break;
        case '2':
        break;
        case '3':
        break;
        case '4':
        break;
        case '5':
        break;
        case '6':
        break;
        case '7':
        break;
        case '8':
        break;
        case '9':
        break;



        // movement
        case 72: // up
        cursor_up(1);
        break;
        case 75: //left
        cursor_backward(1);
        break;
        case 77: // right
        cursor_forward(1);
        break;
        case 80: // down
        cursor_down(1);
        break;
        }

    }
    


    


}


bool timer_active = true;
void main_game(int minuets, int loaded_seconds, bool isloaded,int initial_mins)
{
    // timer stuff
    int totalSeconds = minuets * 60;
    print_table();
    while(timer_active)
    {
        
            if(totalSeconds < 0 || breakout)
            {
                break;
            }
            const int q = 113;
            int displayMinutes;
            int displaySeconds;
            if(!isloaded)
            {
                displayMinutes = totalSeconds / 60;
                displaySeconds = totalSeconds % 60;
            }
            else
            {   displayMinutes = minuets;
                displaySeconds = loaded_seconds;
            }

            if(totalSeconds <= 10)
            {
                change_color_rgb(255,0,0);
            }
            cursor_to_pos(0, screen_cols / 2);
            cout << setw(2) << setfill('0') << displayMinutes << ":"
                << setw(2) << setfill('0') << displaySeconds << flush;
            sleep_for(seconds(1));
            --totalSeconds;
            sudoku(difficulty_num,displayMinutes,displaySeconds);
            

    }
        
      
        reset_color();
        clear_screen();
        fail();
        //win();
        

}

bool loaded_game;
void play_saved()
{
    loaded_game = true;
    char table_loaded[13][13];
    int seconds;
    int minuets;
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            svd_gm >> table_loaded[i][j];
        }
    }

    time_sv_min >> minuets;
    time_sv_sec >> seconds;

    main_game(minuets, seconds, loaded_game, 0);
}


void difficulty_menu()
{
    loaded_game = false;
    int minuets;
    int difficulty_choice;
    change_color_rgb(255 , 0, 0);
    cursor_to_pos(0, screen_cols / 2);

    for(int i = 1; i < 6; i++)
    {
        delay(50);
        switch (i)
        {
        case 1:
            change_color_rgb(132, 0, 255);
            cursor_to_pos(i, 0);
            cout << "Please choose a difficulty";
            break;
        case 2:
            change_color_rgb(5, 138, 0);
            cursor_to_pos(i, 0);
            cout << "1: Easy";
            break;
        case 3:
            change_color_rgb(232, 225, 19);
            cursor_to_pos(i, 0);
            cout << "2: Normal";
            break;
        case 4:
            change_color_rgb(199, 6, 6);
            cursor_to_pos(i, 0);
            cout << "3: Hard";
            break;
        case 5:
            change_color_rgb(132, 0, 255);
            cursor_to_pos(i, 0);
            cout << "Pick your difficulty by typing a number from 1 to 3:";
            break;
        }
    }

    reset_color();
    cursor_to_pos(5, 54);
    cin >> difficulty_choice;

    switch (difficulty_choice)
    {
    case 1:
        difficulty_num = 1;
        diff_numbah = 1;
        reset_color();
        clear_screen();
        minuets = 5;
        main_game(minuets, 0, loaded_game, minuets);
        break;
    case 2:
        diff_numbah = 2;
        difficulty_num = 2;
        reset_color();
        clear_screen();
        minuets = 3;
        main_game(minuets, 0, loaded_game, minuets); 
        break;
    case 3:
        diff_numbah = 3;
        difficulty_num = 3;
        reset_color();
        clear_screen();
        minuets = 2;
        main_game(minuets, 0, loaded_game,minuets); 
        break;
    }

}







void main_menu(string Current_USERNAME)
{
    int menu_choice;
    change_color_rgb(255, 255, 0);
    cursor_to_pos(0, screen_cols / 2);
    cout << "IN HIS SUBLIME NAME";
    change_color_rgb(17, 255, 0);
    cursor_to_pos(2, screen_cols / 2);
    cout << "LET'S PLAY SUDOKU";
    change_color_rgb(8, 0, 255);
    cursor_to_pos(3, screen_cols / 2);
    cout << "<Game options>";

    for(int i = 4; i < 10; i++)
    {
        delay(50);
        change_color_rgb(255, 0, 20);
        switch (i)
        {
        case 4:
        change_color_rgb(82, 56, 6);
        cursor_to_pos(i,0);
        cout << "You logged in as " << Current_USERNAME << endl;
        break;

        case 6:
            cursor_to_pos(i,0);
            cout << "1: Start a new game";
            break;
        case 7:
            cursor_to_pos(i,0);
            cout << "2: Play a Saved Game";
            break;
        case 8:
            cursor_to_pos(i,0);
            cout << "3: View the LeaderBoards";
            break;
        case 9: 
            cursor_to_pos(i,0);
            cout << "4: quit the game";
            break;
        }
    }

    cursor_to_pos(11,0);
    cout << "Press a number from 1 to 4:";
    cursor_to_pos(11,29);
    reset_color();
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
        reset_color();
        clear_screen();
        difficulty_menu();
        break;
    
    case 2:
        reset_color();
        clear_screen();
        play_saved();
        break;
    case 3:
        reset_color();
        clear_screen();
        cout << "leaderbord";
        break;
    case 4:
        reset_color();
        quit();
        break;

        
    }

}







void logging_in()
{
    string current_username;
    bool exists;
    string p_username;
    change_color_rgb(53, 230, 197);
    cursor_to_pos(screen_rows / 2, screen_cols / 2);
    cout << "Enter a username please:";
    cursor_to_pos(screen_rows / 2, screen_cols / 2 + 25);
    cin >> p_username;
    string line;
    current_username = p_username;

    // if it didn't exist, send an error and quit otherwise start the game
    ifstream file("player_usernames.txt");

    while(getline(file,line))
    {
        if(line == p_username)
        {
            exists = true;
            break;
        }
        else
        {
            exists = false;
        }
        
    }

    if(exists)
    {
        clear_screen();
        main_menu(current_username);
    }
    else
    {
        cursor_to_pos(screen_rows + 1,screen_cols / 2 - 5);
        change_color_rgb(255,0,0);
        cursor_to_pos(screen_rows / 2 + 1, screen_cols / 2 - 5);
        cout << "Username doesn't exist, please sign up.";
        delay(5000);
        reset_color();
        quit();
    }




    

    
}

void signing_up()
{
    
    string entered_username;
    cursor_to_pos(screen_rows / 2,screen_cols / 2);
    cout << "Please enter a username:";
    cursor_to_pos(screen_rows / 2,screen_cols / 2 + 26);
    cin >> entered_username;
    ofstream file("player_usernames.txt", ios::app);
    plr_nms << entered_username << "\n";
    current_username = entered_username;
    cursor_to_pos(screen_rows / 2 + 3,screen_cols / 2);

}


void entering_the_game()
{

    int choice;
    for(int i = 0; i < 5; i++)
    {
        change_color_rgb(53, 230, 197);
        delay(50);
        switch (i)
        {
        case 0:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2 - 10);
            cout << "Welcome to The sudoku game.";
            break;
        case 1:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2 - 20);
            cout << "1-Log-in";
            break;
        case 2:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2 - 20);
            cout << "2-Sign-up";
            break;
        case 3:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2 - 20);
            cout << "3-quit";
            break;
        case 4:
            cursor_to_pos(screen_rows / 2 + i, screen_cols / 2 - 20);
            cout << "Please enter a number from the ones above to do the said task:";
            break;
        }
    }
    reset_color();
    cursor_to_pos(screen_rows / 2 + 4, screen_cols / 2 + 43);
    cin >> choice;

    switch (choice)
    {
    case 1:
        reset_color();
        clear_screen();
        logging_in();
        break;
    case 2:
        reset_color();
        clear_screen();
        signing_up();
        break;
    case 3:
        reset_color();
        quit();
        break;
    
    default:
    cursor_to_pos(screen_rows / 2 + 5, screen_cols / 2);
    change_color_rgb(255, 0, 0);
    cout << "Incorrect number";
    delay(2000);
    reset_color();
    quit();
    break;
    }




}



int main()
{ 
    
    entering_the_game();
    getch();
    return 0;
}