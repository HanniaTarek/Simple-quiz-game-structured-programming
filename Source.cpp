#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <windows.h>

#define MAX 1000

using namespace std;

int movies(int& score);
int music(int& score);
int sports(int& score);
int science(int& score);
void tokenize(string s, string del = " ");

string parsed_string[2];

struct userinfo {
    string name;
    int userscore;
};
int score = 0;
int main() {
    system("color 03");
    ofstream outfile;
    string line, scores_file[MAX];
    ifstream myfile("score.txt");
    int file_length = 0, input_name_line_number = -1, old_score = -1;
    char field;
    userinfo x;
    char user_check;
    bool new_user = true;
    stringstream score_string;
    cout << "\t\t\t\t\t************************" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t* Welcome to quiz game *" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t*                      *" << endl;
    cout << "\t\t\t\t\t************************" << endl;
    cout << "Are you a new user ? (Y/N)\n";
    cin >> user_check;

    if ((user_check == 'y') || (user_check == 'Y')) {
        cout << "Please create a username:\n";
        cin >> x.name;
        transform(x.name.begin(), x.name.end(), x.name.begin(), ptr_fun <int, int>(tolower));
    }
    else {
        cout << "Please enter your username:\n";
        cin >> x.name;
        transform(x.name.begin(), x.name.end(), x.name.begin(), ptr_fun <int, int>(tolower));
        new_user = false;
    }
    char* ptr = &field;
    cout << "Which field do you want to be asked in ?(Please enter from 1-4)\n";
    cout << "1. Movies\n2. Music\n3. Sports\n4. Science\n";
    cin >> *ptr;

    cout << "_" << endl;
    bool check;

    do {
        switch (field) {
        case '1':
            movies(score);
            check = true;
            break;
        case '2':
            music(score);
            check = true;
            break;
        case '3':
            sports(score);
            check = true;
            break;
        case '4':
            science(score);
            check = true;
            break;
        default:
            cout << "Incorrect\nRe-enter from 1-4\n";
            cin >> field;
            check = false;
            break;
        }
    } while (!check);


    if (new_user) {
        outfile.open("score.txt", ios::app);
        x.userscore = score;
        outfile << x.name << " " << x.userscore << endl;
        outfile.close();
        cout << "Your current score is: " << score << endl;
        cout << "Leaderboard: \n\n";
        myfile.is_open();
        cout << myfile.rdbuf();
        myfile.close();
    }

    else {
        myfile.is_open();
        while (getline(myfile, line))
        {
            scores_file[file_length] = line;
            file_length++;
        }

        myfile.close();
        for (int i = 0; i <= file_length; i++)
        {
            size_t found = scores_file[i].find(x.name);
            if (found != string::npos)
            {
                input_name_line_number = i;
            }

        }
        for (int i = 0; i < 3; i++) {
            tokenize(scores_file[input_name_line_number], " ");
            old_score = stoi(parsed_string[i]);
         }
        
        tokenize(scores_file[input_name_line_number], " ");

        old_score = stoi(parsed_string[1]);
        if (score > old_score)
        {
            score_string << score;
            string temp;
            score_string >> temp;
            scores_file[input_name_line_number] = x.name + " " + temp;
        }
        else {
            score = old_score;
        }
        cout << "Your current score is: " << score << endl;
        cout << "Leaderboard: \n\n";
        ofstream ofs("score.txt");
        for (int j = 0; j < file_length; j++)
        {

            ofs << scores_file[j] << endl;
            cout << scores_file[j] << endl;
        }
        ofs.close();
    }

    system("pause");
}


