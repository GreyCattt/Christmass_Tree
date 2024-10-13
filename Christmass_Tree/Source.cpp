/**
* Done by:
* Student Name: Ivan Rudiy
* Student Group: 123
* Project name: Christmass_Tree
*/
//that solution with blinking animation
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

void drawTree(const vector<vector<char>>& arr, int m, int basewidth, int totalRows);
void animateTree(vector<vector<char>>& arr, int m, int basewidth, int totalRows, int delay);

int main() {
    srand(static_cast<unsigned>(time(0)));
    int m;
    std::cout << "Specify the number of levels (layers) of the Christmas tree(a number from 1 to 6): ";
    cin >> m;
    int basewidth = 1; // The width of the base of the Christmas tree
    if (m <= 0) {
        cout << "The number of levels must be positive!" << endl;
        return 1;
    }
    else if (m >= 7) 
    {
        cout << "The number is equal to or greater than 7";
        return 1;
    
    }

    //Calculate the total number of rows for all levels of the tree
    int totalRows = 0;
    for (int level = 1; level <= m; level++) {
        totalRows += level; 
    }
    
    vector<vector<char>> arr(totalRows, vector<char>(m * 2 - 1, ' ')); //  Array for tree

    //Generate decorations at the beginning
    int numDecorations = 20; 
    vector<pair<int, int>> decorations; 

    // Randomly place the decorations on the tree
    for (int i = 0; i < numDecorations; i++) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (m * 2 - 1);
        decorations.push_back({ randRow, randCol });
        arr[randRow][randCol] = (rand() % 2 == 0) ? '@' : '#'; 
    }

    animateTree(arr, m, basewidth, totalRows, 500); 

    return 0;
}

// Function for drawing a tree
void drawTree(const vector<vector<char>>& arr, int m, int basewidth, int totalRows) {
    string green = "\033[32m"; 
    string yellow = "\033[33m"; 
    string red = "\033[31m";   
    string blue = "\033[34m";
    string reset = "\033[0m";   

    int currentRow = 0;
    for (int level = 1; level <= m; ++level) {
        for (int row = 0; row < level; row++) {
            int starCount = basewidth + 2 * row;// The number of stars in each row of the level
            int spaces = (m * 2 + 1 - starCount) / 2;//Number of spaces before stars

            //Output of spaces
            for (int j = 0; j < spaces; j++) {
                std::cout << " ";
            }
            //Output of stars or decorations
            for (int j = 0; j < starCount; j++) {
                char outputSymbol = (spaces + j >= 0 && spaces + j < m * 2 - 1 && arr[currentRow][spaces + j] != ' ') ? arr[currentRow][spaces + j] : '*';
                if (outputSymbol == '*') {
                    std::cout << green << outputSymbol;
                }
                else {
                    if (outputSymbol == '@') {
                        std::cout << red << outputSymbol;
                    }
                    else {
                        std::cout << blue << outputSymbol;
                    }
                }
            }
            std::cout << reset << endl;
            currentRow++;
        }
    }

    // draw the tree trunk
    int tree_wd = 3; 
    int tree_hei = 2; 
    int tree_spaces = (m * 2 + 1 - tree_wd) / 2;

    for (int i = 0; i < tree_hei; i++) {
        for (int j = 0; j < tree_spaces; j++) {
            std::cout << " ";
        }
        std::cout << yellow; 
        for (int j = 0; j < tree_wd; j++) {
            std::cout << "*";
        }
        std::cout << reset << endl; 
    }
}


void animateTree(vector<vector<char>>& arr, int m, int basewidth, int totalRows, int delay) {
    int numDecorations = 20; 
    vector<pair<int, int>> decorations;

    // Initialize random decorations
    for (int i = 0; i < numDecorations; i++) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (m * 2 - 1);
        decorations.push_back({ randRow, randCol });
    }

    while (true) {
        drawTree(arr, m, basewidth, totalRows);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        std::cout << "\033[H\033[J"; //clearing the console

        // move decor
        for (int i = 0; i < numDecorations; i++) {
            
            arr[decorations[i].first][decorations[i].second] = ' ';

            int newRow = rand() % totalRows;
            int newCol = rand() % (m * 2 - 1);

            decorations[i] = { newRow, newCol };
            arr[newRow][newCol] = (rand() % 2 == 0) ? '@' : '#';
        }
    }
}
