#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1 or (argc == 2 and strcmp(argv[1], "help") == 0))
        std::cout << "Usage :-\n"
                "$ ./todo add \"todo item\"  # Add a new todo\n"
                "$ ./todo ls               # Show remaining todos\n"
                "$ ./todo del NUMBER       # Delete a todo\n"
                "$ ./todo done NUMBER      # Complete a todo\n"
                "$ ./todo help             # Show usage\n"
                "$ ./todo report           # Statistics\n";
    else if (argc > 1 and strcmp(argv[1], "add") == 0 and argv[2] == 0)
        std::cout << "Error: Missing todo string. Nothing added!\n";
    else if (argc > 1 and strcmp(argv[1], "del") == 0 and argv[2] == 0)
        std::cout << "Error: Missing NUMBER for deleting todo.\n";
    else if (argc == 2 and strcmp(argv[1], "ls") == 0)
    {
        std::ifstream fin;
        fin.open("todo.txt");

        vector<string> v;
        string todo;

        while (fin)
        {
            getline(fin, todo);
            if (!todo.empty())
                v.push_back(todo);
        }
        fin.close();

        if (v.empty())
            cout << "There are no pending todos!\n";
        else {
            int i, N = v.size();
            for (i = N - 1; i >= 0; --i)
                cout << '[' << i + 1 << "] " << v[i] << '\n';
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "add") == 0)
        {
            std::ofstream fout;
            fout.open("todo.txt", ios::app);

            fout << argv[2] << "\n";
            fout.close();

            std::cout << "Added todo: \"" << argv[2] << "\"\n";
        }
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
                v.push_back(todo);
            }

            for (i = v.size() - 1; i >= 0; --i)
                if (i + 1 != num)
                    s = v[i] + "\n" + s;

            ofstream fout;
            fout.open("todo.txt");

            fout << s;

            cout << "Deleted todo #" << num << '\n';
        }
    }
    return 0;
}
