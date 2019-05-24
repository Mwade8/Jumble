// Jumble program: Using standard lib hash tables to implement a simple dictionary/anagram program
// how to use ./a.out filename.txt
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//rearrangez the characters in a string
//so that they are sorted (according to their ASCII value).
void ssort(string &s) {

        /*
        strings are "iterable" objects and so have the begin()
        and end() functions.  These functions (in a pretty
        abstract way) return "iterators" which specify the
        "beginning" and "end" of the associated object).

        Thus, this call is asking the sort function to sort
        the entire string s.
        */
        sort(s.begin(), s.end());
}

void printReport(int wordCount,int numClasses,int largestClass,string largestClassKey,unordered_map<string, vector<string>> &anaMap){
    cout << "REPORT:\n\n";

    cout << "num_words              : " << wordCount << endl;
    cout << "num_classes            : " << numClasses << endl;
    cout << "size-of-largest-class  : " << largestClass << endl;
    cout << "largest-class-key      : '" << largestClassKey << "'" << endl;
    cout << "members of largest class: \n";

    int high = anaMap[largestClassKey].size();
    for(int i = 0; i < high; i++){
        cout << "  '" << anaMap[largestClassKey][i] << "'" << endl;
    }

}
 void dealWithWord(string &word,int &largestClass,string &largestClassKey, int &wordCount,unordered_map<string, vector<string>> &anaMap){
    string unsortedWord = word; //save the unsorted word

    ssort(word); //word = key

    //now push word back at that "key's index", key is word, which is sorted alphabetically
    anaMap[word].push_back(unsortedWord);

    wordCount=wordCount+1;

    //check if the bookeeping data needs to be updated
    if ( anaMap[word].size() > largestClass) {
        largestClass = anaMap[word].size();
        largestClassKey = word;
    }
}


int main(int argc, char *argv[]) {
        unordered_map<string, vector<string>> anaMap;
        ifstream file;
        string word;

        int i=0;
        int high=0;

        int wordCount = 0;
        int largestClass = 0;
        int numClasses = 0;
        string largestClassKey;

        //check if the command line args make sense
        if (argc != 2) {
            cout << "usage:  ./freq <filename>\n";
            cout << "goodbye\n";
            return 1;
        }

        //argv[1] is a C-string which is the filname specified by the user.  Let's try to open it.
        file.open(argv[1], ios::in);

        //check if file cannot be opened
        if (!file.is_open()) {
            cout << "Error: could not open file '" <<
                    argv[1] << "'\n";
            cout << "goodbye\n";
            return 1;
        }

        cout << "reading input file...\n";

        //read in the contents of the file
        while (file >> word) {
            dealWithWord(word,largestClass,largestClassKey,wordCount,anaMap);
        }

        numClasses = anaMap.size(); // update booking variable

        //now user inputs jumbled strings
        cout << "start entering jumbled words (ctrl-d to terminate) ctrl-z on windows...\n";

        cout << "> "; //formatiing

        //user inputs anagrams
        while (cin >> word) {
            ssort(word);

            if (anaMap[word].empty()) {
                cout << "no anagrams found...try again\n";
            }
            else {
                cout << "English Anagrams Found:\n";
                i = 0;
                high = anaMap[word].size();
                while (i < high) {
                        cout << "       " << anaMap[word][i] << endl;
                        i=i+1;
                }
            }
            cout << "> "; //formatting
        }

        //print results
        printReport(wordCount,numClasses,largestClass,largestClassKey,anaMap);

        return 0;
}
