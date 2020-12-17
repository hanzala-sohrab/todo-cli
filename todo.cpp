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

void ls()
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
        cout << "There are no pending todos!\n";
    else
        cout << s;
}

void add_todo(char* todoItem)
{
    ofstream fout;
    fout.open("todo.txt", ios::app);

    fout << todoItem << "\n";
    fout.close();

    std::cout << "Added todo: \"" << todoItem << "\"\n";
}

void delete_todo(char* todoItem)
{
    ifstream fin;
    fin.open("todo.txt");

    vector<string> v;
    string todo, s;

    int i, num;
    sscanf(todoItem, "%d", &num);

    while (fin)
    {
        getline(fin, todo);
        if (!todo.empty())
            v.push_back(todo);
    }

    if (v.empty() or (long unsigned int)num > v.size() or num < 1)
        cout << "Error: todo #" << num << " does not exist. Nothing deleted.\n";
    else {
        for (i = v.size() - 1; i >= 0; --i)
            if (i + 1 != num)
                s = v[i] + "\n" + s;

        ofstream fout;
        fout.open("todo.txt");

        fout << s;

        cout << "Deleted todo #" << num << '\n';
    }
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
            ls();
        else if (strcmp(argv[1], "del") == 0)
            missing_delete_number();
        else if (strcmp(argv[1], "add") == 0)
            missing_todo_string();
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "add") == 0)
            add_todo(argv[2]);
        else if (strcmp(argv[1], "del") == 0)
        {
            std::ifstream fin;
            fin.open("todo.txt");

            vector<string> v;
            string todo, s;

            int i, num;
            sscanf(argv[2], "%d", &num);

            while (fin)
            {
                getline(fin, todo);
                if (!todo.empty())
                    v.push_back(todo);
            }

            if (v.empty() or (long unsigned int)num > v.size() or num < 1)
                cout << "Error: todo #" << num << " does not exist. Nothing deleted.\n";
            else {
                for (i = v.size() - 1; i >= 0; --i)
                    if (i + 1 != num)
                        s = v[i] + "\n" + s;

                ofstream fout;
                fout.open("todo.txt");

                fout << s;

                cout << "Deleted todo #" << num << '\n';
            }
        }
    }
    return 0;
}
