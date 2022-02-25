//Hangman game
#include <iostream>  
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <windows.h> 
using namespace std;
 
bool run;

void changeColor(int desiredColor){   
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor); 
} 
  
string getWord() {
    ifstream words_file;      
    try {                     
        words_file.open("words.txt");
    }
    catch (...) {  // Block of code to handle errors 
	               //words_file.fail()) //Supports unpredictable exceptions
        cout << "Error" << endl;
        run = false;
    }
        
    string line;

    vector<string> words;   
    string word;
    return word;
    
}
void endGame() {
    cout << "                              Thank you for playing. Goodbye!                          " << endl;
    run = false;
}

string updateWord(string word ,vector<int> characterLocations , char to_update) {
    char dummy;
    vector<char> word_vec(word.length(),dummy);
                                                              
    for (int i = 0; i < word.length(); i++) {                
        vector<int>::iterator found = find(characterLocations.begin(), characterLocations.end(), i); 
        if(found != characterLocations.end()) {              
		 
            word_vec[i] = to_update;
            characterLocations.erase(found);               
        }
        else {
            word_vec[i] = word[i];
        }
    }
    

    string result(word_vec.begin(),word_vec.end()); 

    return result;
}

bool has_only_alpha(string word) { 
    char c;
    for (int i = 0; i < word.length(); i++) {
        c = word.at(i); 

        if (! ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z') ) ) { 
            return false;
        }
    }
    return true;
}

