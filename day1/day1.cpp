#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
void part1();
void part2();
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
        printf("argc: %d\n", argc);
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
        printf("argv[1]: %s\n", argv[1]);
    }
}
void part1()
{
    ifstream file("./day1p1_input");
    int inputLine = -1;
    int previousLine;
    string change;
    int numDepthIncreases = 0;

    while (file >> inputLine)
    {
        change = "";
        if (!previousLine)
        {
            change = "no previous input";
            printf("input: %d, previous: %s, change: %s\n",
                   inputLine, "n/a", change.c_str());
        }
        else
        {
            int difference = inputLine - previousLine;

            if (difference > 0)
            {
                change = "depth increase!";
                numDepthIncreases++;
            } // else if(difference == 0 ) {
            //     change = "no change";
            // } else {
            //     change = "depth decrease!";
            // }
            // printf("input: %d, previous: %d, change: %s\n",
            //     inputLine, previousLine, change.c_str());
        }

        previousLine = inputLine;
    }

    printf("Num depth increases: %d\n", numDepthIncreases);
    file.close();
}

void part2()
{
    printf("Part 2 ");
    // sliding 3 part window
    // abc vs bcd difference 4 values and then shift
    //    it's possible if A < D then increase?
    ifstream file("./day1p1_input");
    int input[2000];
    string change;
    int numDepthIncreases = 0;
    int i = 0;
    int a, b, c, d;
    // read all the input in smh
    while (file >> a)
    {
        input[i] = a;
        i++;
    }

    for (int tail = 0; tail < 2000 - 3; tail++)
    {
        //printf("%d; ", input[tail]);
        // assign. 
        a = input[tail];
        b = input[tail+1];
        c = input[tail+2];
        d = input[tail+3];
        //printf("a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
        //check increase
        // if (a + b + c < b + c + d)
        if (a < d)
        {
            numDepthIncreases++;
        }

    }
    printf("num increases: %d\n", numDepthIncreases);

    file.close();
}