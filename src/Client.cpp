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


void Client::initialize(unsigned int player, unsigned int board_size){
    this->player = player;//assign all attributes
    this->board_name = "player_" + to_string(player) + ".action_board.json";
    this->board_size = board_size;
    this->initialized = true;
    fstream action_board;
    action_board.open(board_name, ios::out);//create and open action board file
    if(!action_board){//file error handling
        cout << "Error : Action board not created properly" << endl;
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    fstream shot_file; // declare and open shot file and shot string
    string shot;
    shot = "[{\"x\":" + to_string(x) + ", \"y\":" + to_string(y) + "}]";
    shot_file.open("player_" + to_string(this->player) + ".shot.json", ios::out);
    if(!shot_file){//write contents of shot string
        shot_file << shot;
    } else {
        cout << "Error : shot file not opened properly" << endl;
    }
}


bool Client::result_available() {
    ifstream result_file;
    int file_size;
    result_file.open("player_" + to_string(this->player) + ".result.json", ios::in);
    if(!result_file){//result file does not exist
        cout << "Result file not found..." << endl;
        result_file.close();
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
    result_file.open("player_" + to_string(this->player) + ".result.json");
    std::getline(result_file, line);
    result_file.close();
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
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
    return "";
}