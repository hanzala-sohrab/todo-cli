#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>
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

void missing_done_number()
{
    cout << "Error: Missing NUMBER for marking todo as done.\n";
}

string getLastLine(ifstream& in)
{
    string line;
    //  std::ws
    while (getline(in, line));
    return line;
}

string ls()
{
    ifstream fin;
    fin.open("todo.txt");

    //  Checking if last line is empty
    string lastLine = getLastLine(fin);
    if (!lastLine.empty())
    {
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n";
        fout.close();
    }

    fin.close();

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
        time_t rawtime;
        tm* timeinfo;
        char buffer [80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,80,"%Y-%m-%d",timeinfo);
        string t(buffer);

        r = "x " + t + " " + r;
        fout << r << '\n';
        fout.close();
    }
    return r;
}

void report()
{
    int pendingTodos = 0, completedTodos = 0;
    string todo;
    ifstream fin("todo.txt");

    while (getline(fin, todo))
        ++pendingTodos;

    fin.close();

    fin.open("done.txt");

    while (getline(fin, todo))
        ++completedTodos;

    time_t rawtime;
    tm* timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y-%m-%d",timeinfo);
    printf("%s Pending : %d Completed : %d\n", buffer, pendingTodos, completedTodos);
}

int main(int argc, char* argv[])
{
    // If no extra arguments, then show help
    if (argc == 1)
        help();
    else if (argc == 2)
    {
        // Showing help
        if (strcmp(argv[1], "help") == 0)
            help();

        // Listing todos
        else if (strcmp(argv[1], "ls") == 0)
        {
            string s = ls();
            cout << s;
        }

        // Reporting
        else if (strcmp(argv[1], "report") == 0)
            report();

        // Show error if no todo number provided for deleting
        else if (strcmp(argv[1], "del") == 0)
            missing_delete_number();

        // Show error if no todo provided for adding
        else if (strcmp(argv[1], "add") == 0)
            missing_todo_string();

        // Show error if no todo number provided for marking as done
        else if (strcmp(argv[1], "done") == 0)
            missing_done_number();
    }
    else if (argc == 3)
    {
        // Adding a todo
        if (strcmp(argv[1], "add") == 0)
        {
            add_todo(argv[2]);
            cout << "Added todo: \"" << argv[2] << "\"\n";
        }

        // Deleting a todo
        else if (strcmp(argv[1], "del") == 0)
        {
            string r = delete_todo(argv[2]);
            if (r == "Error")
                cout << "Error: todo #" << argv[2] << " does not exist. Nothing deleted.\n";
            else
                cout << "Deleted todo #" << argv[2] << '\n';
        }

        // Marking todo as done
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
