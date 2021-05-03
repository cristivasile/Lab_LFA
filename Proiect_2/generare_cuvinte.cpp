#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

ifstream f("input.in");

char symbols[500];
unordered_set<string> words;
unordered_set<string> checkedExpressions;
unordered_map<char, vector<string>> expressions;
int lenS;
int length;

bool isSymbol(char c) {
    for (int i = 0; i < lenS; i++)
        if (c == symbols[i])
            return 1;
    return 0;
}

bool hasSymbols(string s) {
    for (int i = 0; i < s.size(); i++)
        if (isSymbol(s[i])) {
            return 1;
        }
    return 0;
}

int countLetters(string s) {
    int nr = 0;
    for (int i = 0; i < s.size(); i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            nr++;
    return nr;
}

void generateWords(string word) {

    cout<<word<<"\n";

    bool wordNotChecked = checkedExpressions.find(word) != checkedExpressions.end();

    if(!wordNotChecked && word.size() <= length+5 && countLetters(word)<=length){
        checkedExpressions.insert(word);
        cout << word << "\n";
        if (countLetters(word) == length && !hasSymbols(word)) {
            words.insert(word);
        }
        else if(countLetters(word)<=length){
            for (int i = 0; i < word.size(); i++)
                if (isSymbol(word[i]))
                    for (string expression : expressions[word[i]]) {
                        string newWord;
                        newWord = word.substr(0, i) + expression + word.substr(i + 1, word.length());
                        generateWords(newWord);
                    }
        }
    }
}

int main()
{
    // citire ------------------------------------------------------------------------------------------------------------------------------------------------------------------
    string read;         //auxiliar pt citire
    getline(f,read);

    for (auto i = 5; i < read.size(); i++)
        if(read[i]>='A' && read[i]<='Z')
            symbols[lenS++] = read[i];

    getline(f, read);    //linia care contine alfabetul, pe care o ignoram

    do{
        getline(f, read);
        char symbol;
        symbol = read[0];
        string transition = read.substr(5, read.size());
        if (transition != "LAMBDA")
            expressions[symbol].push_back(transition);
        else expressions[symbol].push_back("");
    }while (f.eof() != 1);

    cout << "Se vor afisa cuvintele cu lungimea: ";
    cin >> length;

    for (string expression : expressions['S']) {
        string word = expression;
        generateWords(word);
    }

    cout << "Cuvintele cu lungime " << length << " sunt: ";

    for (auto& word : words)
        cout << word <<" ";
}
