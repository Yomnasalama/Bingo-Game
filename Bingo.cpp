#include <bits/stdc++.h>
#include<iostream>
using namespace std;
const int N = 5;
const int n_players = 2;
char marks[n_players] = {'H', 'Y'};
string elements[25] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25"};
vector<string> chosen_elements;
string bingo = "BINGO";
struct players
{
    string grid[N][N];
    int score;
}h,y;
void clear_grid()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            h.grid[i][j] = "0";
            y.grid[i][j] = "0";
        }
    }
}
bool check_full(players &player)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(player.grid[i][j] == "0")
                return false;
        }
    }
    return true;
}
void set_elements()
{
    int x = 0, j = 0, i = 0, k = 0, f = 0;
    srand(time(0));
    while(!check_full(h))
    {
         i = rand() % 5;
         j = rand() % 5;
         if(h.grid[i][j] == "0")
         {
             h.grid[i][j] = elements[x];
             x++;
         }
    }
    x = 0;
    while(!check_full(y))
    {
         i = rand() % 5;
         j = rand() % 5;
         if(y.grid[i][j] == "0")
         {
             y.grid[i][j] = elements[x];
             x++;
         }
    }
}
bool check_valid_element(string element)
{
    stringstream conv(element);
    int num = 0;
    conv >> num;
    if(num < 1 || num > 25)
        return false;
    for(int k = 0; k < chosen_elements.size(); k++)
    {
        if(element == chosen_elements[k])
            return false;
    }
    return true;
}
void print_grid(players player) {
    cout << "Player 1: " << marks[0] << " vs Player 2: " << marks[1] << "\n";
    cout << "---";
    for (int i = 0; i <= N+2; cout << "----", i++);
    cout << "---\n";
    for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++)
       {
           cout << "| ";
           stringstream s(player.grid[i][j]);
           int x = 0;
           s >>x;
           if(x < 10)
               cout <<"  "<< player.grid[i][j] << "  ";
           else
               cout <<" "<< player.grid[i][j] << "  ";
       }
       cout << "|\n";
       cout << "---";
       for (int i = 0; i <= N+2; cout << "----", i++);
       cout << "---\n";
    }
    for(int i = 0; i < player.score; i++)
    {
        cout << "    "<<bingo[i]<<" ";
    }
    cout<<endl;
}
bool check_win_tie()
{
    int count_row = 0, count_column = 0, count_diagonal = 0, count_reverse = 0; y.score = 0; h.score = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(y.grid[i][j] == "B")
                count_row++;
            if(y.grid[j][i] == "B")
                 count_column++;
            if(i == j)
            {
                if(y.grid[i][j] == "B")
                    count_diagonal++;
            }
            if(i+j == 4)
            {
                if(y.grid[i][j] == "B")
                    count_reverse++;
            }
        }
        if(count_column == N)
            y.score++;
        if(count_row == N)
            y.score++;
        count_row = 0;
        count_column = 0;
    }
    if(count_reverse == N)
        y.score++;
    if(count_diagonal == N)
        y.score++;
    count_row = 0; count_column = 0; count_diagonal = 0; count_reverse = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(h.grid[i][j] == "B")
                count_row++;
            if(h.grid[j][i] == "B")
                 count_column++;
            if(i == j)
            {
                if(h.grid[i][j] == "B")
                    count_diagonal++;
            }
            if(i+j == 4)
            {
                if(h.grid[i][j] == "B")
                    count_reverse++;
            }
        }
        if(count_column == N)
            h.score++;
        if(count_row == N)
            h.score++;
        count_row = 0;
        count_column = 0;
    }
    if(count_reverse == N)
        h.score++;
    if(count_diagonal == N)
        h.score++;
    if(y.score > h.score && y.score >= N)
    {
        cout<<marks[1]<<" "<<"Winner winner chicken dinner"<<endl;
        print_grid(y);
        return true;
    }
    else if(y.score < h.score && h.score >= N)
    {
        cout<<marks[0]<<" "<<"Winner winner chicken dinner"<<endl;
        print_grid(h);
        return true;
    }
    else if(y.score == h.score && h.score == N)
    {
        cout<<"TIE!!"<<endl;
        print_grid(h);
        print_grid(y);
        return true;
    }
    return false;
}
void mark(string element)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(h.grid[i][j] == element)
                h.grid[i][j] = "B";
            if(y.grid[i][j] == element)
                y.grid[i][j] = "B";
        }
    }
    chosen_elements.push_back(element);
}
int read_input(string &i)
{
    cout<<"Enter a number: "<<endl;
    cin>>i;
    while(!check_valid_element(i))
    {
        cout<<"Enter valid number: "<<endl;
        cin>>i;
    }
}
void play()
{
        cout<<"Bingo Game..."<<endl;
        cout<<"-------------------------"<<endl;
        int player = 0;
        while(true){
            if(player == 0)
                print_grid(h);
            else
                print_grid(y);
            cout<<"Player "<<marks[player]<<" is playing now"<<endl;
            string i;
            read_input(i);
            mark(i);
            if(check_win_tie())
                break;
            player = (player + 1) % n_players;
       }
}
int main()
{
  while(true)
  {
      clear_grid();
      set_elements();
      play();
      char c;
      cout<<"Play Again [Y/N]";
      cin>>c;
      if(c != 'y' && c!= 'Y')
        break;
 }
}
#include <bits/stdc++.h>
#include<iostream>
using namespace std;
const int N = 5;
const int n_players = 2;
char marks[n_players] = {'H', 'Y'};
string elements[25] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25"};
vector<string> chosen_elements;
string bingo = "BINGO";
struct players
{
    string grid[N][N];
    int score;
}h,y;
void clear_grid()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            h.grid[i][j] = "0";
            y.grid[i][j] = "0";
        }
    }
}
bool check_full(players &player)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(player.grid[i][j] == "0")
                return false;
        }
    }
    return true;
}
void set_elements()
{
    int x = 0, j = 0, i = 0, k = 0, f = 0;
    srand(time(0));
    while(!check_full(h))
    {
         i = rand() % 5;
         j = rand() % 5;
         if(h.grid[i][j] == "0")
         {
             h.grid[i][j] = elements[x];
             x++;
         }
    }
    x = 0;
    while(!check_full(y))
    {
         i = rand() % 5;
         j = rand() % 5;
         if(y.grid[i][j] == "0")
         {
             y.grid[i][j] = elements[x];
             x++;
         }
    }
}
bool check_valid_element(string element)
{
    stringstream conv(element);
    int num = 0;
    conv >> num;
    if(num < 1 || num > 25)
        return false;
    for(int k = 0; k < chosen_elements.size(); k++)
    {
        if(element == chosen_elements[k])
            return false;
    }
    return true;
}
void print_grid(players player) {
    cout << "Player 1: " << marks[0] << " vs Player 2: " << marks[1] << "\n";
    cout << "---";
    for (int i = 0; i <= N+2; cout << "----", i++);
    cout << "---\n";
    for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++)
       {
           cout << "| ";
           stringstream s(player.grid[i][j]);
           int x = 0;
           s >>x;
           if(x < 10)
               cout <<"  "<< player.grid[i][j] << "  ";
           else
               cout <<" "<< player.grid[i][j] << "  ";
       }
       cout << "|\n";
       cout << "---";
       for (int i = 0; i <= N+2; cout << "----", i++);
       cout << "---\n";
    }
    for(int i = 0; i < player.score; i++)
    {
        cout << "    "<<bingo[i]<<" ";
    }
    cout<<endl;
}
bool check_win_tie()
{
    int count_row = 0, count_column = 0, count_diagonal = 0, count_reverse = 0; y.score = 0; h.score = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(y.grid[i][j] == "B")
                count_row++;
            if(y.grid[j][i] == "B")
                 count_column++;
            if(i == j)
            {
                if(y.grid[i][j] == "B")
                    count_diagonal++;
            }
            if(i+j == 4)
            {
                if(y.grid[i][j] == "B")
                    count_reverse++;
            }
        }
        if(count_column == N)
            y.score++;
        if(count_row == N)
            y.score++;
        count_row = 0;
        count_column = 0;
    }
    if(count_reverse == N)
        y.score++;
    if(count_diagonal == N)
        y.score++;
    count_row = 0; count_column = 0; count_diagonal = 0; count_reverse = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(h.grid[i][j] == "B")
                count_row++;
            if(h.grid[j][i] == "B")
                 count_column++;
            if(i == j)
            {
                if(h.grid[i][j] == "B")
                    count_diagonal++;
            }
            if(i+j == 4)
            {
                if(h.grid[i][j] == "B")
                    count_reverse++;
            }
        }
        if(count_column == N)
            h.score++;
        if(count_row == N)
            h.score++;
        count_row = 0;
        count_column = 0;
    }
    if(count_reverse == N)
        h.score++;
    if(count_diagonal == N)
        h.score++;
    if(y.score > h.score && y.score >= N)
    {
        cout<<marks[1]<<" "<<"Winner winner chicken dinner"<<endl;
        print_grid(y);
        return true;
    }
    else if(y.score < h.score && h.score >= N)
    {
        cout<<marks[0]<<" "<<"Winner winner chicken dinner"<<endl;
        print_grid(h);
        return true;
    }
    else if(y.score == h.score && h.score == N)
    {
        cout<<"TIE!!"<<endl;
        print_grid(h);
        print_grid(y);
        return true;
    }
    return false;
}
void mark(string element)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(h.grid[i][j] == element)
                h.grid[i][j] = "B";
            if(y.grid[i][j] == element)
                y.grid[i][j] = "B";
        }
    }
    chosen_elements.push_back(element);
}
int read_input(string &i)
{
    cout<<"Enter a number: "<<endl;
    cin>>i;
    while(!check_valid_element(i))
    {
        cout<<"Enter valid number: "<<endl;
        cin>>i;
    }
}
void play()
{
        cout<<"Bingo Game..."<<endl;
        cout<<"-------------------------"<<endl;
        int player = 0;
        while(true){
            if(player == 0)
                print_grid(h);
            else
                print_grid(y);
            cout<<"Player "<<marks[player]<<" is playing now"<<endl;
            string i;
            read_input(i);
            mark(i);
            if(check_win_tie())
                break;
            player = (player + 1) % n_players;
       }
}
int main()
{
  while(true)
  {
      clear_grid();
      set_elements();
      play();
      char c;
      cout<<"Play Again [Y/N]";
      cin>>c;
      if(c != 'y' && c!= 'Y')
        break;
 }
}
