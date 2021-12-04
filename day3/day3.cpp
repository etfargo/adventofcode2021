#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
void part1()
{
    ifstream file("./day3_input.txt");
    string inputLine;
    int mostCommonBit[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // index is order of element
    string gamma = "";
    string epsilon = "";
    while (file >> inputLine)
    {
        std::printf("input: %s\n", inputLine.c_str());
        // loop over each line and inc/dec respective counter
        for(int i = 0; i < inputLine.length(); i++) {
            if (inputLine[i] == '1') {
                mostCommonBit[i]++;
            } else {
                mostCommonBit[i]--;
            }
        }
        std::printf("mCB: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d}\n",
            mostCommonBit[0], mostCommonBit[1], mostCommonBit[2],
            mostCommonBit[3], mostCommonBit[4], mostCommonBit[5], 
            mostCommonBit[6], mostCommonBit[7], mostCommonBit[8],
            mostCommonBit[9], mostCommonBit[10], mostCommonBit[11]);
    }
    // get gamma bin 
    for(int i = 0; i < 12; i++) {
        if(mostCommonBit[i] > 0) {
            gamma.append("1");
        } else {
            gamma.append("0");
        }
    }
    // get epsilon bin 
    for(int i = 0; i < 12; i++) {
        if(mostCommonBit[i] < 0) {
            epsilon.append("1");
        } else {
            epsilon.append("0");
        }
    }
    std::printf("%s\n", gamma.c_str());
    std::printf("%s\n", epsilon.c_str());
    int g = std::stoi(gamma, nullptr, 2);
    int e = std::stoi(epsilon, nullptr, 2);
    int result = e * g;
    //file.close();
    std::printf("result = %d\n", result);
}

void part2()
{
    ifstream file("./day3_input.txt");
    ifstream newFile;
    string inputLine; // 12 binary bit
    vector<string> input;
    vector<string> asdf, asdfd;
    int mostCommonBit[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    int amount, pos, i = 0;
    bool flag = false;

    while (file  >> inputLine)
    {
        for(int i = 0; i < inputLine.length(); i++) {
            if (inputLine[i] == '1') {
                mostCommonBit[i]++;
            } else {
                mostCommonBit[i]--;
            }
        }
        input.push_back(inputLine);
        std::printf("input: %s\n", inputLine.c_str());
    }
    // consider row[k], bit [i]
    for(int i = 0; i < 12; i++) {
        if(flag) {
            break;
        }
        int common = mostCommonBit[i] >= 0 ? 1 : 0;
        for(int k = 0; k < 1000; k++ ) {
            std::printf("k: %d, i: %d\n", k, i);
            // consider only the first bit, find most common (1 if equal)
            // remove all values that dont
            //this is bad
            if ((int)(input.at(k)[i]) != common) {
                input.at(k) = "";
            }
        }
        
    }
    
    //file.close();
}