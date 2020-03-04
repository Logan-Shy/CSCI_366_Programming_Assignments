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
#include "Server.hpp"
/**
 * helper function to determine if a given character
 * is a whitespace.
 * @param c - character to be checked
 * @return boolean if character is a whitespace
 */
bool isSpace(unsigned char c){
   return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f');
}


/**
 * Calculate the length of a file (helper function)
 * (Code snippets found at https://www.bfilipek.com/2019/01/filesize.html)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
   streamsize fileSize = 0;
   if(file->is_open()){
      file->seekg(0, ios::end);
      fileSize = file->tellg();
      file->seekg(0, ios::beg);
   } else {
      try{
         throw "File not opened properly";
      } catch(string e){
         cout << e << endl;
      }
   }
   return fileSize;
}



void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
   //Assign board sizes and open setup boards
   if(board_size < BOARD_SIZE){
      throw 20;
   } else {
      this->board_size = board_size;
   }
   if(p1_setup_board.length() <= 1 || p2_setup_board.length() <= 1){
      throw 20;
   } else{
      this->p1_setup_board.open(p1_setup_board);
      this->p2_setup_board.open(p2_setup_board);
   }
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
   
   if (player > 2 || player < 1) {//Check if player number and shot are within bounds
      return OUT_OF_BOUNDS;
   } else if ((x > 9 || x < 0) || (y > 9 || y < 0)) {
      return OUT_OF_BOUNDS;
   }

   string line = "";
   char shot = 'x';

   if(player == 1){//extract shot destination from opposing players board
      if(!p2_setup_board){//file not opened correctly
         try{
            throw 20;
         } catch(int e){
            cout << e << endl;
         }
      } else {
         for(int i = 0; i < y; i++){
            getline(p2_setup_board, line);
         }
         shot = line[x];
      }
   } else if(player == 2){
      if(!p1_setup_board){//file2 not opened properly
         try{
            throw 20;
         } catch(int e){
            cout << e << endl;
         }
      } else {
         for(int i = 0; i < y; i++){
            getline(p1_setup_board, line);
         }
         shot = line[x];
      }
   }

   try {
      if (shot == 'x') throw "Something went wrong";
   } catch (string e) {
      cout << e;
   }

   if (shot == '_') {
      return MISS;
   } else {
      return HIT;
   }
   
}


int Server::process_shot(unsigned int player) {
   int filesize = 0;
   ifstream file;
   ofstream resultFile;
   int xcoord, ycoord = -1; //initialize coordinates to something not expected


   if(player == 1){
      file.open("src/shots/player_1.shot.json", ios::in);
   } else if (player == 2) {
      file.open("src/shots/player_2.shot.json", ios::in);
   }

   if (file) {//file exists and is open
      filesize = get_file_length(&file);
      printf("shot filesize from player %d: %d\n", player, filesize);
      file.seekg(0, ios::beg);
      file.clear();
      if (filesize < 3) {
         file.close();
         return NO_SHOT_FILE;
      } else { //file is large enough to extract coordinates
         char *buffer = new char [filesize + 1];
         file.read(buffer, filesize);
         file.close();

         //open in truncating mode and erase proper shot file
         file.open("src/shots/player_" + to_string(player) + ".shot.json", ios::out | ios::trunc);
         if(!file.is_open() || file.fail()){
               file.close();
               cout << "\nError : Failed to erase file content!" << endl;
            }
         file.close();

         buffer[filesize] = '\0'; //add null string to terminate
         string line = buffer;//remove whitespaces from shot string
         line.erase(remove_if(line.begin(), line.end(), isSpace), line.end());
         cout << "trimmed shot string: " << line << endl;

         delete[] buffer;
         
         for(int i = 0; i < line.size(); i++){//extract coordinates
            if(line[i] == 'x'){
               cout << "x coord: " << line[i + 3] << endl;
               xcoord = (int)line[i + 3] - 48;
            }
            if(line[i] == 'y'){
               cout << "y coord: " << line[i + 3] << endl;
               ycoord = (int)line[i + 3] - 48;
            }
         }

         //pass info to evaluate_shot
         int result = evaluate_shot(player, xcoord, ycoord);
         string resultJSON = "[{\"result\":" + to_string(result) + "}]";
         cout << "result: " << result << endl;

         //write to proper result file
         resultFile.open("src/results/player_" + to_string(player) + ".result.json", ios::out);
         if(resultFile.is_open()){
            resultFile << resultJSON << "\n";
            resultFile.close();
         } else {
            printf("\nError : couldn't open result file for %d", player);
         }
         return SHOT_FILE_PROCESSED;
      }
   } else {//file error handling
      cout << "Error opening file" << endl;
   }
   return NO_SHOT_FILE;
}