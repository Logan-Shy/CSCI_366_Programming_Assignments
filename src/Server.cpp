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
   const auto begin = file.tellg();
   file.seekg(0, ios::end);
   const auto end = file.tellg();
   const auto fsize = (end - begin);
}

class Server {
   public:
      int board_size;

   private:
      ifstream p1_setup_board;
      ifstream p2_setup_board;
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
   this.board_size = board_size;
   this.p1_setup_board.open(p1_setup_board);
   while () 

   this.p2_setup_board.open(p2_setup_board);
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
   //Check if player number and shot are within bounds
   if (player > 2 || player < 1) {
      return OUT_OF_BOUNDS;
   } else if ((x > 9 || x < 0) || (y > 9 || y < 0)) {
      return OUT_OF_BOUNDS;
   }
}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}