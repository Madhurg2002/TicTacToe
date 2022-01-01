#include <iostream>
#include <vector>
using namespace std;
int bel = 0;
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
                cout << arr[i][j].first << " ";
            cout << endl;
        }
    }
    char check_for_victory(int n)
    {
        if (n >= 5)
        {
            int x = 0;
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
        }
        return (char)0;
    }
};
int min_max(char turn, int turn_number, game initial, int depth, char comp, char player)
{
    // cout << "hello " << depth << endl;
    // initial.board();
    game n;
    int curr, mind = 10;
    char to_move = '0';
    if (depth == 10)
        return -(depth - turn_number);
    depth++;
    if (turn == comp)
        for (int i = 0; i < 9; i++)
        {
            if (!initial.arr[i / 3][i % 3].second)
            {
                n.arr = initial.arr;
                n.arr[i / 3][i % 3].second = 1;
                n.arr[i / 3][i % 3].first = turn;
                curr = min_max(comp + player - turn, turn_number, n, depth, comp, player);
                mind = min(mind, curr);
                if (mind == curr)
                    to_move = '0' + i;
            }
        }
    if (turn == player)
        for (int i = 0; i < 9; i++)
        {
            if (!initial.arr[i / 3][i % 3].second)
            {
                n.arr = initial.arr;
                n.arr[i / 3][i % 3].second = 1;
                n.arr[i / 3][i % 3].first = turn;
                curr = min_max(comp + player - turn, turn_number, n, depth, comp, player);
                mind = max(mind, curr);
                if (mind == curr)
                    to_move = '0' + i;
            }
        }
    if (n.check_for_victory(depth) == comp)
        return 10 - (depth - turn_number);
    if (n.check_for_victory(depth) == player)
        return -10 - (depth - turn_number);
    if (turn_number == depth - 1)
    {
        cout << to_move - '0' << endl;
        return (int)(to_move - '0');
    }
    return mind;
}
void versus_player()
{
    system("cls");
    cout << "Playing 1v1\n";
    game player;
    player.initiate();
    player.board();
    for (int i = 0; i < 9; i++)
    {
        if (!(i % 2))
        {
            cout << "Turn Player 1 (O)\n";
            player.play('O');
        }
        else
        {
            cout << "Turn Player 2 (X)\n";
            player.play('X');
        }
        system("cls");
        player.board();
        if (player.check_for_victory(i + 1) == 'O' || player.check_for_victory(i + 1) == 'X')
        {
            cout << "Victory Player" << (i + 1) % 2 + 1 << "\n";
            break;
        }
        if (i == 8)
            cout << "Draw\n";
    }
}
void versus_Computer()
{
    system("cls");
    game player;
    player.initiate();
    player.board();
    int turn, i = 0, j;
    cout << "Choose which player you wanna be :-\nFor player 1 press 1\nFor player 2 press 2\nTo exit press any other\n";
    cin >> turn;
    if (turn == 1)
        for (i = 0; i < 9; i++)
        {
            if (!(i % 2))
            {
                j = min_max('O', i + 1, player, i + 1, 'O', 'X');
                player.arr[j / 3][j % 3].second = 1;
                player.arr[j / 3][j % 3].first = 'O';
            }
            else
            {
                cout << "Player's turn\n";
                player.play('X');
            }
            char k = player.check_for_victory(i + 1);
            if (k == 'O')
            {
                cout << "Victory Computer\n";
                break;
            }
            if (k == 'X')
            {
                cout << "Victory Player\n";
                break;
            }
            player.board();
        }
    else if (turn == 2)
        for (i = 0; i < 9; i++)
        {
            if (!(i % 2))
            {
                cout << "Player's Turn\n";
                player.play('O');
            }
            else
            {
                j = min_max('X', i + 1, player, i + 1, 'X', 'O');
                player.arr[j / 3][j % 3].second = 1;
                player.arr[j / 3][j % 3].first = 'X';
            }
            char k = player.check_for_victory(i + 1);
            if (k == 'X')
            {
                cout << "Victory Computer\n";
                break;
            }
            if (k == 'O')
            {
                cout << "Victory Player\n";
                break;
            }
            player.board();
        }
    if (i == 9)
        cout << "Draw\n";
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