vector<int> findLocation(string sample, char findIt)
{
    vector<int> characterLocations;
    for(int i =0; i < sample.size(); i++)
        if(sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

void toLower(string& word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}
void ShowHeader() 
{
	system("cls");
		    cout <<"                                             "<< "  O" << endl;
            cout <<"                                             "<< " -|-" << endl;
            cout <<"                                             "<<" / /"<< endl;
	cout<<endl<<"          +-----------------------------------------------------------------------------+";
	cout<<endl<<"          |                                Hangman Game                                 |";
	cout<<endl<<"          +-----------------------------------------------------------------------------+";
	cout<<endl<<endl;
            cout <<"                                             "<< "I===" << endl;
            cout <<"                                             "<< "I  O" << endl;
            cout <<"                                             "<< "I -|-" << endl;
            cout <<"                                             "<< "I / /"<< endl;                                          
	return;
}


int main() {
	system("color 70");
	ShowHeader();
    

    run = true; //bool run=1

    while (run) {

        string gameMode;
        string player1,player2;
        
    cout<<endl<<"          +-----------------------------------------------------------------------------+";
	cout<<endl<<"          |                         Hello! Welcome to the HANGMAN game                  |";
	cout<<endl<<"          +-----------------------------------------------------------------------------+";
	cout<<endl<<endl;
        

        cout << "                                    Please type in your name, PLAYER 1:)" << endl;
        cin >> player1;
        cout << "                                    Please type in your name, PLAYER 2:)" << endl;
        cin >> player2;
        cout <<"                                    "<< "OK " << player1 << " and " << player2 << ". Let's start game!" << endl<<endl<<endl;

        cout << "|press 1 to play with your freind" << endl;
        
        cout << "|OR Type 'quit' to end the game." << endl;

        cin >> gameMode;
        
        string hidden_word = "";
        string input;

        if (gameMode == "1") {
            bool isValidWord = false;

            cout << "            =========PLAYER 1'S TURN=========" << endl;
            while (true) {

                cout << "Give me a word: ";
                cin >> input;
                isValidWord = has_only_alpha(input);
                if (isValidWord) {
                    for (int i = 0; i < 10; i++) { 
                        cout << "\n\n\n" << endl<<endl;
                    }
                    break;
                }
                cout << "XXXX  Only letters are allowed in words. XXXX" <<endl<<endl;
            }

            for (int j = 0; j < input.length(); j++) {
                hidden_word +=   "_" ;
            }

            toLower(input);
   
            cout << "            =========PLAYER 2'S TURN=========" << endl;

           bool game_over = false;

            int num_tries = input.length() + 1;   

            cout << "  The word that your friend gave was " << input.length() << " letters long." << endl<<endl<<endl;

            cout << "  Updated Word: " << hidden_word << endl<<endl<<endl;

            while (num_tries > 0) {
                char letter;
                cout << "         Number of tries left: " << num_tries << endl<<endl;
                cout << "         Give me a letter you think is in the word: ";
                cin >> letter;
                
                
                stringstream stream;
                string str;

                stream << letter;
                stream >> str;

                toLower(str);
                            
                size_t found = input.find(letter);
                if (found != string::npos) { 
                    cout << "++++++++++   That letter is in the word!  ++++++++++"  << endl<<endl;
                    vector<int> characterLocations = findLocation(input,letter);



                    hidden_word = updateWord(hidden_word, characterLocations, letter);
                    if (hidden_word == input) {
                        game_over = true;
                        break;
                    }
                    cout << "  Updated Word: " << hidden_word << endl<<endl;



                }
                else {
                    cout << "XXXXXXXXXX   That letter is not in the word. XXXXXXXXXX" << endl<<endl;
                }

                num_tries--;
            }

            if (num_tries != 0) {
            	changeColor(32);
                cout << "                                           Player 2 wins!:)                                             " << endl;
                cout <<"    _____      ___                   ____      ______         _      ________  ____    "<<endl;
                cout <<"  /          /   \\    | \\    |    /         |      \\       / \\         |      /     "<<endl;
                cout <<"  |         |     |   |  \\   |    |   ___   |______/      /___\\        |      \\___ "<<endl;
                cout <<"  |         |     |   |   \\  |    |     |   |     \\      /     \\       |          |"<<endl;
                cout <<"  \\_____     \\___/    |    \\ |    \\_____|   |      \\    /       \\      |      ____|"<<endl<<endl<<endl;
                cout <<"  O " << endl;
                cout <<" -|-" << endl;
                cout <<" / /"<< endl<<endl<<endl;
                changeColor(4);
                cout << "                                           Player 1 lose:(!                                             "<< endl;
                
                cout<<"   ____       _      _         _  ____     ___             _____  _____            " <<endl;                
                cout<<"  /          / \\    | \\      / | |        /   \\ \\      /  |      |     \\" <<endl;
                cout<<" /  ____    /___\\   |  \\    /  | |____   |     | \\    /   |_____ |_____/" <<endl;
                cout<<" |      |  /     \\  |   \\  /   | |       |     |  \\  /    |      |    \\" <<endl;
                cout<<"  \\___ |  /       \\ |    \\/    | |____    \\___/    \\/     |_____ |     \\" <<endl<<endl;
				cout << "I===" << endl;
                cout << "I  O" << endl;
                cout << "I -|-" << endl;
                cout << "I / /"<< endl;               
            }
            else {
            	changeColor(32);
                cout << "                                           Player 1 wins!                                               " << endl;

                cout <<"    _____      ___                   ____      ______         _      ________  ____    "<<endl;
                cout <<"  /          /   \\    | \\    |    /         |      \\       / \\         |      /     "<<endl;
                cout <<"  |         |     |   |  \\   |    |   ___   |______/      /___\\        |      \\___ "<<endl;
                cout <<"  |         |     |   |   \\  |    |     |   |     \\      /     \\       |          |"<<endl;
                cout <<"  \\_____     \\___/    |    \\ |    \\_____|   |      \\    /       \\      |      ____|"<<endl<<endl;
                cout <<"  O " << endl;
                cout <<" -|-" << endl;
                cout <<" / /"<< endl<<endl<<endl;                
                changeColor(4);
                cout<<"                                            player 2 lose:(                                              "<<endl;
	    
		        cout<<"   ____       _      _         _  ____     ___             _____  _____            " <<endl;
                cout<<"  /          / \\    | \\      / | |        /   \\ \\      /  |      |     \\" <<endl;
                cout<<" /  ____    /___\\   |  \\    /  | |____   |     | \\    /   |_____ |_____/" <<endl;
                cout<<" |      |  /     \\  |   \\  /   | |       |     |  \\  /    |      |    \\" <<endl;
                cout<<"  \\___ |  /       \\ |    \\/    | |____    \\___/    \\/     |_____ |     \\" <<endl<<endl;
                cout << "I===" << endl;
                cout << "I  O" << endl;
                cout << "I -|-" << endl;
                cout << "I / /"<< endl;                
            }
cout<<"*************************************************************************************************************"<<endl<<endl;
          changeColor(7);
            cout << "                              *The word you gave me was:  <<"<< input <<">>"<< endl<<endl;
            run = false;
        }
               

        else if (gameMode == "quit") {
            run = false;
        }

    }
    endGame();
cout<<"**************************************************************************************************************";
    return 0;
}



