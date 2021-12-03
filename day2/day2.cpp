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
    ifstream file("./day2_input.txt");
    ifstream newFile;
    string inputLine;
    int position[2]= {0, 0}; // forward, depth
    string direction;
    int amount;
    int pos;

    while (file)
    {
        getline(file, inputLine);
        // ugh reads an extra line bc dumb..
        if(inputLine == "") {
            printf("end of file\n");
            continue;
        }
        printf("input: %s\n", inputLine.c_str());
        pos = inputLine.find(' ');
        //printf("pos: %d\n", pos);
        direction = inputLine.substr(0, pos);
        amount = stoi(inputLine.substr(pos)); //pos to end
        // forward
        if(direction[0] == 'f') {
            position[0] += amount;
            printf("dir: %s, distance: %d\n", direction.c_str(), position[0]);
        }
        // up decreases depth
        if(direction[0] == 'u') {
            // do i need to check for < 0?
            position[1] -= amount;
            printf("dir: %s, depth: %d\n", direction.c_str(), position[1]);
        }
        // down increases depth
        if(direction[0] == 'd') {
            position[1] += amount;
            printf("dir: %s, depth: %d\n", direction.c_str(), position[1]);
        }
    }
    //file.close();
    printf("forward: %d, final depth: %d\n", position[0], position[1]);
    printf("forward x depth = %d\n", position[0]*position[1]);
}

void part2()
{
    // down and up relate to aim, forward is same but new functionality
    ifstream file("./day2_input.txt");
    ifstream newFile;
    string inputLine;
    int position[3]= {0, 0, 0}; // forward, depth, aim
    string direction;
    int amount;
    int pos;

    while (file)
    {
        getline(file, inputLine);
        // ugh reads an extra line bc dumb..
        if(inputLine == "") {
            printf("end of file\n");
            continue;
        }
        printf("input: %s\n", inputLine.c_str());

        pos = inputLine.find(' ');
        direction = inputLine.substr(0, pos);
        amount = stoi(inputLine.substr(pos)); //pos to end
        // forward
        if(direction[0] == 'f') {
            position[0] += amount;
            // calc new depth (+= aim x amount)
            position[1] = position[1] + (position[2]*amount);
            printf("dir: %s, distance: %d, depth: %d\n", 
                direction.c_str(), position[0], position[1]);
        }
        // up decreases aim
        if(direction[0] == 'u') {
            // do i need to check for < 0?
            position[2] -= amount;
            printf("dir: %s, aim: %d\n", direction.c_str(), position[2]);
        }
        // down increases aim
        if(direction[0] == 'd') {
            position[2] += amount;
            printf("dir: %s, aim: %d\n", direction.c_str(), position[2]);
        }
    }
    //file.close();
    printf("forward: %d, final depth: %d\n", position[0], position[1]);
    printf("forward x depth = %d\n", position[0]*position[1]);
}