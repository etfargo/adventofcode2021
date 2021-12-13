#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

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
    //part2();
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
    vector<string> input, tmp, workingset;
    vector<int> mostCommonBit {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    int amount, pos, o2, co2;
    bool flag = true;
    string o2Gen, co2scrub;

    while (file  >> inputLine)
    {
        input.push_back(inputLine);
        std::printf("input: %s\n", inputLine.c_str());
    }
    // o2 thing
    // for each bit if most common bit one, keep only those, else keep only 0
        // if length is of accepted is 1 end, else repeat
    int curBit = 0;
    tmp = input;
    while(flag) {
        // --- first update the mostCommonBit for selection (tmp) ---
        // reset most common bit for tmp
        mostCommonBit = {0,0,0,0,0,0,0,0,0,0,0,0};
        // loop through temp
        for( int i = 0; i < tmp.size(); i++) {
            // reset bit, then inc/dec each 
            for(int j = 0; j < tmp[i].length(); j++) {
                if (tmp[i][j] == '1') {
                    mostCommonBit[j]++;
                } else {
                    mostCommonBit[j]--;
                }
            }
        }
        // --- now you can go and do the checking ---
        int mcb = mostCommonBit[curBit] >= 0 ? 1 : 0;
        for(int i = 0; i < tmp.size(); i++) {
            if((tmp[i][curBit] - '0') == mcb ) {
                workingset.push_back(tmp[i]);
            }
        }
        if(workingset.size() > 1) {
            tmp = workingset;
            workingset.clear();
            // continue
        } else {
            flag = false;
            printf("you 02 gen value is: %s\n", workingset[0].c_str());
            // get that value!
            o2Gen = workingset[0];
        }
        curBit++;
    }
    // reset for next search
    flag = true;
    workingset.clear();

    // c02 thing
    // for each bit if least common bit one, keep only those, else keep only 0
        // if length is of accepted is 1 end, else repeat
    curBit = 0;
    tmp = input;
    while(flag) {
        // --- first update the mostCommonBit for selection (tmp) ---
        // reset most common bit for tmp
        mostCommonBit = {0,0,0,0,0,0,0,0,0,0,0,0};
        // loop through temp
        for( int i = 0; i < tmp.size(); i++) {
            // reset bit, then inc/dec wach 
            for(int j = 0; j < tmp[i].length(); j++) {
                if (tmp[i][j] == '1') {
                    mostCommonBit[j]++;
                } else {
                    mostCommonBit[j]--;
                }
            }
        }
        // --- now you can go and do the checking ---
        int lcb = mostCommonBit[curBit] >= 0 ? 0 : 1;
        for(int i = 0; i < tmp.size(); i++) {
            if((tmp[i][curBit] - '0') == lcb ) {
                workingset.push_back(tmp[i]);
            }
        }
        if(workingset.size() > 1) {
            tmp = workingset;
            workingset.clear();
            // continue
        } else {
            flag = false;
            printf("you c02 value is: %s\n", workingset[0].c_str());
            // get that value!
            co2scrub = workingset[0];
        }
        curBit++;
    }

    o2 = std::stoi(o2Gen, nullptr, 2);
    co2 = std::stoi(co2scrub, nullptr, 2);

    printf("O2 is: %d, CO2 is: %d, Multiplied is: %d\n", o2, co2, o2*co2);
}