int movies(int& score) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    score = 0;
    string questions[5];
    questions[0] = "What kind of animal is Aslan in 'The Chronicles of Narnia'?\na.Lion\nb.Fish\nc.Giraffe\nd.Bird\n";
    questions[1] = "What was Nemo's father friend's name\na.Lori\nb.Dori\nc.Gori\nd.Flori\n";
    questions[2] = "In the movie 'Monsters, Inc.' what does the company in Monsters, Inc. do?(a-d)\na.Generates Electricity\nb.Play video games\nc.Dance\nd.Babysit\n";
    questions[3] = "When Nemo was put in a fish tank in 'Finding Nemo', what new name did the other fish give him?(a-d)\na.Orange\nb.Clown\nc.Luffy\nd.Sharkbait\n";
    questions[4] = "Who said the quote \"I killed Mufasa\"?\na.Simba\nb.Scar\nc.Timon\nd.Pumba\n";

    char answers[5];
    answers[0] = 'a';
    answers[1] = 'b';
    answers[2] = 'a';
    answers[3] = 'd';
    answers[4] = 'b';
    char answer;

    for (int i = 0; i < 5; i++) {
        cout << questions[i] << endl;
        cin >> answer;
        answer = putchar(tolower(answer));
        if (answer == answers[i]) {
            cout << "\nCorrect answer\n";
            score += 100;
        }
        else if (answer != answers[i]) {
            cout << "\nIncorrect answer\n";
            if (score > 0) {
                score -= 50;
            }
        }
    }
    cout << "Your current score is: " << score << endl;
    if (score >= 250) {
        cout << "\t\t\t\t\tCongratulations! you have passed round 1\n\n";
        cout << "Round 2:\n\n";

        string question[8];
        question[0] = "How many dwarves were with snow white?\na.8\nb.6\nc.9\nd.7\n";
        question[1] = "How many infinty stones are there in MCU movies?\na.3\nb.5\nc.6\nd.7\n";
        question[2] = "Who's Loki's biological father?\na.Lofi\nb.Farbauti\nc.Odin\nd.Thor\n";
        question[3] = "What did Jimmy Neutron used to say whe he wanted to solve a problem?\na.think,think,think\nb.try,try,try\nc.solve,solve,solve\nd.do it,do it,do it\n";
        question[4] = "What's Mr. Crab's favorite thing in life?\na.His daughter\nb.Spongebob\nc.Money\nd.His restaurant\n";
        question[5] = "How many brothers does prince Hans of the southren Isles have in Frozen?\na.12\nb.16\nc.10\nd.8\n";
        question[6] = "What is the name of Andy's neighbor in Toy Story?\na.steve\nb.sid\nc.tony\nd.phil\n";
        question[7] = "What does Hakuna Matata mean?\na.no fear\nb.no mistakes\nc.good bye\nd.no worries\n";
        char answers2[8];
        answers2[0] = 'd';
        answers2[1] = 'c';
        answers2[2] = 'b';
        answers2[3] = 'a';
        answers2[4] = 'c';
        answers2[5] = 'a';
        answers2[6] = 'b';
        answers2[7] = 'd';
        for (int i = 0; i < 8; i++) {
            cout << question[i] << endl;
            cin >> answer;
            answer = putchar(tolower(answer));
            if (answer == answers2[i]) {
                cout << "\nCorrect answer\n";
                score += 100;
            }
            else if (answer != answers2[i]) {
                cout << "\nIncorrect answer\n";
                if (score > 0) {
                    score -= 50;
                }
            }
        }
        cout << "\t\t\t\t\tCongrats! you have cleared the game :)\n";
    }
    else
    {
        cout << "\t\t\t\t\tGame over :(\n";
        cout << "\t\t\t\t\t___" << endl;
        score = 0;
    }
    return score;
}


int music(int& score) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    score = 0;
    string questions[5];
    questions[0] = "Guess the artist!\njust the way you are\na.The Weekend\nb.Bruno mars\nc.Maroon 5.\nd.Issac gracie\n";
    questions[1] = "Guess the artist!\nNear,far,wherever you are.....\na.Elton john\nb.Celine dion\nc.Ed sheeran\nd.Sia\n";
    questions[2] = "Complete the lyrics:)\nPut you head on my.....\na.chest\nb.bed\nc.shoulder\nd.heart\n";
    questions[3] = "Guess the song!\ncollab. between taylor swift and zayn\na.Pillow talk\nb.blank space\nc.dusk till dawn\nd.I don't wanna live forever\n";
    questions[4] = "Guess the artist!\n We are only getting older baby.....\na.Maroon 5\nb.Beach house\nc.One direction\nd.The Beatles.\n";

    char answers[5];
    answers[0] = 'b';
    answers[1] = 'b';
    answers[2] = 'c';
    answers[3] = 'd';
    answers[4] = 'c';
    char answer;
    for (int i = 0; i < 5; i++) {
        cout << questions[i] << endl;
        cin >> answer;
        answer = putchar(tolower(answer));
        if (answer == answers[i]) {
            cout << "\nCorrect answer\n";
            score += 100;
        }
        else {
            cout << "\nIncorrect answer\n";
            if (score > 0) {
                score -= 50;
            }
        }
    }
    cout << "Your current score is: " << score << endl;
    if (score >= 250) {
        cout << "\t\t\t\t\tCongratulations! you have passed round 1\n\n";
        cout << "Round 2:\n\n";
        string questions[8];
        questions[0] = "Guess the artist!\nAll my friends are heathens....\na.The chain smokers\nb.Beach house\nc.21 pilots\nd.Nothing but thieves\n";
        questions[1] = "Complete the lyrics:)\nCity of stars....\na.are you there for me\nb.are you shining just for me\nc.Are you real\nd.you are just like a dream\n ";
        questions[2] = "Complete the lyrics:)\nCause i'll give you...\na.All of me\nb.Everything you need\nc.What you want\nd.Everything love\n";
        questions[3] = "How many members are there in the Jonas brothers band?\na.4\nb.3\nc.5\nd.2\n";
        questions[4] = "Guess the song!\ncollab between halsey and khalid\na.location\nb.Better\nc.Colors\nd.Eastside";
        questions[5] = "In what year did Fergie, of Black Eyed Peas fame, make her first solo album The Dutchess?\na.2006\nb.2009 \nc.2010\nd.2011\n";
        questions[6] = "What is the other language that Celine Dion regularly sang in throughout the 90s?\na.English\nb.French\nc.German\nd.Turkish\n ";
        questions[7] = "How old was Britney Spears when her hit song 'Baby One More Time' came out in 1998?\na.18\nb.20\nc.17\nd.23\n";
        char answers[8];
        answers[0] = 'c';
        answers[1] = 'b';
        answers[2] = 'a';
        answers[3] = 'b';
        answers[4] = 'd';
        answers[5] = 'a';
        answers[6] = 'b';
        answers[7] = 'c';
        char answer;
        for (int i = 0; i < 8; i++)
        {
            cout << questions[i] << endl;
            cin >> answer;
            answer = putchar(tolower(answer));
            if (answer == answers[i])
            {
                cout << "\nCorrect answer\n";
                score += 100;
            }
            else {
                cout << "\nIncorrect answer\n";
                if (score > 0) {
                    score -= 50;
                }
            }
        }
        cout << "\t\t\t\t\tCongrats! you have cleared the game :)\n";
    }
    else
    {
        cout << "\t\t\t\t\tGame over :(\n";
        cout << "\t\t\t\t\t___" << endl;
        score = 0;
    }
    return score;
}

