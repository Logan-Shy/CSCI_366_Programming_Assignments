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

#ifndef BATTLESHIP_COMMON_H
#define BATTLESHIP_COMMON_H

#define MAX_PLAYERS 2
#define HIT 1
#define MISS -1
#define OUT_OF_BOUNDS 0

#define BOARD_SIZE 10

#endif //BATTLESHIP_COMMON_H

// Shot file example:
// [{"x" : 4, "y" : 7}]

//Action board example:
/**
 * 
{"0":[{"x0":"C"},{"x1":"C"},{"x2":"C"},{"x3":"C"},{"x4":"C"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"1":[{"x0":"B"},{"x1":"B"},{"x2":"B"},{"x3":"B"},{"x4":"_"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"2":[{"x0":"R"},{"x1":"R"},{"x2":"R"},{"x3":"_"},{"x4":"_"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"3":[{"x0":"S"},{"x1":"S"},{"x2":"S"},{"x3":"_"},{"x4":"_"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"4":[{"x0":"D"},{"x1":"_"},{"x2":"_"},{"x3":"_"},{"x4":"_"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"5":[{"x0":"D"},{"x1":"_"},{"x2":"_"},{"x3":"_"},{"x4":"_"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"6":[{"x0":"C"},{"x1":"C"},{"x2":"C"},{"x3":"C"},{"x4":"C"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"7":[{"x0":"C"},{"x1":"C"},{"x2":"C"},{"x3":"C"},{"x4":"C"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"8":[{"x0":"C"},{"x1":"C"},{"x2":"C"},{"x3":"C"},{"x4":"C"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}],
"9":[{"x0":"C"},{"x1":"C"},{"x2":"C"},{"x3":"C"},{"x4":"C"},{"x5":"_"},{"x6":"_"},{"x7":"_"},{"x8":"_"},{"x9":"_"}]}
*/