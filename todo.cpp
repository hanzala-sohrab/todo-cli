#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void help()
{
    cout << "Usage :-\n"
             "$ ./todo add \"todo item\"  # Add a new todo\n"
             "$ ./todo ls               # Show remaining todos\n"
             "$ ./todo del NUMBER       # Delete a todo\n"
             "$ ./todo done NUMBER      # Complete a todo\n"
             "$ ./todo help             # Show usage\n"
             "$ ./todo report           # Statistics\n";
}

void missing_todo_string()
{
    cout << "Error: Missing todo string. Nothing added!\n";
}

void missing_delete_number()
{
    cout << "Error: Missing NUMBER for deleting todo.\n";
}

string ls()
{
    ifstream fin;
    fin.open("todo.txt");

    string todo, s;
    int i = 0;

    while (fin)
    {
        getline(fin, todo);
        ++i;
        if (!todo.empty())
            s = "[" + to_string(i) + "] " + todo + "\n" + s;
    }
    fin.close();

    if (s.empty())
        s = "There are no pending todos!\n";
    return s;
}

void add_todo(char* todoItem)
{
    ofstream fout;
    fout.open("todo.txt", ios::app);

    fout << todoItem << "\n";
    fout.close();
}

string delete_todo(char* todoItem)
{
    ifstream fin;
    fin.open("todo.txt");

    vector<string> v;
    string todo, s, r;

    int i, num;
    sscanf(todoItem, "%d", &num);

    while (fin)
    {
        getline(fin, todo);
        if (!todo.empty())
            v.push_back(todo);
    }

    if (v.empty() or (long unsigned int)num > v.size() or num < 1)
        r = "Error";
    else
    {
        for (i = v.size() - 1; i >= 0; --i)
            if (i + 1 != num)
                s = v[i] + "\n" + s;
            else
                r = v[i];

        ofstream fout;
        fout.open("todo.txt");
        fout << s;
    }
    return r;
}

string done_todo(char* todoItem)
{
    int num;
    sscanf(todoItem, "%d", &num);

    ofstream fout;
    fout.open("done.txt", ios::app);

    string r = delete_todo(todoItem);

    if (r != "Error")
    {
        fout << r << '\n';
        fout.close();
    }
    return r;
}

void report()
{

}

int main(int argc, char* argv[])
{
    if (argc == 1)
        help();
    else if (argc == 2)
    {
        if (strcmp(argv[1], "help") == 0)
            help();
        else if (strcmp(argv[1], "ls") == 0)
        {
            string s = ls();
            cout << s;
        }
        else if (strcmp(argv[1], "report") == 0)
            report();
        else if (strcmp(argv[1], "del") == 0)
            missing_delete_number();
        else if (strcmp(argv[1], "add") == 0)
            missing_todo_string();
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "add") == 0)
        {
            add_todo(argv[2]);
            cout << "Added todo: \"" << argv[2] << "\"\n";
        }
        else if (strcmp(argv[1], "del") == 0)
        {
            string r = delete_todo(argv[2]);
            if (r == "Error")
                cout << "Error: todo #" << argv[2] << " does not exist. Nothing deleted.\n";
            else
                cout << "Deleted todo #" << argv[2] << '\n';
        }
        else if (strcmp(argv[1], "done") == 0)
        {
            string r = done_todo(argv[2]);
            if (r == "Error")
                cout << "Error: todo #" << argv[2] << " does not exist.\n";
            else
                cout << "Marked todo #" << argv[2] << " as done.\n";
        }
    }
    return 0;
}
