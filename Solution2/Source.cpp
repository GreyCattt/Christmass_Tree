//this static, but works with numbers higher than 7
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

void drawTree(const vector<vector<char>>& arr, int m);
void generateDecorations(vector<vector<char>>& arr, int m);

int main() {
    srand(static_cast<unsigned>(time(0)));
    int m;
    std::cout << "Specify the number of levels (layers) of the Christmas tree: ";
    cin >> m;

    if (m <= 0) {
        cout << "The number of levels must be positive!" << endl;
        return 1;
    }

    // Calculation of the total number of rows for the Christmas tree
    int totalRows = 0;
    for (int level = 1; level <= m; level++) {
        totalRows += level;
    }

    vector<vector<char>> arr(totalRows, vector<char>(2 * m - 1, ' ')); // Array for tree

    // Generation of scenery
    generateDecorations(arr, m);

    // draw tree
    drawTree(arr, m);

    return 0;
}

// Function for drawing a tree
void drawTree(const vector<vector<char>>& arr, int m) {
    string green = "\033[32m";
    string yellow = "\033[33m";
    string red = "\033[31m";
    string blue = "\033[34m";
    string reset = "\033[0m";

    int currentRow = 0;
    for (int level = 1; level <= m; ++level) {
        for (int row = 0; row < level; row++) {
            int starCount = 1 + 2 * row; // The number of stars in each row of the level
            int spaces = (2 * m - 1 - starCount) / 2; // Number of spaces before stars

            // Output of spaces
            for (int j = 0; j < spaces; j++) {
                std::cout << " ";
            }

            // Output of stars or decorations
            for (int j = 0; j < starCount; j++) {
                char outputSymbol = (spaces + j >= 0 && spaces + j < 2 * m - 1 && arr[currentRow][spaces + j] != ' ') ? arr[currentRow][spaces + j] : '*';
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

    //draw the trunk
    int treeWidth = 3;
    int treeHeight = 2;
    int trunkSpaces = (2 * m - 1 - treeWidth) / 2;

    for (int i = 0; i < treeHeight; i++) {
        for (int j = 0; j < trunkSpaces; j++) {
            std::cout << " ";
        }
        std::cout << yellow;
        for (int j = 0; j < treeWidth; j++) {
            std::cout << "*";
        }
        std::cout << reset << endl;
    }
}

// Generation of decorations for the tree
void generateDecorations(vector<vector<char>>& arr, int m) {
    int totalRows = 0;
    for (int level = 1; level <= m; level++) {
        totalRows += level;
    }

    int numDecorations = 20;

    // Randomly place the decorations on the tree
    for (int i = 0; i < numDecorations; i++) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (2 * m - 1);
        arr[randRow][randCol] = (rand() % 2 == 0) ? '@' : '#';
    }
}