int sports(int& score) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    score = 0;
    string questions[5];
    questions[0] = "The Olympics are held every how many years?\na.5 years\nb.6 years\nc.4 years\nd.3 years\n";
    questions[1] = "What sport is best known as the \"King of Sports\"?\na.Soccer\nb.Basketball\nc.Volleyball\nd.Golf\n";
    questions[2] = "In soccer, what body part can't touch the ball?\na.Head\nb.Hand\nc.Knee\nd.Chest\n";
    questions[3] = "What African country was the first ever to qualify for a World Cup?\na.Nigeria\nb.Egypt\nc.Algeria\nd.Morocco\n";
    questions[4] = "How many rings are there on the Olympic flag?\na.3\nb.6\nc.4\nd.5\n";

    char answers[10];
    answers[0] = 'c';
    answers[1] = 'a';
    answers[2] = 'b';
    answers[3] = 'b';
    answers[4] = 'd';
    char answer;
    for (int i = 0; i < 5; i++) {
        cout << questions[i] << endl;
        cin >> answer;
        answer = putchar(tolower(answer));
        if (answer == answers[i]) {
            cout << "\nCorrect answer\n";
            score += 100;
        }
        else {
            cout << "\nIncorrect answer\n";
            if (score > 0) {
                score -= 50;
            }
        }
    }
    cout << "Your current score is: " << score << endl;
    if (score >= 250) {
        cout << "\t\t\t\t\tCongratulations! you have passed round 1\n\n";
        cout << "Round 2:\n\n";

        string question[8];
        question[0] = "which country has played in each and every world cup till date?\na.Brazil\nb.Egypt\nc.Spain\nd.Russia\n";
        question[1] = "Who's known as the godfather of boxing?\na.Mike Tyson\nb.Mohamed Ali\nc.Floyd Mayweather\nd.Manny Pacquiao\n";
        question[2] = "For which country did David Beckham played for?\na.Spain\nb.Bravil\nc.Egypt\nd.England\n";
        question[3] = "How many goals are scored in hat-trick?\na.3\nb.1\nc.4\nd.5\n";
        question[4] = "In which country will the next football world cup would be held?\na.Brazil\nb.France\nc.USA\nd.Qatar\n";
        question[5] = "Which is the national sport of Canada?\na.Football\nb.Ice hockey\nc.Tennis\nd.Volleyball\n";
        question[6] = "What sport did Kobe Bryant play?\na.Basketball\nb.Football\nc.Ice skating\nd.Tennis\n";
        question[7] = "Where was the olympics first held?\na.Paris\nb.Rome\nc.Greece\nd.Germany\n";
        char answers2[8];
        answers2[0] = 'a';
        answers2[1] = 'b';
        answers2[2] = 'd';
        answers2[3] = 'a';
        answers2[4] = 'd';
        answers2[5] = 'b';
        answers2[6] = 'a';
        answers2[7] = 'c';

        char answer;
        for (int i = 0; i < 8; i++) {
            cout << question[i] << endl;
            cin >> answer;
            answer = putchar(tolower(answer));
            if (answer == answers2[i]) {
                cout << "\nCorrect answer\n";
                score += 100;
            }
            else {
                cout << "\nIncorrect answer\n";
                if (score > 0) {
                    score -= 50;
                }
            }
        }
        cout << "\t\t\t\t\tCongrats! you have cleared the game :)\n";
    }
    else
    {
        cout << "\t\t\t\t\tGame over :(\n";
        cout << "\t\t\t\t\t___" << endl;
        score = 0;
    }
    return score;
}

