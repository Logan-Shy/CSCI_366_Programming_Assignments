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
      try{
         throw "File not opened properly";
      } catch(string e){
         cout << e << endl;
      }
   } else {
      this->board_size = board_size;
   }
   if(p1_setup_board.length() <= 1 || p2_setup_board.length() <= 1){
      try{
         throw "File not opened properly";
      } catch(string e){
         cout << e << endl;
      }
   } else{
      this->p1_setup_board.open(p1_setup_board);
      this->p2_setup_board.open(p2_setup_board);
   }
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
   
   if (player > 2 || player < 1) {//Check if player number and shot are within bounds
      throw std::runtime_error(string("Failed: player OOB"));
   } else if ((x > 9 || x < 0) || (y > 9 || y < 0)) {
      return OUT_OF_BOUNDS;
   }

   string line = "";
   char shot = 'x';

   if(player == 1){//extract shot destination from opposing players board
      if(!p2_setup_board){//file not opened correctly
         try{
            // throw 20;
         } catch(int e){
            cout << e << endl;
         }
      } else {
         for(int i = 0; i <= y; i++){
            getline(p2_setup_board, line);
         }
         cout << "character on player board at shot position: " << line[x] << endl;
         shot = line[x];
      }
   } else if(player == 2){
      if(!p1_setup_board){//file2 not opened properly
         try{
            // throw 20;
         } catch(int e){
            cout << e << endl;
         }
      } else {
         for(int i = 0; i <= y; i++){
            getline(p1_setup_board, line);
         }
         cout << "character on player board at shot position: " << line[x] << endl;
         shot = line[x];
      }
   }

   if(shot == 'x'){
      return OUT_OF_BOUNDS;
   }

   if (shot == '_') {
      return MISS;
   } else {
      return HIT;
   }
   
}


int Server::process_shot(unsigned int player) {
   
   int filesize = 0;
   ifstream shotFile;
   ofstream resultFile;
   string boardName = "player_" + to_string(player) + ".shot.json";
   int xcoord, ycoord = -1; //initialize coordinates to something not expected

   if(player > 2 || player < 1){
      throw std::runtime_error(string("Failed: player OOB"));
   }

   shotFile.open(boardName, ios::in);

   if (shotFile) {//file exists and is open
      filesize = get_file_length(&shotFile);
      printf("shot filesize from player %d: %d\n", player, filesize);
      shotFile.seekg(0, ios::beg);
      shotFile.clear();
      if (filesize > 3) {//file large enough to be read from
         cereal::JSONInputArchive archive(shotFile);
         archive(xcoord);
         archive(ycoord);
         shotFile.close();

         if(remove(boardName.c_str()) != 0){
            cout << "Error : couldn't remove shot file" << endl;
         } else {
            cout << "removed player " << player << " shot file" << endl;
         }

         cout << "\nxcoord: " + to_string(xcoord) + "\nycoord: " + to_string(ycoord) << endl << endl;

         //pass info to evaluate_shot
         int result = evaluate_shot(player, xcoord, ycoord);
         string resultJSON = "{\n"
                            "    \"result\": "+to_string(result)+"\n"
                                                               "}";

         //write to proper result file
         cout << "Writing result = " << result << " to proper result file..." << endl;
         resultFile.open("test/player_" + to_string(player) + ".result.json", ios::out);
         if(resultFile){
            resultFile << resultJSON;
            cout << "Successfully wrote to File" << endl;
            resultFile.close();
         } else {
            throw std::runtime_error(string("Failed: couldn't write to result file"));
         }
         return SHOT_FILE_PROCESSED;
      } else { //file not large enough to extract coordinates
         shotFile.close();
         return NO_SHOT_FILE;
      }
   } else {//file error handling
      cout << "Error opening shot file" << endl;
   }
   return NO_SHOT_FILE;
}