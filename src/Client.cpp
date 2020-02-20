//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"

Client::~Client() {
}

/**
 * Helper function to clean files 
 *@param file - input file to be opened and cleaned
 */
void cleanFile(string fileName){
    ofstream file;
    file.open(fileName, ios::out | ios::trunc);
    if(file){
        file << fflush;
    } else {
        cout << "Error : couldn't clean file: " << fileName << endl;
    }
    file.close();
}


void Client::initialize(unsigned int player, unsigned int board_size){
    this->player = player;//assign all attributes
    this->board_name = "src/actionBoards/player_" + to_string(player) + ".action_board.json";
    this->board_size = board_size;
    this->initialized = true;
    ofstream action_board;
    string default_board = "{";
    for(int i = 0; i < board_size; i++){
        if(i != 0){
            default_board = default_board + ",\n";
        }
        default_board = default_board + 
        "\"" + to_string(i) + "\":[{\"x0\":\"_\"},{\"x1\":\"_\"},{\"x2\":\"_\"},{\"x3\":\"_\"},"
                                "{\"x4\":\"_\"},{\"x5\":\"_\"},{\"x6\":\"_\"},{\"x7\":\"_\"},"
                                "{\"x8\":\"_\"},{\"x9\":\"_\"}]";
    }
    default_board = default_board + "}";
    action_board.open(board_name, ios::out | ios::trunc);//create and open action board file
    if(!action_board){//file error handling
        cout << "Error : Action board not created properly" << endl;
        this->initialized = false;
    } else {
        action_board << default_board;
        action_board.close();
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    fstream shot_file; // declare and open shot file and shot string
    string shot;
    shot = "[{\"x\":" + to_string(x) + ", \"y\":" + to_string(y) + "}]";
    shot_file.open("src/shots/player_" + to_string(this->player) + ".shot.json", ios::out);
    if(shot_file){//write contents of shot string
        shot_file << shot;
    } else {
        cout << "Error : shot file not opened properly" << endl;
    }
}


bool Client::result_available() {
    fstream result_file;
    // result_file.open("src/results/player_"+to_string(this->player) + ".result.json", ios::in);
    // string line; 
    // getline(result_file, line);
    // cout << line << endl;
    // return false;

    int file_size;
    result_file.open("src/results/player_" + to_string(this->player) + ".result.json", ios::in);
    if(!result_file){//result file does not exist
        cout << "Result file not found..." << endl;
        // result_file.close();
        return false;
    } else {//file exists, check size
        cout << "Result file found! Checking size..." << endl;
        result_file.seekg(0, ios::end);
        file_size = result_file.tellg();
        result_file.close();
        if(file_size <= 4){
            cout << "Result File too small" << endl;
            return false;
        } else {
            cout <<"Result available" << endl;
            return true;
        }
    }
}


int Client::get_result() {
    ifstream result_file;
    char result;
    string line = "";
    result_file.open("src/results/player_" + to_string(this->player) + ".result.json");
    
    if(result_file){
        std::getline(result_file, line);
        result_file.close();
        cleanFile("src/results/player_" + to_string(this->player) + ".result.json");
        for(int i = 0; i < line.size(); i++){//extract result
            if (line[i] == ':'){
                if(line[i + 1] == '1'){
                    return HIT;
                } else if(line[i + 1] == '-' && line[i + 2] == '1') {
                    return MISS;
                } else if(line[i + 1] == '0'){
                    return OUT_OF_BOUNDS;
                } else if(line[i + 1] == ' ' || line[i + 1] == '\t'){
                    cout << "Error : whitespace detected as shot result" << endl;
                }
                cout << "Error reading shot result" << endl;
            }
        }
        cout << "Error : file not in JSON format (i.e. a colon wasn't found)" << endl;
        return OUT_OF_BOUNDS;
    } else {
        cout << "Error : Couldn't open result file, even though it exists" << endl;
        return OUT_OF_BOUNDS;
    }
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    if(result == 0){// out of bounds
        cout << "Skipping action board update, as shot is OOB" << endl;
    } else {//valid shot, update json file
        fstream action_board;
        string board_string = "";
        string line = "";
        int position = 0;
        action_board.open(board_name, ios::in);
        if(action_board){
            for(int i = 0; i < board_size; i++){
                getline(action_board, line);
                board_string = board_string + line + '\n';
            }
            cout << "action Board loaded from board on file:" << endl << board_string << endl;
            action_board.close();
        } else {
            cout << "Error : couldn't open action_board" << endl;
        }
    }
}


string Client::render_action_board(){
    return "this is the rendered action board \n";
}