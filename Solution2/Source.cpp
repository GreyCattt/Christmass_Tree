/*
* Done by:
* Student Name: Ivan Rudiy
* Student Group: 123
*Christmas_Tree
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream> // For file operations
using namespace std;

void drawTree(const vector<vector<char>>& arr, int m, ofstream& file);
void generateDecorations(vector<vector<char>>& arr, int m);

int main() {
    srand(static_cast<unsigned>(time(0)));
    int m;
    cout << "Specify the number of levels (layers) of the Christmas tree: ";
    cin >> m;

    if (m <= 0) {
        cout << "The number of levels must be positive!" << endl;
        return 1;
    }

    // Calculate the total number of rows for the Christmas tree
    int totalRows = 0;
    for (int level = 1; level <= m; ++level) {
        totalRows += level;
    }

    vector<vector<char>> arr(totalRows, vector<char>(2 * m - 1, ' ')); // Array for tree

    // Generate decorations
    generateDecorations(arr, m);

    // Open a file to save the output
    ofstream file("Christmas_Tree_output.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    // Draw the tree and save it to the file
    drawTree(arr, m, file);

    cout << "Tree drawn successfully! Check 'Christmas_Tree_output.txt' for the saved output." << endl;

    file.close();
    return 0;
}

// Function to draw the tree and save it to both the console and a file
void drawTree(const vector<vector<char>>& arr, int m, ofstream& file) {
    string green = "\033[32m";
    string yellow = "\033[33m";
    string red = "\033[31m";
    string blue = "\033[34m";
    string reset = "\033[0m";

    int currentRow = 0;
    for (int level = 1; level <= m; ++level) {
        for (int row = 0; row < level; ++row) {
            int starCount = 1 + 2 * row; // Number of stars in each row of the level
            int spaces = (2 * m - 1 - starCount) / 2; // Number of spaces before stars

            // Output spaces
            for (int j = 0; j < spaces; ++j) {
                cout << " ";
                file << " ";
            }

            // Output stars or decorations
            for (int j = 0; j < starCount; ++j) {
                char outputSymbol = (spaces + j >= 0 && spaces + j < 2 * m - 1 && arr[currentRow][spaces + j] != ' ')
                    ? arr[currentRow][spaces + j] : '*';

                if (outputSymbol == '*') {
                    cout << green << outputSymbol;
                    file << '*';
                }
                else if (outputSymbol == '@') {
                    cout << red << outputSymbol;
                    file << '@';
                }
                else {
                    cout << blue << outputSymbol;
                    file << '#';
                }
            }
            cout << reset << endl;
            file << endl;
            ++currentRow;
        }
    }

    // Draw the trunk
    int treeWidth = 3;
    int treeHeight = 2;
    int trunkSpaces = (2 * m - 1 - treeWidth) / 2;

    for (int i = 0; i < treeHeight; ++i) {
        for (int j = 0; j < trunkSpaces; ++j) {
            cout << " ";
            file << " ";
        }
        cout << yellow;
        for (int j = 0; j < treeWidth; ++j) {
            cout << "*";
            file << "*";
        }
        cout << reset << endl;
        file << endl;
    }
}

// Function to generate decorations for the tree
void generateDecorations(vector<vector<char>>& arr, int m) {
    int totalRows = 0;
    for (int level = 1; level <= m; ++level) {
        totalRows += level;
    }

    int numDecorations = 40;

    // Randomly place decorations on the tree
    for (int i = 0; i < numDecorations; ++i) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (2 * m - 1);
        arr[randRow][randCol] = (rand() % 2 == 0) ? '@' : '#';
    }
}
