#include <iostream>
#include <vector>
using namespace std;
int count = 0;
class game
{
private:
    vector<pair<char, int>> row_temp;
    pair<char, int> temp;

public:
    vector<vector<pair<char, int>>> arr;
    void play(char c)
    {
        int k;
        cin >> k;
        k--;
        if (k < 9 && k >= 0 && arr[k / 3][k % 3].second == 0)
        {
            temp = {c, 1};
            arr[k / 3][k % 3] = temp;
        }
        else
        {
            cout << "invalid move\n";
            play(c);
        }
    }
    void initiate()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                temp.first = '1' + (char)(3 * i + j);
                temp.second = 0;
                row_temp.push_back(temp);
            }
            arr.push_back(row_temp);
            row_temp.clear();
        }
    }
    void board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << " " << arr[i][j].first;
                if (j < 2)
                    cout << "  | ";
            }
            if (i < 2)
            {
                cout << "\n---------------";
            }
            cout << endl;
        }
    }
    char checkifgameisover()
    {
        int j = 0;
        for (int i = 0; i < 9; i++)
        {
            j += arr[i / 3][i % 3].second;
        }
        if (j >= 5)
        {
            for (int i = 0; i < 3; i++)
            {
                if (arr[i][0].first == arr[i][1].first && arr[i][1].first == arr[i][2].first)
                {
                    return arr[i][0].first;
                }
                if (arr[0][i].first == arr[1][i].first && arr[1][i].first == arr[2][i].first)
                {
                    return arr[0][i].first;
                }
            }
            if (arr[1][1].second && ((arr[0][0] == arr[1][1] && arr[2][2] == arr[1][1]) || (arr[2][0] == arr[1][1] && arr[0][2] == arr[1][1])))
            {
                return arr[1][1].first;
            }
            if (j == 9)
                return 'D';
        }
        return (char)0;
    }
};
void versus_player()
{
    system("cls");
    cout << "Playing 1v1\n";
    game player;
    player.initiate();
    cout << "Which one do you wanna be X or O\nTo exit press any other\n";
    char p1, p2;
    cin >> p1;
    if (p1 >= 'a')
        p1 = p1 - 32;
    if (p1 != 'X' && p1 != 'O')
    {
        return;
    }
    p2 = 'X' + 'O' - p1;
    player.board();
    for (int i = 0; i < 9; i++)
    {
        if (!(i % 2))
        {
            cout << "Turn Player 1 (" << p1 << ")\n";
            player.play(p1);
        }
        else
        {
            cout << "Turn Player 2 (" << p2 << ")\n";
            player.play(p2);
        }
        system("cls");
        player.board();
        char check = player.checkifgameisover();
        if (check)
        {
            if (check == p1)
            {
                cout << "Victory Player 1\n";
                break;
            }
            if (check == p2)
            {
                cout << "Victory Player 2\n";
                break;
            }
            if (check == 'D')
            {
                cout << "Draw\n";
                break;
            }
        }
    }
}
int minMax(game player, int depth, bool maximize, int alpha, int beta, char comp, char opponent)
{
    char c = player.checkifgameisover();
    if (c)
    {
        count++;
        if (c == comp)
            return 10 - depth;
        if (c == opponent)
            return -10 - depth;
        if (c == 'D')
            return -depth;
    }
    game n;
    int index = 0, eval = 0;
    if (maximize)
    {
        int max_eval = INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if (!player.arr[i / 3][i % 3].second)
            {
                n.arr = player.arr;
                n.arr[i / 3][i % 3].second = 1;
                n.arr[i / 3][i % 3].first = comp;
                eval = minMax(n, depth + 1, !maximize, alpha, beta, comp, opponent);
                if (eval > max_eval)
                {
                    max_eval = eval;
                    index = i;
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        if (depth != 0)
            return max_eval;
    }
    else
    {
        int min_eval = INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if (!player.arr[i / 3][i % 3].second)
            {
                n.arr = player.arr;
                n.arr[i / 3][i % 3].second = 1;
                n.arr[i / 3][i % 3].first = opponent;
                eval = minMax(n, depth + 1, !maximize, alpha, beta, comp, opponent);
                if (eval < min_eval)
                {
                    min_eval = eval;
                    index = i;
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        if (depth != 0)
            return min_eval;
    }
    return index;
}
void versus_Computer()
{
    system("cls");
    game player;
    player.initiate();
    player.board();
    int turn, i = 0, j;
    cout << "Choose which turn you want :-\nFor player 1 press 1\nFor player 2 press 2\nTo exit press any other\n";
    cin >> turn;
    if (turn != 1 && turn != 2)
        return;
    cout << "Choose what do you wanna play as X or O\n";
    char p1, p2;
    cin >> p2;
    if (p2 >= 'a')
        p2 = p2 - 32;
    if (p2 != 'X' && p2 != 'O')
        return;
    p1 = 'X' + 'O' - p2;
    system("cls");
    player.board();
    for (i = 0; i < 9; i++)
    {
        if (!((i + turn) % 2))
        {
            count = 0;
            j = minMax(player, 0, true, INT_MIN, INT_MAX, p1, p2);
            cout << "Iterations = " << count << endl;
            player.arr[j / 3][j % 3].second = 1;
            player.arr[j / 3][j % 3].first = p1;
        }
        else
        {
            cout << "Player's turn\n";
            player.play(p2);
        }
        player.board();
        char k = player.checkifgameisover();
        if (k)
        {
            if (k == p1)
                cout << "Victory Computer\n";
            if (k == p2)
                cout << "Victory Player\n";
            if (k == 'D')
                cout << "Draw\n";
            return;
        }
    }
    return;
}
int main()
{
    int j = 1;
    while (j == 1 || j == 2)
    {
        cout << "For playing 1v1 enter 1\nFor playing with computer enter 2\nTo exit press any other \n";
        cin >> j;
        if (j == 1)
            versus_player();
        else if (j == 2)
            versus_Computer();
    }
    system("cls");
    cout << "Thank You for playing";
}