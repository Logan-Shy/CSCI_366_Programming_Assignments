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
      file->close();
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
   this->board_size = board_size;
   this->p1_setup_board.open(p1_setup_board);
   // while () 

   this->p2_setup_board.open(p2_setup_board);
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
   //Check if player number and shot are within bounds
   if (player > 2 || player < 1) {
      return OUT_OF_BOUNDS;
   } else if ((x > 9 || x < 0) || (y > 9 || y < 0)) {
      return OUT_OF_BOUNDS;
   }

   string line = "";
   char shot = 'x';

   switch(player)
   {
      case 1:  
         for(int i = 0; i < y; i++){
            getline(p1_setup_board, line);
         }
         shot = line[x];
      
      case 2:
         for(int i = 0; i < y; i++){
            getline(p2_setup_board, line);
         }
         shot = line[x];
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


   if (player == 1){
      ifstream file("src/shots/player_1.shot.json");
      if (file) {//file exists and is open
         filesize = get_file_length(&file);
         cout << "shot filesize from player 1:" << filesize << endl;
         if (filesize < 3) {
            file.close();
            return NO_SHOT_FILE;
         } else { //file is large enough to extract coordinates
            file.close();
            return SHOT_FILE_PROCESSED;
         }
      } else {
         try{
            throw "Error opening file";
         } catch(string e) {
            cout << e << endl;
         }
      }
   } else if (player == 2) {
      ifstream file("src/shots/player_2.shot.json");
      if (file) {//file exists and is open
         filesize = get_file_length(&file);
         cout << "shot filesize from player 2:" << filesize << endl;
         if (filesize < 3) {
            file.close();
            return NO_SHOT_FILE;
         } else { //file is large enough to extract coordinates
            file.close();
            // return SHOT_FILE_PROCESSED;
            return NO_SHOT_FILE;
         }
      } else {
         try{
            throw "Error opening file";
         } catch(string e) {
            cout << e << endl;
         }
      }
   }
}