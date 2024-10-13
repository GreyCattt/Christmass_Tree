#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>
#include <csignal>  

using namespace std;

bool keepRunning = true;  // To control the animation loop

void signalHandler(int signal) {
    if (signal == SIGINT) {  // SIGINT is the signal sent by Ctrl+C
        cout << "\nAnimation stopped by user (Ctrl+C).\n";
        keepRunning = false;  // Set flag to exit loop
    }
}

void drawTree(const vector<vector<char>>& arr, int m, int basewidth, int totalRows, ofstream& file);
void animateTree(vector<vector<char>>& arr, int m, int basewidth, int totalRows, int delay, ofstream& file);

int main() {
    // Register signal handler for Ctrl+C
    signal(SIGINT, signalHandler);

    ofstream file("Christmas_Tree_output.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));
    int m;
    cout << "Specify the number of levels (layers) of the Christmas tree (1 to 6): ";
    cin >> m;

    if (m <= 0 || m >= 7) {
        cout << "The number of levels must be between 1 and 6." << endl;
        return 1;
    }

    int basewidth = 1;
    int totalRows = 0;

    // Calculate the total number of rows
    for (int level = 1; level <= m; ++level) {
        totalRows += level;
    }

    vector<vector<char>> arr(totalRows, vector<char>(m * 2 - 1, ' '));

    // Initial decoration placement
    int numDecorations = 40;
    vector<pair<int, int>> decorations;
    for (int i = 0; i < numDecorations; ++i) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (m * 2 - 1);
        decorations.push_back({ randRow, randCol });
        arr[randRow][randCol] = (rand() % 2 == 0) ? '@' : '#';
    }

    // Start the animation
    animateTree(arr, m, basewidth, totalRows, 500, file);

    return 0;
}

void drawTree(const vector<vector<char>>& arr, int m, int basewidth, int totalRows, ofstream& file) {
    string green = "\033[32m";
    string yellow = "\033[33m";
    string red = "\033[31m";
    string blue = "\033[34m";
    string reset = "\033[0m";

    int currentRow = 0;
    for (int level = 1; level <= m; ++level) {
        for (int row = 0; row < level; ++row) {
            int starCount = basewidth + 2 * row;
            int spaces = (m * 2 + 1 - starCount) / 2;

            for (int j = 0; j < spaces; ++j) {
                cout << " ";
                file << " ";
            }

            for (int j = 0; j < starCount; ++j) {
                char outputSymbol = (spaces + j >= 0 && spaces + j < m * 2 - 1 && arr[currentRow][spaces + j] != ' ')
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

    int trunkWidth = 3;
    int trunkHeight = 2;
    int trunkSpaces = (m * 2 + 1 - trunkWidth) / 2;

    for (int i = 0; i < trunkHeight; ++i) {
        for (int j = 0; j < trunkSpaces; ++j) {
            cout << " ";
            file << " ";
        }
        cout << yellow;
        file << "***";
        cout << "***" << reset << endl;
        file << endl;
    }
}

void animateTree(vector<vector<char>>& arr, int m, int basewidth, int totalRows, int delay, ofstream& file) {
    int numDecorations = 20;
    vector<pair<int, int>> decorations(numDecorations);

    for (int i = 0; i < numDecorations; ++i) {
        int randRow = rand() % totalRows;
        int randCol = rand() % (m * 2 - 1);
        decorations[i] = { randRow, randCol };
    }

    while (keepRunning) {
        drawTree(arr, m, basewidth, totalRows, file);
        this_thread::sleep_for(chrono::milliseconds(delay));
        cout << "\033[H\033[J";

        for (int i = 0; i < numDecorations; ++i) {
            arr[decorations[i].first][decorations[i].second] = ' ';
            int newRow = rand() % totalRows;
            int newCol = rand() % (m * 2 - 1);
            decorations[i] = { newRow, newCol };
            arr[newRow][newCol] = (rand() % 2 == 0) ? '@' : '#';
        }
    }


}
