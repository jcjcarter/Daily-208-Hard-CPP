#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <sstream>

using namespace std;

int main() {

    map<pair<string, char>, tuple<string, char, char>> rules_dict;
    map<int, char> tape;

    ifstream file("input.txt");
    file.ignore(100, '\n');
    file.ignore(100, '\n');

    string temp, state, accepting_state, tape_str;

    file >> state >> accepting_state >> tape_str;

    for (size_t i = 0; i < tape_str.size(); ++i) {
        tape[i] = tape_str[i];
    }

    string rule, s1, s2;
    char v1, v2, dir;

    while(getline(file, rule)){

        istringstream srule(rule);
        srule >> s1 >> v1 >> temp >> s2 >> v2 >> dir;

        rules_dict[{s1,v1}] = std::make_tuple(s2,v2, dir);
    }

    int head = 0;

    while (state != accepting_state){
        char dir, at_head = tape[head];
        std::tie(state, tape[head], dir) = rules_dict[{state, at_head ? at_head : '_'}];
        head += dir == '>' ? 1 : -1;
    }

    for (const auto &kv : tape){
        cout << kv.second;
    }

    cout << endl;

    string indicators(tape.size(), ' ');
    indicators[-tape.begin()->first + head] = '^';
    indicators[-tape.begin()->first] = '|';
    cout << indicators << endl;
    return 0;
}