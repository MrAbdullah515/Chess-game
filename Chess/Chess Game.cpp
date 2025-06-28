#include<iostream>
#include<time.h>
#include<fstream>
#include<Windows.h>
#include<math.h>
#include<conio.h>
using namespace std;
const int col = 8, row = 8;
char game_type, game_progress, h1, h2;
bool arr_p[8] = { 0,0,0,0,0,0,0,0 }, arr_P[8] = { 0,0,0,0,0,0,0,0 };
int col_enter, col_desired, row_enter, row_desired, turn = 0, counterR = 0, counterR2 = 0, counterK = 0, countersk = 0, counterR3 = 0, counterR4 = 0;
clock_t white_time = clock(), black_time = clock();
float clasical_time_w = 0, clasical_time_b = 0;
float time_in_sec(float time)
{
    time = time / CLOCKS_PER_SEC;
    if (game_type == 'r')   // for rapid
    {
        static float w_time = 600, b_time = 600;
        if (turn % 2 == 0)
        {
            w_time = (w_time - time) + 10;
            return w_time;
        }
        else
        {
            b_time = (b_time - time) + 10;
            return b_time;
        }
    }
    if (game_type == 'b')   // for blitz
    {
        static float w_time = 300, b_time = 300;
        if (turn % 2 == 0)
        {
            w_time = (w_time - time);
            return w_time;
        }
        else
        {
            b_time = (b_time - time);
            return b_time;
        }
    }
    if (game_type == 'c')            // for classical mode
    {
        if (turn % 2 == 0)
            clasical_time_w += time;
        else
            clasical_time_b += time;
    }
}
void time_dealing()
{
    if (turn % 2 == 0)
    {
        white_time = clock() - white_time;
        white_time = time_in_sec(white_time);
    }
    else
    {
        black_time = clock() - black_time;
        black_time = time_in_sec(black_time);
    }
}
void printboard(char arr[][col])
{
    cout << endl;
    for (int i = 0, k = 0, n = 8; i < 8; i++, n--, k++)
    {
        if (i == 0)
            cout << " _________________________________________" << endl;

        for (int w = 0; w < 8; w++)
        {
            if (w == 0)
            {
                cout << n;
                cout << "|    |";
            }
            else
            {
                cout << "    |";
            }
        }
        cout << endl;
        //increasing length;
        for (int w = 0, x = 0; w < 8; w++, x++)
        {
            if (w == 0)
            {
                int z = 0;
                cout << " |  " << arr[i][z] << " ";
                cout << "|";
            }
            else
            {

                cout << " " << arr[i][x] << "  |";
            }
        }
        cout << endl;
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
                cout << " ";

            cout << "|____";

            if (j == 7)
                cout << "|";
        }
        cout << endl;
    }
    cout << "   a     b    c   d    e    f    g    h";
    cout << endl;
}
void getmove(char a[], char c[], char arr[][col])
{
    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, 3);
     // hand shake
    if (turn % 2 == 0)
    {
        cout << " If White want to hand shake , press(h)";
        cin >> h1;
        if (h1 == 'h')
        {
            cout << " If Black want to hand shake , press(h)";
            cin >> h2;
        }
    }
    if (turn % 2 != 0)
    {
        cout << " If Black want to hand shake , press(h)";
        cin >> h2;
        if (h2 == 'h')
        {
            cout << " If white want to hand shake , press(h)";
            cin >> h1;
        }
    }
       // getting move if hand is not shaken
    if (h1 != 'h' || h2 != 'h')
    {
    move_taking:
        HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(colors, 4);
        cout << "Enter the goti location : ";
        for (int i = 0; i < 2; i++)
        {
            cin >> a[i];
            if (i == 0)
            {
                col_enter = static_cast<int>(a[i]) - 97;
            }
            else
            {
                row_enter = 7 - (static_cast<int>(a[i]) - 49);
            }
        }cout << " The selected piece is : " << arr[row_enter][col_enter] << endl;
        SetConsoleTextAttribute(colors, 6);
        cout << "Enter destination : ";
        for (int j = 0; j < 2; j++)
        {
            cin >> c[j];
            if (j == 0)
            {
                col_desired = static_cast<int>(c[j]) - 97;
            }
            else
            {
                row_desired = 7 - (static_cast<int>(c[j]) - 49);
            }
        }cout << " The entered distinction is : " << endl << endl;
    }
}
void goti_move(char arr[][col])
{
    swap(arr[row_enter][col_enter], arr[row_desired][col_desired]);
    arr[row_enter][col_enter] = 32;
    time_dealing();
    system("CLS");
    if (game_type == 'r' || game_type == 'b')
    {
        cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
        cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
    }
    else if (game_type == 'c')
    {
        cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
        cout << "Time taken by black till last move is : " << black_time << " seconds.";
    }
    printboard(arr);
    turn++;
}
void pawn_empassant(char arr[][col])
{
    swap(arr[row_enter][col_enter], arr[row_desired][col_desired]);
    arr[row_enter][col_desired] = 32;
    time_dealing();
    system("CLS");
    if (game_type == 'r' || game_type == 'b')
    {
        cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
        cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
    }
    else if (game_type == 'c')
    {
        cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
        cout << "Time taken by black till last move is : " << black_time << " seconds.";
    }
    printboard(arr);
    turn++;
}
void pawn_promo(char arr[][col])
{
    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, 8);
    cout << "\n\nYour pawn has been promoted";
    char alpha;
    if (turn % 2 == 1)
    {
        cout << "\n\tPress \"q\" for 'queen'\n\tPress \"r\" for 'rook'\n\tPress \"h\" for 'knight'\n\tPress \"b\" for 'bishop' :  ";
        do {
            cin >> alpha;
        } while (alpha != 'q' && alpha != 'r' && alpha != 'h' && alpha != 'b');
    }
    else
    {
        cout << "\n\tPress \"Q\" for 'queen'\n\tPress \"R\" for 'rook'\n\tPress \"H\" for 'knight'\n\tPress \"B\" for 'bishop' :  ";
        do {
            cin >> alpha;
        } while (alpha != 'Q' && alpha != 'R' && alpha != 'H' && alpha != 'B');
    }
    arr[row_desired][col_desired] = alpha;
    arr[row_enter][col_enter] = 32;
    time_dealing();
    turn++;
    system("Color 0A");
    printboard(arr);
}
void pawn(char arr[][col])
{
    if (turn % 2 == 0)
    {
        if (arr[row_enter][col_enter] == 'P' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
        {
            // pawn movement for 2  boxes in start
            if (arr[row_desired][col_desired] == 32 && row_enter == 6 && col_enter == col_desired && row_desired == 4)
            {
                int counter1 = fabs(row_enter - row_desired), counter2 = 0;
                for (int i = row_desired; i <= row_enter; i++)
                {
                    if (arr[i][col_enter] == 32)
                        counter2++;
                }
                if (counter1 == counter2)
                    goti_move(arr);
                arr_P[col_enter] = 1;
            }
            // simple pawn promotion 
            else if (arr[row_desired][col_desired] == 32 && row_enter == 1 && row_desired == 0 && col_enter == col_desired)
                pawn_promo(arr);
            // pawn promotion with goti cutting
            else if (arr[row_desired][col_desired] != 32 && row_desired == 0 && row_enter == 1)
            {
                if (col_desired == col_enter + 1)
                    pawn_promo(arr);
                else if (col_desired == col_enter - 1)
                    pawn_promo(arr);
            }
            // simple pawn movemwnt
            else if (arr[row_desired][col_desired] == 32 && col_enter == col_desired && row_desired == row_enter - 1)
                goti_move(arr);
            // killing of goti by pawn
            else if (arr[row_desired][col_desired] != 32 && row_desired == row_enter - 1)
            {
                if (col_desired == col_enter - 1)
                    goti_move(arr);
                else if (col_desired == col_enter + 1)
                    goti_move(arr);
            }
            else if (row_enter == 3 && row_desired == 2 && arr[row_desired][col_desired] == 32 && (col_desired == col_enter + 1 || col_desired == col_enter - 1) && arr_p[col_desired == 1])
                pawn_empassant(arr);
        }
    }
    else
    {
        if (arr[row_enter][col_enter] == 'p' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
        {
            // pawn movement for 2  boxes in start
            if (arr[row_desired][col_desired] == 32 && row_enter == 1 && col_enter == col_desired && row_desired == 3)
            {
                int counter1 = fabs(row_desired - row_enter), counter2 = 0;
                for (int i = row_enter; i <= row_desired; i++)
                {
                    if (arr[i][col_enter] == 32)
                        counter2++;
                }
                if (counter1 == counter2)
                    goti_move(arr);
                arr_p[col_enter] = 1;
            }
            // simple pawn promotion 
            else if (arr[row_desired][col_desired] == 32 && row_enter == 6 && row_desired == 7 && col_enter == col_desired)
                pawn_promo(arr);
            // pawn promotion with goti cutting
            else if (arr[row_desired][col_desired] != 32 && row_desired == 7 && row_enter == 6)
            {
                if (col_desired == col_enter + 1)
                    pawn_promo(arr);
                else if (col_desired == col_enter - 1)
                    pawn_promo(arr);
            }
            // simple pawn movement 
            else if (arr[row_desired][col_desired] == 32 && col_enter == col_desired && row_desired == row_enter + 1)
                goti_move(arr);
            // killing of goti by pawn
            else if (arr[row_desired][col_desired] != 32 && row_desired == row_enter + 1)
            {
                if (col_desired == col_enter - 1)
                    goti_move(arr);
                else if (col_desired == col_enter + 1)
                    goti_move(arr);
            }
            else if (row_enter == 4 && row_desired == 5 && arr[row_desired][col_desired] == 32 && (col_desired == col_enter + 1 || col_desired == col_enter - 1) && arr_P[col_desired])
                pawn_empassant(arr);
        }
    }
}
void rukh(char arr[][col])
{
    int l, s, counter1 = 0, counter2 = 0;
    if (row_enter == row_desired)            // for same row
    {
        if (col_enter > col_desired)
            l = col_enter, s = col_desired;
        else
            l = col_desired, s = col_enter;
        counter1 = fabs(col_enter - col_desired);
        for (int i = s; i <= l; i++)
        {
            if (arr[row_enter][i] == 32)
                counter2++;
        }
        if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'R' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
            }
            else
            {

                if (arr[row_enter][col_enter] == 'r' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
            }
        }
    }
    if (col_enter == col_desired)           // for same column
    {
        if (row_enter > row_desired)
            l = row_enter, s = row_desired;
        else
            l = row_desired, s = row_enter;
        counter1 = fabs(row_enter - row_desired);
        for (int i = s; i <= l; i++)
        {
            if (arr[i][col_enter] == 32)
                counter2++;
        }
        if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'R' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
            }
            else
            {
                if (arr[row_enter][col_enter] == 'r' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);

            }
        }
    }
}
void bishop(char arr[][col])
{
    if (turn % 2 == 0)
    {
        if (arr[row_enter][col_enter] == 'B')
        {
            int k = 0, z = 0, x = 0;
            k = row_enter - (row_desired + 1);
            int y = -((row_enter + 1) - row_desired);
            //loops for checking empty boxes
            for (int i = row_enter - 1, j = col_enter + 1; i >= row_desired + 1 && j <= col_desired - 1; i--, j++)//forward-writ
            {
                if (arr[i][j] == 32)
                    z = z + 1;

            }
            for (int i = row_enter + 1, j = col_enter - 1; i <= row_desired - 1 && j >= col_desired + 1; i++, j--)//backward-frm-writ
            {
                if (arr[i][j] == 32)
                    x = x + 1;
            }
            int t = 0;
            for (int i = row_enter - 1, j = col_enter - 1; i >= row_desired + 1 && j >= col_desired + 1; i--, j--)//forward-left
            {
                if (arr[i][j] == 32)
                    t = t + 1;

            }
            int v = 0;
            for (int i = row_enter + 1, j = col_enter + 1; i <= row_desired - 1 && j <= col_desired + 1; i++, j++)//backward-frm-left
            {
                if (arr[i][j] == 32)
                    v = v + 1;
            }
            if (arr[row_desired][col_desired] == 32)
            {
                if (arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'B' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'H')
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
            else if (arr[row_desired][col_desired] != 32)//goti maro(B)
            {
                if (arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'B' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'H')
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (arr[row_enter][col_enter] == 'b')
        {
            int s = 0, a = 0, b = 0, f = 0, y = 0, x = 0;
            s = -((row_enter + 1) - row_desired);
            f = row_enter - (row_desired + 1);//distance b/w two selcted boxes
            //loops for checking empty boxes
            for (int i = row_enter + 1, j = col_enter - 1; i <= row_desired - 1 && j >= col_desired + 1; i++, j--)//forward-left
            {
                if (arr[i][j] == 32)
                    a = a + 1;
            }
            for (int i = row_enter - 1, j = col_enter + 1; i >= row_desired + 1 && j <= col_desired - 1; i--, j++)//backward-left
            {
                if (arr[i][j] == 32)
                    y = y + 1;
            }
            for (int i = row_enter + 1, j = col_enter + 1; i <= row_desired - 1 && j <= col_desired - 1; i++, j++)//forward-right
            {
                if (arr[i][j] == 32)
                {
                    x = x + 1;
                }
            }
            for (int i = row_enter - 1, j = col_enter - 1; i >= row_desired + 1 && j >= col_desired + 1; i--, j--)//backward-right
            {
                if (arr[i][j] == 32)
                    b = b + 1;
            }
            if (arr[row_desired][col_desired] == 32)
            {
                if (arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'b' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'b')
                {
                    if (a == s || y == f || x == s || b == f)
                    {
                        // reverse + forward
                        if (row_desired == row_enter + 1 || row_desired == row_enter - 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 2 || row_desired == row_enter - 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 3 || row_desired == row_enter - 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 4 || row_desired == row_enter - 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 5 || row_desired == row_enter - 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 6 || row_desired == row_enter - 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 7 || row_desired == row_enter - 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 8 || row_desired == row_enter - 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
            else if (arr[row_desired][col_desired] != 32)//goti maro(b)
            {
                if (arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'b' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'b')
                {
                    if (a == s || y == f || x == s || b == f)
                    {
                        //reverse + forward
                        if (row_desired == row_enter + 1 || row_desired == row_enter - 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 2 || row_desired == row_enter - 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 3 || row_desired == row_enter - 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 4 || row_desired == row_enter - 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 5 || row_desired == row_enter - 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 6 || row_desired == row_enter - 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 7 || row_desired == row_enter - 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter + 8 || row_desired == row_enter - 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
        }
    }
}
bool checkmate(char arr[][col])
{
    bool b1 = 0, b2 = 0, b3 = 0, b4 = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    static int king_row, king_col;
    static int sking_row, sking_col;
    bool K_check = 0, d1_check = 0, d2_check = 0, d3_check = 0, d4_check = 0, dabas_check = 0;

    int b_rowfr = 0, b_colfr = 0;
    //king position;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (arr[i][j] == 'K')
            {
                king_row = i;
                king_col = j;
                break;
            }
        }
    }
    for (int i = king_row - 1, j = king_col + 1; i >= 0 && j <= 7; i--, j++)
    {
        if (arr[i][j] == 'b' || arr[i][j] == 'q')
        {
            b1 = 1;
            //  cout << "b1=" << b1;
            break;
        }
    }
    //forward left;
    for (int i = king_row - 1, j = king_col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (arr[i][j] == 'b' || arr[i][j] == 'q')
        {
            b2 = 1;
            // cout << "b2=" << b2;
            break;
        }
    }
    //backward right;
    for (int i = king_row + 1, j = king_col + 1; i <= 7 && j <= 7; i++, j++)
    {


        if (arr[i][j] == 'b' || arr[i][j] == 'q')
        {
            b3 = 1;
            //  cout << "b3=" << b3;
            break;
        }

    }
    //backward left;
    for (int i = king_row + 1, j = king_col - 1; i <= 7 && j >= 0; i++, j--)
    {

        if (arr[i][j] == 'b' || arr[i][j] == 'q')
        {
            b4 = 1;
            // cout << "b4=" << b4;
            break;
        }

    }
    //rukh up;
    for (int i = king_row - 1, j = king_col; i >= 0; i--)
    {
        if (arr[i][j] == 'r' || arr[i][j] == 'q')
        {
            r1 = 1;
        }
    }
    //rukh down;
    for (int i = king_row + 1, j = king_col; i <= 7; i++)
    {
        if (arr[i][j] == 'r' || arr[i][j] == 'q')
        {
            r2 = 1;
        }
    }
    //rukh right;
    for (int i = king_row, j = king_col + 1; j <= 7; j++)
    {
        if (arr[i][j] == 'r' || arr[i][j] == 'q')
        {
            r3 = 1;
        }
    }
    //rukh left;
    for (int i = king_row, j = king_col - 1; j >= 0; j--)
    {
        if (arr[i][j] == 'r' || arr[i][j] == 'q')
        {
            r4 = 1;
        }
    }
    //knight;
    if (arr[king_row - 2][king_col - 1] == 'h' || arr[king_row - 2][king_col + 1] == 'h')
        h1 == 1;
    if (arr[king_row + 1][king_col - 2] == 'h' || arr[king_row + 1][king_col + 2] == 'h')
        h2 == 1;
    if (arr[king_row + 2][king_col - 1] == 'h' || arr[king_row + 2][king_col + 1] == 'h')
        h3 == 1;
    if (arr[king_row - 1][king_col - 2] == 'h' || arr[king_row - 1][king_col + 2] == 'h')
        h4 == 1;
    if (b1 == 1 || b2 == 1 || b3 == 1 || b4 == 1 || r1 == 1 || r2 == 1 || r3 == 1 || r4 == 1 || h1 == 1 || h2 == 1 || h3 == 1 || h4 == 1)
    {
        K_check = 1;
        return 1;
    }
    else
    {
        return 0;
    }
}
void knight(char arr[][col])
{
    bool flag = 0;
    if (turn % 2 == 0)
    {
        if (arr[row_enter][col_enter] == 'H')
        {
            if (arr[row_desired][col_desired] == 32)
            {
                if (arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'B' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'H')
                {
                    //horizontal move
                    //reverse + forward
                    if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                    {
                        if (col_desired == col_enter + 2)
                            goti_move(arr);
                        else if (col_desired == col_enter - 2)
                            goti_move(arr);
                    }
                    //vertical move
                    //reverse + forward
                    else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                    {
                        if (col_desired == col_enter + 1)
                            goti_move(arr);
                        else if (col_desired == col_enter - 1)
                            goti_move(arr);
                    }

                }
            }
            //goti maro (H) not equal to space
            else if (arr[row_desired][col_desired] != 32)
            {
                if (arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'B' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'H')
                {
                    //horizontal move
                    //rverse + forward
                    if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                    {
                        if (col_desired == col_enter + 2)
                            goti_move(arr);
                        else if (col_desired == col_enter - 2)
                            goti_move(arr);
                    }
                    //vertical move
                    //reverse + forward
                    else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                    {
                        if (col_desired == col_enter + 1)
                            goti_move(arr);
                        else if (col_desired == col_enter - 1)
                            goti_move(arr);
                    }
                }
            }
        }
    }
    else
    {
        if (arr[row_enter][col_enter] == 'h')
        {
            if (arr[row_desired][col_desired] == 32)
            {
                if (arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'b' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'h')
                {
                    //horizontal move:
                    //reverse + forward
                    if (row_desired == row_enter + 1 || row_desired == row_enter - 1)
                    {
                        if (col_desired == col_enter + 2)
                            goti_move(arr);
                        else if (col_desired == col_enter - 2)
                            goti_move(arr);
                    }
                    //vertical move:
                    ///reverse + forward
                    else if (row_desired == row_enter + 2 || row_desired == row_enter - 2)
                    {
                        if (col_desired == col_enter + 1)
                            goti_move(arr);
                        else if (col_desired == col_enter - 1)
                            goti_move(arr);
                    }
                }
            }
            //goti maro (h) not equal to space
            else if (arr[row_desired][col_desired] != 32)
            {
                if (arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'b' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'h')
                {
                    //horizontal move:
                    //reverse + forward
                    if (row_desired == row_enter + 1 || row_desired == row_enter - 1)
                    {
                        if (col_desired == col_enter + 2)
                            goti_move(arr);
                        else if (col_desired == col_enter - 2)
                            goti_move(arr);
                    }
                    //vertical move:
                    //reverse + forward
                    else if (row_desired == row_enter + 2 || row_desired == row_enter - 2)
                    {
                        if (col_desired == col_enter + 1)
                            goti_move(arr);
                        else if (col_desired == col_enter - 1)
                            goti_move(arr);
                    }
                }
            }
        }
    }
}
void king(char arr[][col])
{
    if (col_enter == col_desired)
    {
        if (row_desired == row_enter - 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }
        }
        else if (row_desired == row_enter + 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
    }
    else if (row_enter == row_desired)
    {
        if (col_desired == col_enter - 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
        else if (col_desired == col_enter + 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
    }
    else if (row_desired == row_enter - 1)
    {
        if (col_desired == col_enter - 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
        else if (col_desired == col_enter + 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
    }
    else if (row_desired == row_enter + 1)
    {
        if (col_desired == col_enter - 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }

        }
        else if (col_desired == col_enter + 1)
        {
            if (turn % 2 == 0)
            {
                if (arr[row_enter][col_enter] == 'K' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'Q' && arr[row_desired][col_desired] != 'H' && arr[row_desired][col_desired] != 'B')
                    goti_move(arr);
                counterK = counterK + 1;
            }
            else
            {
                if (arr[row_enter][col_enter] == 'k' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'q' && arr[row_desired][col_desired] != 'h' && arr[row_desired][col_desired] != 'b')
                    goti_move(arr);
                countersk = countersk + 1;
            }
        }
    }

    /////////////////////////////////CASTLING//////////////////////////////////
    int space = 0;
    int s = 2;
    for (int i = 7, j = 5; i <= 7 && j <= 6; j++)
    {
        if (arr[i][j] == 32)
        {
            space = space + 1;
        }
    }
    int space2 = 0;
    int s2 = 3;
    for (int i = 7, j = 1; i <= 7 && j <= 3; j++)
    {
        if (arr[i][j] == 32)
        {
            space2 = space2 + 1;
        }
    }
    //lower case (k)
    int space3 = 0;
    int s3 = 2;
    for (int i = 0, j = 5; i <= 7 && j <= 6; j++)
    {
        if (arr[i][j] == 32)
        {
            space3 = space3 + 1;
        }
    }
    int space4 = 0;
    int s4 = 3;
    for (int i = 0, j = 1; i <= 7 && j <= 3; j++)
    {
        if (arr[i][j] == 32)
        {
            space4 = space4 + 1;
        }
    }
    if (turn % 2 == 0)
    {
        if (arr[row_enter][col_enter] == 'K' && (row_desired == 7 && col_desired == 6) || (row_desired == 7 && col_desired == 7))
        {
            if (counterK == 0 && arr[6][6] != 'h' && arr[6][2] != 'h' && arr[5][5] != 'h' && arr[5][3] != 'h' && arr[6][4] != 'h' && arr[6][5] != 'b' && arr[6][5] != 'q' && arr[5][6] != 'b' && arr[4][7] != 'b' && arr[4][7] != 'q' && arr[5][6] != 'q' && arr[6][3] != 'b' && arr[6][3] != 'q' && arr[5][2] != 'b' && arr[5][2] != 'q' && arr[4][1] != 'b' && arr[4][1] != 'q' && arr[3][0] != 'b' && arr[3][0] != 'q' && arr[6][4] != 'r' && arr[6][4] != 'q' && arr[5][4] != 'r' && arr[5][4] != 'q' && arr[4][4] != 'r' && arr[4][4] != 'q' && arr[3][4] != 'r' && arr[3][4] != 'q' && arr[2][4] != 'r' && arr[2][4] != 'q' && arr[1][4] != 'r' && arr[1][4] != 'q' && arr[0][4] != 'r' && arr[0][4] != 'q' && arr[6][5] != 'p' && arr[6][3] != 'p')
            {
                if (counterR == 0 && space == 2 && arr[7][7] == 'R')
                {
                    if (arr[6][6] != 'r' && arr[6][6] != 'q' && arr[5][6] != 'r' && arr[5][6] != 'q' && arr[4][6] != 'r' && arr[4][6] != 'q' && arr[3][6] != 'r' && arr[3][6] != 'q' && arr[2][6] != 'r' && arr[2][6] != 'q' && arr[1][6] != 'r' && arr[1][6] != 'q' && arr[0][6] != 'r' && arr[0][6] != 'q' && arr[6][7] != 'b' && arr[6][7] != 'q' && arr[6][7] != 'p' && arr[6][5] != 'p' && arr[6][4] != 'h' && arr[5][7] != 'h' && arr[6][5] != 'b' && arr[6][5] != 'q' && arr[5][4] != 'b' && arr[4][3] != 'q' && arr[4][3] != 'b' && arr[4][3] != 'q' && arr[3][2] != 'b' && arr[3][2] != 'q' && arr[2][1] != 'b' && arr[2][1] != 'q' && arr[1][0] != 'b' && arr[1][0] != 'q')
                    {
                        swap(arr[row_enter][col_enter], arr[7][6]);
                        swap(arr[7][7], arr[7][5]);
                        time_dealing();
                        system("CLS");
                        if (game_type == 'r' || game_type == 'b')
                        {
                            cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
                            cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
                        }
                        else if (game_type == 'c')
                        {
                            cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
                            cout << "Time taken by black till last move is : " << black_time << " seconds.";
                        }
                        printboard(arr);
                        turn++;
                    }
                }
            }
        }
        if (arr[row_enter][col_enter] == 'K' && (row_desired == 7 && col_desired == 2) || (row_desired == 7 && col_desired == 0))
        {
            if (counterK == 0 && arr[6][6] != 'h' && arr[6][2] != 'h' && arr[5][5] != 'h' && arr[5][3] != 'h' && arr[6][5] != 'b' && arr[6][5] != 'q' && arr[5][6] != 'b' && arr[4][7] != 'b' && arr[4][7] != 'q' && arr[5][6] != 'q' && arr[6][3] != 'b' && arr[6][3] != 'q' && arr[5][2] != 'b' && arr[5][2] != 'q' && arr[4][1] != 'b' && arr[4][1] != 'q' && arr[3][0] != 'b' && arr[3][0] != 'q' && arr[6][4] != 'r' && arr[6][4] != 'q' && arr[5][4] != 'r' && arr[5][4] != 'q' && arr[4][4] != 'r' && arr[4][4] != 'q' && arr[3][4] != 'r' && arr[3][4] != 'q' && arr[2][4] != 'r' && arr[2][4] != 'q' && arr[1][4] != 'r' && arr[1][4] != 'q' && arr[0][4] != 'r' && arr[0][4] != 'q' && arr[6][5] != 'p' && arr[6][3] != 'p')
            {
                if (counterR2 == 0 && space2 == 3 && arr[7][0] == 'R')
                {
                    if (arr[6][2] != 'r' && arr[6][2] != 'q' && arr[5][2] != 'r' && arr[5][2] != 'q' && arr[4][2] != 'r' && arr[4][2] != 'q' && arr[3][2] != 'r' && arr[3][2] != 'q' && arr[2][2] != 'r' && arr[2][2] != 'q' && arr[1][2] != 'r' && arr[1][2] != 'q' && arr[0][2] != 'r' && arr[0][2] != 'q' && arr[6][3] != 'p' && arr[6][1] != 'p' && arr[6][0] != 'h' && arr[5][3] != 'h' && arr[5][1] != 'h' && arr[6][4] != 'h' && arr[6][3] != 'b' && arr[6][3] != 'q' && arr[5][4] != 'b' && arr[5][4] != 'q' && arr[4][5] != 'b' && arr[4][5] != 'q' && arr[3][6] != 'b' && arr[3][6] != 'q' && arr[2][7] != 'b' && arr[2][7] != 'q' && arr[6][1] != 'b' && arr[6][1] != 'q' && arr[5][0] != 'b' && arr[5][0] != 'q')
                    {
                        swap(arr[row_enter][col_enter], arr[7][2]);
                        swap(arr[7][0], arr[7][3]);
                        time_dealing();
                        system("CLS");
                        if (game_type == 'r' || game_type == 'b')
                        {
                            cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
                            cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
                        }
                        else if (game_type == 'c')
                        {
                            cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
                            cout << "Time taken by black till last move is : " << black_time << " seconds.";
                        }
                        printboard(arr);
                        turn++;
                    }
                }
            }
        }
    }
    else
    {
        if (arr[row_enter][col_enter] == 'k' && (row_desired == 0 && col_desired == 6) || (row_desired == 0 && col_desired == 7))
        {
            if (countersk == 0 && arr[2][3] != 'H' && arr[2][5] != 'H' && arr[1][2] != 'H' && arr[1][6] != 'H' && arr[1][5] != 'B' && arr[1][5] != 'Q' && arr[2][6] != 'B' && arr[2][6] != 'Q' && arr[3][7] != 'B' && arr[3][7] != 'Q' && arr[1][3] != 'B' && arr[1][3] != 'Q' && arr[2][2] != 'B' && arr[2][2] != 'Q' && arr[3][1] != 'B' && arr[3][1] != 'Q' && arr[4][0] != 'B' && arr[4][0] != 'Q' && arr[1][4] != 'R' && arr[1][4] != 'Q' && arr[2][4] != 'R' && arr[2][4] != 'Q' && arr[3][4] != 'R' && arr[3][4] != 'Q' && arr[4][4] != 'R' && arr[4][4] != 'Q' && arr[5][4] != 'R' && arr[5][4] != 'Q' && arr[6][4] != 'R' && arr[6][4] != 'Q' && arr[7][4] != 'R' && arr[7][4] != 'Q' && arr[1][3] != 'P' && arr[1][5] != 'P')
            {
                if (counterR3 == 0 && space3 == 2 && arr[0][7] == 'r')
                {
                    if (arr[1][6] != 'R' && arr[1][6] != 'Q' && arr[2][6] != 'R' && arr[2][6] != 'Q' && arr[3][6] != 'R' && arr[3][6] != 'Q' && arr[4][6] != 'R' && arr[4][6] != 'Q' && arr[5][6] != 'R' && arr[5][6] != 'Q' && arr[6][6] != 'R' && arr[6][6] != 'Q' && arr[7][6] != 'R' && arr[7][6] != 'Q' && arr[1][7] != 'B' && arr[1][7] != 'Q' && arr[1][7] != 'P' && arr[1][5] != 'P' && arr[2][7] != 'H' && arr[2][5] != 'H' && arr[1][4] != 'H' && arr[1][5] != 'B' && arr[1][5] != 'Q' && arr[2][4] != 'B' && arr[2][4] != 'Q' && arr[3][3] != 'B' && arr[3][3] != 'Q' && arr[4][2] != 'B' && arr[4][2] != 'Q' && arr[5][1] != 'B' && arr[5][1] != 'Q' && arr[6][0] != 'B' && arr[6][0] != 'Q')
                    {
                        swap(arr[row_enter][col_enter], arr[0][6]);
                        swap(arr[0][7], arr[0][5]);
                        time_dealing();
                        system("CLS");
                        if (game_type == 'r' || game_type == 'b')
                        {
                            cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
                            cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
                        }
                        else if (game_type == 'c')
                        {
                            cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
                            cout << "Time taken by black till last move is : " << black_time << " seconds.";
                        }
                        printboard(arr);
                        turn++;
                    }
                }
            }
        }
        if (arr[row_enter][col_enter] == 'k' && (row_desired == 0 && col_desired == 2) || (row_desired == 0 && col_desired == 0))
        {
            if (countersk == 0 && arr[2][3] != 'H' && arr[2][5] != 'H' && arr[1][2] != 'H' && arr[1][6] != 'H' && arr[1][5] != 'B' && arr[1][5] != 'Q' && arr[2][6] != 'B' && arr[2][6] != 'Q' && arr[3][7] != 'B' && arr[3][7] != 'Q' && arr[1][3] != 'B' && arr[1][3] != 'Q' && arr[2][2] != 'B' && arr[2][2] != 'Q' && arr[3][1] != 'B' && arr[3][1] != 'Q' && arr[4][0] != 'B' && arr[4][0] != 'Q' && arr[1][4] != 'R' && arr[1][4] != 'Q' && arr[2][4] != 'R' && arr[2][4] != 'Q' && arr[3][4] != 'R' && arr[3][4] != 'Q' && arr[4][4] != 'R' && arr[4][4] != 'Q' && arr[5][4] != 'R' && arr[5][4] != 'Q' && arr[6][4] != 'R' && arr[6][4] != 'Q' && arr[7][4] != 'R' && arr[7][4] != 'Q' && arr[1][3] != 'P' && arr[1][5] != 'P')
            {
                if (counterR4 == 0 && space4 == 3 && arr[0][0] == 'r')
                {
                    if (arr[1][2] != 'R' && arr[1][2] != 'Q' && arr[2][2] != 'R' && arr[2][2] != 'Q' && arr[3][2] != 'R' && arr[3][2] != 'Q' && arr[4][2] != 'R' && arr[4][2] != 'Q' && arr[5][2] != 'R' && arr[5][2] != 'Q' && arr[6][2] != 'R' && arr[6][2] != 'Q' && arr[7][2] != 'R' && arr[7][2] != 'Q' && arr[1][3] != 'P' && arr[1][1] != 'P' && arr[2][1] != 'H' && arr[2][3] != 'H' && arr[1][4] != 'H' && arr[1][0] != 'H' && arr[1][3] != 'B' && arr[1][3] != 'Q' && arr[2][4] != 'B' && arr[2][4] != 'Q' && arr[3][5] != 'B' && arr[3][5] != 'Q' && arr[4][6] != 'B' && arr[4][6] != 'Q' && arr[5][7] != 'B' && arr[5][7] != 'Q' && arr[1][1] != 'B' && arr[1][1] != 'Q' && arr[2][0] != 'B' && arr[2][0] != 'Q')
                    {
                        swap(arr[row_enter][col_enter], arr[0][2]);
                        swap(arr[0][0], arr[0][3]);
                        time_dealing();
                        system("CLS");
                        if (game_type == 'r' || game_type == 'b')
                        {
                            cout << "Time remaining for white in seconds is : " << white_time << " seconds.";
                            cout << "\nTime remaining for black in seconds is : " << black_time << " seconds.";
                        }
                        else if (game_type == 'c')
                        {
                            cout << "Time taken by white till last move is : " << white_time << " seconds." << endl;
                            cout << "Time taken by black till last move is : " << black_time << " seconds.";
                        }
                        printboard(arr);
                        turn++;
                    }
                }
            }
        }
    }
}
void queen(char arr[][col])
{
    if (turn % 2 == 0)
    {
        if (arr[row_enter][col_enter] == 'Q' && arr[row_desired][col_desired] != 'P' && arr[row_desired][col_desired] != 'R' && arr[row_desired][col_desired] != 'K' && arr[row_desired][col_desired] != 'B' && arr[row_desired][col_desired] != 'H')
        {
            if (row_enter == row_desired || col_enter == col_desired)  // rukh walay moves
            {
                int l, s, counter1 = 0, counter2 = 0;
                if (row_enter == row_desired)            // for same row
                {
                    if (col_enter > col_desired)
                        l = col_enter, s = col_desired;
                    else
                        l = col_desired, s = col_enter;
                    counter1 = fabs(col_enter - col_desired);
                    for (int i = s; i <= l; i++)
                    {
                        if (arr[row_enter][i] == 32)
                            counter2++;
                    }
                    if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
                    {
                        if (turn % 2 == 0)
                            goti_move(arr);
                        else
                            goti_move(arr);
                    }
                }
                else if (col_enter == col_desired)           // for same column
                {
                    if (row_enter > row_desired)
                        l = row_enter, s = row_desired;
                    else
                        l = row_desired, s = row_enter;
                    counter1 = fabs(row_enter - row_desired);
                    for (int i = s; i <= l; i++)
                    {
                        if (arr[i][col_enter] == 32)
                            counter2++;
                    }
                    if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
                    {
                        if (turn % 2 == 0)
                            goti_move(arr);
                        else
                            goti_move(arr);
                    }
                }
            }
            else  // bishop walay moves
            {
                int k = 0, z = 0, x = 0;
                k = row_enter - (row_desired + 1);
                int y = -((row_enter + 1) - row_desired);
                //loops for checking empty boxes
                for (int i = row_enter - 1, j = col_enter + 1; i >= row_desired + 1 && j <= col_desired - 1; i--, j++)//forward-writ
                {
                    if (arr[i][j] == 32)
                        z = z + 1;

                }
                for (int i = row_enter + 1, j = col_enter - 1; i <= row_desired - 1 && j >= col_desired + 1; i++, j--)//backward-frm-writ
                {
                    if (arr[i][j] == 32)
                        x = x + 1;
                }
                int t = 0;
                for (int i = row_enter - 1, j = col_enter - 1; i >= row_desired + 1 && j >= col_desired + 1; i--, j--)//forward-left
                {
                    if (arr[i][j] == 32)
                        t = t + 1;

                }
                int v = 0;
                for (int i = row_enter + 1, j = col_enter + 1; i <= row_desired - 1 && j <= col_desired + 1; i++, j++)//backward-frm-left
                {
                    if (arr[i][j] == 32)
                        v = v + 1;
                }
                if (arr[row_desired][col_desired] == 32)
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
                else if (arr[row_desired][col_desired] != 32)//goti maro
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (arr[row_enter][col_enter] == 'q' && arr[row_desired][col_desired] != 'p' && arr[row_desired][col_desired] != 'r' && arr[row_desired][col_desired] != 'k' && arr[row_desired][col_desired] != 'b' && arr[row_desired][col_desired] != 'h')
        {
            if (row_enter == row_desired || col_enter == col_desired)  // rukh walay moves
            {
                int l, s, counter1 = 0, counter2 = 0;
                if (row_enter == row_desired)            // for same row
                {
                    if (col_enter > col_desired)
                        l = col_enter, s = col_desired;
                    else
                        l = col_desired, s = col_enter;
                    counter1 = fabs(col_enter - col_desired);
                    for (int i = s; i <= l; i++)
                    {
                        if (arr[row_enter][i] == 32)
                            counter2++;
                    }
                    if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
                    {
                        if (turn % 2 == 0)
                            goti_move(arr);
                        else
                            goti_move(arr);
                    }
                }
                else if (col_enter == col_desired)           // for same column
                {
                    if (row_enter > row_desired)
                        l = row_enter, s = row_desired;
                    else
                        l = row_desired, s = row_enter;
                    counter1 = fabs(row_enter - row_desired);
                    for (int i = s; i <= l; i++)
                    {
                        if (arr[i][col_enter] == 32)
                            counter2++;
                    }
                    if (counter1 == counter2 || (counter2 == counter1 - 1 && arr[row_desired][col_desired] != 32))
                    {
                        if (turn % 2 == 0)
                            goti_move(arr);
                        else
                            goti_move(arr);
                    }
                }
            }
            else  // bishop walay moves
            {
                int k = 0, z = 0, x = 0;
                k = row_enter - (row_desired + 1);
                int y = -((row_enter + 1) - row_desired);
                //loops for checking empty boxes
                for (int i = row_enter - 1, j = col_enter + 1; i >= row_desired + 1 && j <= col_desired - 1; i--, j++)//forward-writ
                {
                    if (arr[i][j] == 32)
                        z = z + 1;

                }
                for (int i = row_enter + 1, j = col_enter - 1; i <= row_desired - 1 && j >= col_desired + 1; i++, j--)//backward-frm-writ
                {
                    if (arr[i][j] == 32)
                        x = x + 1;
                }
                int t = 0;
                for (int i = row_enter - 1, j = col_enter - 1; i >= row_desired + 1 && j >= col_desired + 1; i--, j--)//forward-left
                {
                    if (arr[i][j] == 32)
                        t = t + 1;

                }
                int v = 0;
                for (int i = row_enter + 1, j = col_enter + 1; i <= row_desired - 1 && j <= col_desired + 1; i++, j++)//backward-frm-left
                {
                    if (arr[i][j] == 32)
                        v = v + 1;
                }
                if (arr[row_desired][col_desired] == 32)
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
                else if (arr[row_desired][col_desired] != 32)//goti maro
                {
                    if (z == k || x == y || t == k || v == y)
                    {
                        //reverse + forward
                        if (row_desired == row_enter - 1 || row_desired == row_enter + 1)
                        {
                            if (col_desired == col_enter + 1)
                                goti_move(arr);
                            else if (col_desired == col_enter - 1)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 2 || row_desired == row_enter + 2)
                        {
                            if (col_desired == col_enter + 2)
                                goti_move(arr);
                            else if (col_desired == col_enter - 2)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 3 || row_desired == row_enter + 3)
                        {
                            if (col_desired == col_enter + 3)
                                goti_move(arr);
                            else if (col_desired == col_enter - 3)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 4 || row_desired == row_enter + 4)
                        {
                            if (col_desired == col_enter + 4)
                                goti_move(arr);
                            else if (col_desired == col_enter - 4)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 5 || row_desired == row_enter + 5)
                        {
                            if (col_desired == col_enter + 5)
                                goti_move(arr);
                            else if (col_desired == col_enter - 5)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 6 || row_desired == row_enter + 6)
                        {
                            if (col_desired == col_enter + 6)
                                goti_move(arr);
                            else if (col_desired == col_enter - 6)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 7 || row_desired == row_enter + 7)
                        {
                            if (col_desired == col_enter + 7)
                                goti_move(arr);
                            else if (col_desired == col_enter - 7)
                                goti_move(arr);
                        }
                        else if (row_desired == row_enter - 8 || row_desired == row_enter + 8)
                        {
                            if (col_desired == col_enter + 8)
                                goti_move(arr);
                            else if (col_desired == col_enter - 8)
                                goti_move(arr);
                        }
                    }
                }
            }
        }
    }
}

void main()
{
    char arr[8][8];
    char load, file;
    ifstream fin, fin2, fin3, turnin, turnin2, turnin3, time_in, time_in2, time_in3, modein, modein2, modein3;
    ofstream fout, fout2, fout3, turnout, turnout2, turnout3, time_out, time_out2, time_out3, modeout, modeout2, modeout3;
    bool yes = 0;
    file_loading:
    cout << "In which file you want a game\n\tPress '1' for file 1\n\tPress '2' for file 2\n\tPress '3' for file 3 : ", cin >> file;
    if (file == '1')
    {
        modein.open("mode.txt"); // loading game mode
        modein >> game_type;
        if (game_type != 'c' && game_type != 'r' && game_type != 'b')
            cout << "Select game  mode : \n\t1 - Press 'c' for classical mode\n\t2 - Press 'r' for rapid mode\n\t3 - Press 'b' for blitz mode\n\t Enter choise : ", cin >> game_type;
        modein.close();
        turnin.open("number.txt"); // loading turn
        turnin >> turn;
        turnin.close();
        time_in.open("time.txt"); // loading time
        time_in >> white_time >> black_time;
        time_in.close();
        fin.open("array.txt"); // loading array
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fin >> load;
                if (load == '-')
                    arr[i][j] = 32;
                else
                    arr[i][j] = load;
            }
        }
        fin.close();
    }
    else if (file == '2')
    {
        modein2.open("mode2.txt"); // loading game mode
        modein2 >> game_type;
        if (game_type != 'c' || game_type != 'r' || game_type != 'b')
            cout << "Select game  mode : \n\t1 - Press 'c' for classical mode\n\t2 - Press 'r' for rapid mode\n\t3 - Press 'b' for blitz mode\n\t Enter choise : ", cin >> game_type;
        modein2.close();
        turnin2.open("number2.txt"); // loading turn
        turnin2 >> turn;
        turnin2.close();
        time_in2.open("time2.txt"); // loading time
        time_in2 >> white_time >> black_time;
        time_in2.close();
        fin2.open("array2.txt"); // loading array
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fin2 >> load;
                if (load == '-')
                    arr[i][j] = 32;
                else
                    arr[i][j] = load;
            }
        }
        fin2.close();
    }
    else if (file == '3')
    {
        modein3.open("mode3.txt"); // loading game mode
        modein3 >> game_type;
        if (game_type != 'c' || game_type != 'r' || game_type != 'b')
            cout << "Select game  mode : \n\t1 - Press 'c' for classical mode\n\t2 - Press 'r' for rapid mode\n\t3 - Press 'b' for blitz mode\n\t Enter choise : ", cin >> game_type;
        modein3.close();
        turnin3.open("number3.txt"); // loading turn
        turnin3 >> turn;
        turnin3.close();
        time_in3.open("time3.txt"); // loading time
        time_in3 >> white_time >> black_time;
        time_in3.close();
        fin3.open("array3.txt"); // loading array
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fin3 >> load;
                if (load == '-')
                    arr[i][j] = 32;
                else
                    arr[i][j] = load;
            }
        }
        fin3.close();
    }
    else
        goto file_loading;
    printboard(arr);
    char a[2], c[2];
    do
    {
        if (turn % 2 == 0)
        {
            yes = checkmate(arr);
            if (yes == 1)
            {
                system("CLS");
                cout << "\t\t\tKing is checkmate...!! GAMEOVER";
                cout << endl << "\n\t\t\t\tWinner is black";
                break;
            }
            cout << "\n\t\t\t\t\t\tWhite Turn\n" << endl;
        }
        else
            cout << "\n\t\t\t\t\t\tBlack Turn\n" << endl;
        system("Color 0A");
        move_taking:
        getmove(a, c, arr);
        if (h1 == 'h' && h2 == 'h')  // hand shaking
        {
            system("CLS");
            cout << endl; cout << endl;  cout << endl; cout << endl; cout << endl; cout << endl;
            cout << "\n\t\t\t\tHand Shake By both Players..!!!Game Draw" << endl;
            break;
        }
        if (arr[row_enter][col_enter] == 'p' || arr[row_enter][col_enter] == 'P')
            pawn(arr);
        else if (arr[row_enter][col_enter] == 'r' || arr[row_enter][col_enter] == 'R')
            rukh(arr);
        else if (arr[row_enter][col_enter] == 'h' || arr[row_enter][col_enter] == 'H')
            knight(arr);
        else if (arr[row_enter][col_enter] == 'q' || arr[row_enter][col_enter] == 'Q')
            queen(arr);
        else if (arr[row_enter][col_enter] == 'k' || arr[row_enter][col_enter] == 'K')
            king(arr);
        else if (arr[row_enter][col_enter] == 'b' || arr[row_enter][col_enter] == 'B')
            bishop(arr);
        if (white_time <= 0 || black_time <= 0)
            break;
        cout << "\nFor quit and save press 's' other-wise press 'q' for simply exit game with out saving and to continue press any other key : ", cin >> game_progress;
        if (game_progress == 's' || game_progress == 'q')
            break;
    } while (yes == 0);
    system("Color 74");
   
    if (game_progress == 's')
    {
        char file;
        file_number:
        cout << "In which file you want to save\n\tPress '1' for file 1\n\tPress '2' for file 2\n\tPress '3' for file 3 : ", cin >> file;
        if (file == '1')
        {
            fout.open("array.txt");  // saving array
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] == 32)
                        fout << "-";
                    else
                        fout << arr[i][j];
                }
                fout << endl;
            }
            fout.close();
            turnout.open("number.txt"); // saving turn
            turnout << turn;
            turnout.close();
            time_out.open("time.txt"); // saving time
            time_out << white_time << endl << black_time;
            time_out.close();
            modeout.open("mode.txt"); // saving game mode
            modeout << game_type;
            modeout.close();
        }
        else if (file == '2')
        {
            fout2.open("array2.txt");  // saving array
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] == 32)
                        fout2 << "-";
                    else
                        fout2 << arr[i][j];
                }
                fout2 << endl;
            }
            fout2.close();
            turnout2.open("number2.txt"); // saving turn
            turnout2 << turn;
            turnout2.close();
            time_out2.open("time2.txt"); // saving time
            time_out2 << white_time << endl << black_time;
            time_out2.close();
            modeout2.open("mode2.txt"); // saving game mode
            modeout2 << game_type;
            modeout2.close();
        }
        else if (file == '3')
        {
            fout3.open("array3.txt");  // saving array
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] == 32)
                        fout3 << "-";
                    else
                        fout3 << arr[i][j];
                }
                fout3 << endl;
            }
            fout3.close();
            turnout3.open("number3.txt"); // saving turn
            turnout3 << turn;
            turnout3.close();
            time_out3.open("time3.txt"); // saving time
            time_out3 << white_time << endl << black_time;
            time_out3.close();
            modeout3.open("mode3.txt"); // saving game mode
            modeout3 << game_type;
            modeout3.close();
        }
        else
            goto file_number;
    }
    cout << "\n\n\n\t\t\t Thanks for playing";
    _getch();
}