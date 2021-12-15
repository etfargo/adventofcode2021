#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;
void part1();
void part2();

struct Board_Data
{
    /* data */
    int board[5][5] = {};
};
vector<struct Board_Data> Boards;
vector<struct Board_Data> Marks;
void printBoard(struct Board_Data board, struct Board_Data marks);

/**
 * @brief need to run with ./run <1|2> for part one or two
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{

    if (argc)
    {
        std::printf("argc: %d\n", argc);
    }

    if (argv[1])
    {
        int num = stoi(argv[1]);
        if (num == 1)
        {
            part1();
        }
        else
        {
            part2();
        }
        std::printf("argv[1]: %s\n", argv[1]);
    }
}
// Which board will win first?
void part1()
{
    ifstream file("./day4_input.txt");
    
    string callorder, curLine;

    // read first line into numbers vector, this is order of calling
    file >> callorder;
    istringstream firstLine( callorder );
    vector<int> nums;

    while(firstLine) {
        string call;
        if( !getline(firstLine, call, ',')) break;
        nums.push_back(std::stoi(call, nullptr, 10));
    }

    // read boards in 
    int lineNum = 0, lineIndex = 0;
    struct Board_Data board;
    struct Board_Data emptyBoard;
    while(file >> curLine) {
        //std::printf("%s ", curLine.c_str());
        board.board[lineNum][lineIndex] = std::stoi(curLine, nullptr, 10);
        lineIndex++;
        if(lineIndex == 5) {
            // go to beginning of next line
            lineIndex = 0;
            lineNum++;
            //std::printf("\n");
        }
        if(lineNum == 5) {
            // start new board
            lineNum = 0;
            // add this board
            Boards.push_back(board); 
            // make a same structure filled with zero to indicate marks
            Marks.push_back(emptyBoard);
            //std::printf("\n");
        }
        
    }

    // loop over each board
    int winningBoard = -1;
    int winningCall = -1;
    for(int call = 0; call < nums.size(); call++){
        std::printf("call %d is %d\n", call, nums[call]);
        winningCall = call;
        // mark boards then check if anyone won before calling next
        for(int i = 0; i < Boards.size(); i++) {

            for(int row = 0; row < 5; row++) {

                for(int col = 0; col < 5; col++) {

                    if(Boards[i].board[row][col] == nums[call]) {
                        // mark it off
                        Marks[i].board[row][col] = 1;
                        std::printf("%d -- New mark on Board %d, row: %d, col %d\n",
                            nums[call], i, row, col);
                    }
                }
            }
        }
        bool winFound = false;
        // check wins
        for(int i = 0; i < Boards.size(); i++) {
            // check for row wins
            for(int row = 0; row < 5; row++) {
                int sum = 0;
                for(int col = 0; col < 5; col++) {
                    sum += Marks[i].board[row][col];
                }
                if(sum == 5) {
                    std::printf("BOARD %d HAS A ROW BINGO\n", i);
                    winFound = true;
                    winningBoard = i;
                    break;
                    // maybe set a bool for outer loop break?
                }
            }
            // row found before column
            if(winFound) break;
            // check for column wins
            for(int col = 0; col < 5; col++) {
                int sum = 0;
                for(int row = 0; row < 5; row++) {
                    sum += Marks[i].board[row][col];
                }
                if(sum == 5) {
                    std::printf("BOARD %d HAS A COLUMN BINGO\n", i);
                    winFound = true;
                    winningBoard = i;
                    break;
                    // maybe set a bool for outer loop break?
                }
            }
            // column found before row
            if(winFound) break;
        }
        if(winFound) break;
    }

    // add up the total of all unmarked squares
    int unmarkedSum = 0;
    for(int row = 0; row < 5; row ++) {
        for(int col = 0; col < 5; col++) {
            if(Marks[winningBoard].board[row][col] == 0) {
                unmarkedSum += Boards[winningBoard].board[row][col];
            }
        }
    }
    std::printf("unmarkedSum = %d\n", unmarkedSum);
    // multiply that with the most recently called number
    long score = unmarkedSum * nums[winningCall];
    // this is your score
    std::printf("Your score is: %ld\n", score);
}
// Which board will win LAST??
void part2() 
{
    ifstream file("./day4_input.txt");
    
    string callorder, curLine;

    // read first line into numbers vector, this is order of calling
    file >> callorder;
    istringstream firstLine( callorder );
    vector<int> nums;
    vector<int> winningBoards;

    while(firstLine) {
        string call;
        if( !getline(firstLine, call, ',')) break;
        nums.push_back(std::stoi(call, nullptr, 10));
    }

    // read boards in 
    int lineNum = 0, lineIndex = 0;
    struct Board_Data board;
    struct Board_Data emptyBoard;
    while(file >> curLine) {
        //std::printf("%s ", curLine.c_str());
        board.board[lineNum][lineIndex] = std::stoi(curLine, nullptr, 10);
        lineIndex++;
        if(lineIndex == 5) {
            // go to beginning of next line
            lineIndex = 0;
            lineNum++;
            //std::printf("\n");
        }
        if(lineNum == 5) {
            // start new board
            lineNum = 0;
            // add this board
            Boards.push_back(board); 
            // make a same structure filled with zero to indicate marks
            Marks.push_back(emptyBoard);
            //std::printf("\n");
        }
        
    }


    // loop over each board
    int winningBoard = -1;
    int winningCall = -1;
    bool lastWinFound = false;

    for(int call = 0; call < nums.size(); call++){
        if(winningBoards.size() >= 99) {
            lastWinFound = true;
            break;
        }
        // next call
        std::printf("call %d is %d\n", call, nums[call]);
        winningCall = call;
        
        // mark boards 
        for(int i = 0; i < Boards.size(); i++) {
            // if already won, then skip it
            bool skipBoard = false;
            for(int num : winningBoards) {
                if (i == num) {
                    skipBoard = true;
                    break;
                } 
            }
            if(!skipBoard) {
                for(int row = 0; row < 5; row++) {
                    for(int col = 0; col < 5; col++) {
                        if(Boards[i].board[row][col] == nums[call]) {
                            // mark it off
                            Marks[i].board[row][col] = 1;
                            std::printf("%d -- New mark on Board %d, row: %d, col %d\n",
                                nums[call], i, row, col);
                        }
                    }
                }
            }
        }

        // something is going wrong here. Boards are having many many wins before 
        // being added to the winningBoards list

        // check wins
        for(int i = 0; i < Boards.size(); i++) {
            // if already won, then skip it
            bool skipBoard = false;
            bool winFound = false;
            for(int num : winningBoards) {
                if (i == num) {
                    skipBoard = true;
                    break;
                } 
            }
            if(!skipBoard){
                // check for row wins
                for(int row = 0; row < 5; row++) {
                    int sum = 0;
                    for(int col = 0; col < 5; col++) {
                        sum += Marks[i].board[row][col];
                    }
                    if(sum == 5) {
                        std::printf("BOARD %d HAS A ROW BINGO\n", i);
                        winFound = true;
                        winningBoard = i;
                        winningBoards.push_back(i);
                        break;
                    }
                }
                // row found before column -- don't double count
                if(!winFound) {
                    // check for column wins
                    for(int col = 0; col < 5; col++) {
                        int sum = 0;
                        for(int row = 0; row < 5; row++) {
                            sum += Marks[i].board[row][col];
                        }
                        if(sum == 5) {
                            std::printf("BOARD %d HAS A COLUMN BINGO\n", i);
                            //winFound = true;
                            winningBoard = i;
                            winningBoards.push_back(i);
                            break;
                        }
                    }
                }
            }
        }
        if(lastWinFound) break;
    }


    for(int i : winningBoards) {
        printf("Board %d won\n", i);
    }

    for(int i = 0; i < Boards.size(); i++) {
        printBoard(Boards[i], Marks[i]);
    }


    //add up the total of all unmarked squares
    int unmarkedSum = 0;
    int lastBoard = winningBoards[winningBoards.size() - 1];
    std::printf("last board num is = %d\n", lastBoard);
    for(int row = 0; row < 5; row ++) {
        for(int col = 0; col < 5; col++) {
            if(Marks[lastBoard].board[row][col] == 0) {
                unmarkedSum += Boards[lastBoard].board[row][col];
            }
        }
    }
    std::printf("unmarkedSum = %d\n", unmarkedSum);
    std::printf("winning call num = %d\n", nums[winningCall]);
    // multiply that with the most recently called number
    long score = unmarkedSum * nums[winningCall];
    // this is your score
    std::printf("Your score is: %ld\n", score);
}

void printBoard(struct Board_Data board, struct Board_Data marks) {
    for(int row = 0; row < 5; row ++) {
        for(int col = 0; col < 5; col++) {
            printf("%d ", board.board[row][col]);
        }
        printf("\t");
        for(int col = 0; col < 5; col++) {
            printf("%d ", marks.board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}