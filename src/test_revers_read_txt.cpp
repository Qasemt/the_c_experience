#include "test_revers_read_txt.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

int  ll(std::ifstream& in, bool from_end, int pos, int numberOfline)
{
    std::string tmp;
    int length = 0;
    int size_file=1000;
    char c = '\0';
    length = pos;
    // loop backward over the file
    int newpos = 0;

    if (from_end)
        newpos = length - 2;

    while (numberOfline > 0)
    {
        if (from_end)
        {
            for (; newpos > 0; newpos--)
            {
                in.seekg(newpos);
                c = in.get();
                if (c == '\r' || c == '\n')//new line?
                {
                    numberOfline--;
                    break;
                }
            }
        }
        else
        {
            for (; newpos < size_file; newpos++)
            {
                in.seekg(newpos);
                c = in.get();
                if (c == '\r' || c == '\n')//new line?
                {
                    numberOfline--;
                    break;
                }
            }
        }

        std::getline(in, tmp);//read last line
        std::cout << tmp << std::endl; // print it


        if (from_end) {
            if (newpos == 0)
                break;
            newpos = newpos - 2;
        }
        else
        {
            if (newpos >= size_file)
                break;
            newpos = newpos + 2;
        }

    }
    return  newpos;
}


void read_line(bool from_end, int number_line)
{
    ifstream in("d://t.txt",from_end?std::ios_base::ate:0);
    if (in)
    {
        int pos1 = ll(in, from_end,static_cast<int>(in.tellg()), 1);
    }
    in.close();
}
void run_test_read_text(void)
{
    read_line(false, 2);
}