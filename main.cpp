#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <random>

using std::string;

string read_file(const string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open file " + filename);

    string line;
    unsigned int num_lines = 0;
    while(std::getline(file, line)) 
    {
        if(line.empty()) continue;
        num_lines++;
    }    

    int random_line = rand() % num_lines;
    std::cout << "Random line: " << random_line << "\n";

    file.clear();
    file.seekg(0, std::ios::beg);
    int index = 0; 
    while(std::getline(file, line)) 
    {
        if(line.empty()) continue;

        if(index == random_line) break;
        
        index++;
    }

    file.close();

    return line;
}

int main() {
    srand(time(0));
    
    string random_word = read_file("words_alpha.txt");

    string hangman_word;
    for (size_t i = 0; i < random_word.length(); i++)
    {
        hangman_word += "_ ";
    }
    
    std::cout << "Welcome to Hangman!\n";
    std::cout << "The word has " << random_word.length() << " letters\n";
    std::cout << "The word is: " << hangman_word << "\n";

    int tries = 0;

    while (tries < 6)
    {
        char letter;
        std::cout << "Enter a letter: ";
        std::cin >> letter;

        bool found = false;
        for (size_t i = 0; i < random_word.length(); i++)
        {
            if (random_word[i] == letter)
            {
                hangman_word[i * 2] = letter;
                found = true;
            }
        }

        if (!found)
        {
            tries++;
            std::cout << "Letter not found. Tries left: " << 6 - tries << "\n";
        }
        else
        {
            std::cout << "The word is: " << hangman_word << "\n";
        }

        if (hangman_word.find("_") == string::npos)
        {
            std::cout << "Congratulations! You found the word!\n";
            break;
        }
    }

    if (tries == 6)
    {
        std::cout << "You lost! The word was: " << random_word << "\n";
    }

    return 0;
}