int science(int& score) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    score = 0;
    string questions[5];
    questions[0] = "........ gas is important so that we can breath.\na.Carbon dioxide\nb.Nitrogen\nc.Oxygen\nd.Helium\n";
    questions[1] = "What is the nearest planet to the sun?\na.Earth\nb.Mercury\nc.Venus\nd.Deimos\n";
    questions[2] = "What is the rarest blood type?\na.AB Negative\nb.A Negative\nc.B Positive\nd.O Positive\n";
    questions[3] = "How many hearts does an octopus have?\na.3\nb.8\nc.4\nd.5\n";
    questions[4] = "What's the boiling point of water?|\na.90\nb.100\nc.70\nd.95\n";

    char answers[5];
    answers[0] = 'c';
    answers[1] = 'b';
    answers[2] = 'a';
    answers[3] = 'a';
    answers[4] = 'b';
    char answer;
    for (int i = 0; i < 5; i++) {
        cout << questions[i] << endl;
        cin >> answer;
        answer = putchar(tolower(answer));
        if (answer == answers[i]) {
            cout << "\nCorrect answer\n";
            score += 100;
        }
        else {
            cout << "\nIncorrect answer\n";
            if (score > 0) {
                score -= 50;
            }
        }
    }
    cout << "Your current score is: " << score << endl;
    if (score >= 250) {
        cout << "\t\t\t\t\tCongratulations! you have passed round 1\n\n";
        cout << "Round 2:\n\n";
        string questions2[8];
        questions2[0] = "Which system of the body controls the senses?\na.Digestive system\nb.Nervous system\nc.Skeletal system\nd.Circulatory system\n";
        questions2[1] = "Earth is located in which galaxy?\na.Sombrero galaxy\nb.Black eye galaxy\nc.Cartwheel galaxy\nd.Milky way galaxy\n";
        questions2[2] = "How many elements are there in the periodic table?\na.112\nb.120\nc.117\nd.118\n";
        questions2[3] = "What is the smartest mammal?\na.Whales\nb.Dolphins\nc.Elephants\nd.Kangaroos\n";
        questions2[4] = "Diabetes happens because of problems in which organ of the body?\na.Pancreas\nb.Liver\nc.Heart\nd.Kidneys\n";
        questions2[5] = "Which is the strongest sense in a dog?\na.Touch\nb.Hearing\nc.Smell\nd.Taste\n";
        questions2[6] = "What is the hardest substance available on earth?\na.Gold\nb.Iron\nc.Diamond\nd.Platinum\n";
        questions2[7] = "Which planet of our solar system has 53 moons?\na.Saturn\nb.Venus\nc.Mercury\nd.Neptune\n";
        char answers2[8];
        answers2[0] = 'b';
        answers2[1] = 'd';
        answers2[2] = 'd';
        answers2[3] = 'b';
        answers2[4] = 'a';
        answers2[5] = 'c';
        answers2[6] = 'c';
        answers2[7] = 'a';
        char answer2;
        for (int i = 0; i < 8; i++) {
            cout << questions2[i] << endl;
            cin >> answer2;
            answer2 = putchar(tolower(answer2));
            if (answer2 == answers2[i]) {
                cout << "\nCorrect answer\n";
                score += 100;
            }
            else {
                cout << "\nIncorrect answer\n";
                if (score > 0) {
                    score -= 50;
                }
            }
        }
        cout << "\t\t\t\t\tCongrats! you have cleared the game :)\n";
    }
    else
    {
        cout << "\t\t\t\t\tGame over :(\n";
        cout << "\t\t\t\t\t___" << endl;
        score = 0;
    }
    return score;
}
void tokenize(string s, string del)
{
    int start = 0;
    int i = 0;

    int end = s.find(del);
    while (end != -1) {
        parsed_string[i] = s.substr(start, end - start);
        i++;
        start = end + del.size();
        end = s.find(del, start);
    }
    parsed_string[i] = s.substr(start, end - start);
}