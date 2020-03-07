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
    shot = "{\n"
                          "    \"x\": " + to_string(x) + ",\n"
                          "    \"y\": " + to_string(y) + "\n"
                          "}";

    shot_file.open("src/player_" + to_string(this->player) + ".shot.json", ios::out);
    if(shot_file){//write contents of shot string
        shot_file << shot;
        shot_file.close();
    } else {
        cout << "Error : shot file not opened properly" << endl;
    }
}


bool Client::result_available() {
    fstream result_file;
    int file_size;
    result_file.open("src/player_" + to_string(this->player) + ".result.json", ios::in);
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
    int result;
    string boardName = "src/player_" + to_string(this->player) + ".result.json";
    result_file.open(boardName, ios::in);
    if(result_file){
        cereal::JSONInputArchive archive(result_file);
        archive(result);
        cout <<"\n\nresult: " + to_string(result) << endl << endl;
    } else {
        cout << "Error : couldn't open result file" << endl;
        return -1;
    }
    result_file.close();

    if(result == 999){
        try{
            throw "bad stuf";
        } catch(exception e){
            cout << "exception occurred" << endl;
        }
        return -1;
    }
    
    if(this->player == 1){
        if(remove("src/player_1.result.json") != 0){
            cout << "Couldn't remove result file" << endl;
        } else{
            cout << "removed result file" << endl;
        }
    } else if(this->player == 2){
        if(remove("src/player_2.result.json") != 0){
            cout << "Couldn't remove result file" << endl;
        } else{
            cout << "removed result file" << endl;
        }
    }
    
    return result;
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
                if(i == y){//update shot as we read in file
                    for(int j = 0; j < line.size(); j++){
                        if (line[j] == 'x'){
                            cout << "found shot in action board" << endl;
                            cout << "current position: " << line[j + 1] << endl;
                            if ( (((int)line[j + 1]) - 48) == x){
                                line[j + 5] = (char)0;
                                line.insert(j + 5, to_string(result));
                                cout << "just wrote result to action board" << endl;
                            }
                        }
                    }
                }
                board_string = board_string + line + '\n';
            }
            cout << "action Board loaded from board on file:" << endl << board_string << endl;
            action_board.close();
            cout << "writing result to action board:" << endl;
            action_board.open(board_name, ios::out | ios::trunc);
            if(action_board){
                action_board << board_string;
                action_board.close();
                cout << "result written to action board" << endl;
            } else {
                cout << "Error : couldn't write result to action board" << endl;
                action_board.close();
            }
        } else {
            cout << "Error : couldn't open action_board" << endl;
        }
    }
}


string Client::render_action_board(){
    string returnStr = "";
    string line = "";
    ifstream actionBoard;
    actionBoard.open(this->board_name, ios::in);
    if (actionBoard){
        while(std::getline(actionBoard, line)){
            for(int i = 0; i < line.size(); i++){
                if(line[i] == ':'){
                    if(line[i + 2] == '_'){
                        returnStr = returnStr + "_ ";
                    } else if(line[i + 2] == '1'){
                        returnStr = returnStr + "1 ";
                    } else if(line[i + 2] == '-' || line[i + 3] == '1'){
                        returnStr = returnStr + "-1 ";
                    }
                }
            }
            returnStr = returnStr + "\n";
        }
        actionBoard.close();
        returnStr = returnStr + "\n";
    } else {
        cout << "Error : Couldn't open action board to render" << endl;
    }
    
    return returnStr;
}