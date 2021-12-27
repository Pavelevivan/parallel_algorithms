#include <iostream>
#include <string.h>

using namespace std;

int countWords(char *str)
{
	int nWords = 0;
    bool checker = false; 

    while (*str) {

        if (*str == ' ') {checker = false;}

        else if (*str == '\\') {
            ++str;
            if (*str == 'n' || *str == 't') {checker = false;}
        }

        else if (checker == false) {
            checker = true;
            ++nWords;
        }

        ++str;
    }
 
    return nWords;
}

int main(int argc, char* argv[])
{
    int nWords = 0;

    nWords = countWords(argv[1]);
    
    cout << "Number of words = " << nWords << "\n";

    return 0;
}