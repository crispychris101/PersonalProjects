#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    // Open the input file
    ifstream file(fileName);

    // Check if the file is valid and not empty
    if (!file || file.eof()) {
        file.close();
        return nullptr;
    }

    // READ IN DATA
    int t_maxRow, t_maxCol, t_player_r, t_player_c;

    if (!(file >> t_maxRow >> t_maxCol >> t_player_r >> t_player_c)) {
        file.close();
        return nullptr; 
    }

    // Check if rows/columns and player POSITIONS ARE INT
    if (file.fail() || file.bad()) {
        file.close();
        return nullptr; 
    }

    // Check for negative or MASSIVEvalues
    if (t_maxRow <= 0 || t_maxCol <= 0 || t_player_r < 0 || t_player_c < 0 ||
        (static_cast<unsigned long long>(t_maxRow) * t_maxCol >= static_cast<unsigned long long>(INT32_MAX))) {
        file.close();
        return nullptr;
    }

    // Validate row and column within INT32_MAX bounds
    if ((static_cast<unsigned long long>(t_maxRow) > (static_cast<unsigned long long>(INT32_MAX) / t_maxCol)) ||
        (static_cast<unsigned long long>(t_maxCol) > (static_cast<unsigned long long>(INT32_MAX) / t_maxRow))) { // HAD TO DOUBLE CHEK THIS LOLL
        file.close();
        return nullptr; 
    }

    // Check if the player's starting position is within the bounds
    if (t_player_r >= t_maxRow || t_player_c >= t_maxCol || t_player_r == t_maxRow || t_player_c == t_maxCol) {
        file.close();
        return nullptr; 
    }

    // Create the map
    char** map = createMap(t_maxRow, t_maxCol);

    // Populate the map from the file
    int totalSpaces = 0; // Counter for spaces in the map
    for (int r = 0; r < t_maxRow; r++) {
        for (int c = 0; c < t_maxCol; c++) {
            char tile;
            if (!(file >> tile)) {
                file.close();
                deleteMap(map, t_maxRow);
                return nullptr; // If file reading fails
            }

            // If more characters present after maxRow * maxCol iterations
            if (r == t_maxRow - 1 && c == t_maxCol - 1 && file >> tile) {
                file.close();
                deleteMap(map, t_maxRow);
                return nullptr; 
            }

            if (tile == TILE_DOOR || tile == TILE_EXIT) {
                totalSpaces++;
            }

            if (tile != TILE_OPEN && tile != TILE_TREASURE && tile != TILE_AMULET &&
                tile != TILE_DOOR && tile != TILE_EXIT && tile != TILE_MONSTER &&
                tile != TILE_PILLAR && tile != TILE_PLAYER) { // FROM PIAZIAAAA
                file.close();
                deleteMap(map, t_maxRow);
                return nullptr; // Invalid tiles
            }

            map[r][c] = tile;
        }
    }

    //  missing door/exit IF THERE SEEMS TO BE ONE 
    if (totalSpaces == 0) {
        file.close();
        deleteMap(map, t_maxRow);
        return nullptr; 
    }
    map[t_player_r][t_player_c] = TILE_PLAYER;
    // Check if the file is fully read
    char extraChar;
    if (file >> extraChar) {
        file.close();
        deleteMap(map, t_maxRow);
        return nullptr; 
    }
    // CLOSE THE BAD BOY 
    file.close();
    maxRow = t_maxRow;  // RESET AND RETURNN 
    maxCol = t_maxCol;
    player.row = t_player_r;
    player.col = t_player_c;
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    // Update nextRow and nextCol based on input
    if (input == MOVE_UP) { // I LIKE TO MOVE IT MOVE IT 
        nextRow -= 1; // JUST MOVIN IN DIRECTIONS BASED N WHAT IT IS
    } else if (input == MOVE_DOWN) {
        nextRow += 1;
    } else if (input == MOVE_LEFT) {
        nextCol -= 1;
    } else if (input == MOVE_RIGHT) {
        nextCol += 1;
    }
    // No reset for the perpendicular direction
}


/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    // Check for invalid input values
    int max_row_col=999999; // TEST CASEE FROM PIAZA AND TEH SHEET TBH
    if (maxRow <= 0 || maxCol <= 0 || maxRow>max_row_col|| maxCol>max_row_col) {
        return nullptr; // Invalid input values, return nullptr
    }
    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; i++) { // LOOPING THROUGH 
        map[i] = new char[maxCol];
    }
    // Initialize each array element to TILE_OPEN
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            map[i][j] = TILE_OPEN;
        }
    }
    // Return a pointer to the new map in memory
    return map;
}


/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr || maxRow <= 0) {
        // Nothing to delete for invalid input, but ensure map and maxRow are updated
        map = nullptr;
        maxRow = 0;
        return;
    } //DEALOCATE
    for (int i = 0; i < maxRow; i++) {
        delete[] map[i];
        map[i] = nullptr; // Set each row pointer to null
    }
    delete[] map;
    // Update map, maxRow, and maxCol
    map = nullptr;
    maxRow = 0;
}


/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */

// edit and restructure the function 
char **resizeMap(char **map, int &maxRow, int &maxCol) {
  char **tempMap = createMap(maxRow * 2, maxCol * 2);
  // if the map is null then return nullptr
  if (tempMap == nullptr || maxRow <= 0 || maxCol <= 0) {
    return nullptr;
  }

  int playerRow;
  int playerCol;
  for (int i = 0; i < maxRow; i++) {
    for (int j = 0; j < maxCol; j++) {
      tempMap[i][j] = map[i][j];
      if (tempMap[i][j] == TILE_PLAYER) {
        playerCol = j;
        playerRow = i;
        tempMap[i][j] = TILE_OPEN;
      }
    }
  }


  int newMaxRow = maxRow * 2;
  int newMaxCol = maxCol * 2;
  deleteMap(map, maxRow);
  maxRow = newMaxRow;
  maxCol = newMaxCol;


   // bottom right
  for (int i = newMaxRow / 2; i < newMaxRow; i++) {
    for (int j = newMaxCol / 2; j < newMaxCol; j++) { // we iterate thru botom firstt teh our top 
      int baseRow = i - newMaxRow / 2;
      int baseCol = j - newMaxCol / 2;
      tempMap[i][j] = tempMap[baseRow][baseCol];
    }
  }

  // bottom left
  for (int i = newMaxRow / 2; i < newMaxRow; i++) {
    for (int j = 0; j < newMaxCol / 2; j++) {
      int baseRow = i - newMaxRow / 2;
      int baseCol = j;
      tempMap[i][j] = tempMap[baseRow][baseCol];
    }
  }
// right tops 
  for (int i = 0; i < newMaxRow / 2; i++) {
    for (int j = newMaxCol / 2; j < newMaxCol; j++) {
      int baseRow = i;
      int baseCol = j - newMaxCol / 2;
      tempMap[i][j] = tempMap[baseRow][baseCol];
    }
  }

  tempMap[playerRow][playerCol] = TILE_PLAYER;
  

  return tempMap;
}




    // Copy the content from the original map into subarrays B, C, and 

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    // Check if the next position is within the bounds of the map
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol || map[nextRow][nextCol] == TILE_PILLAR) {
        return STATUS_STAY; // Move outside bounds or onto a pillar, adventurer stays
    }

    // Check the tile at the next position
    char nextTile = map[nextRow][nextCol];

    switch (nextTile) {
        case TILE_PILLAR:
            return STATUS_STAY;
        
    
        case TILE_OPEN:
            // Update the map to move the adventurer
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;

            // Update the player's position
            player.row = nextRow;
            player.col = nextCol;

            return STATUS_MOVE;

        case TILE_TREASURE:
            // Increment the adventurer's treasure count
            player.treasure++;

            // Update the map to move the adventurer and update the tile
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;

            // Update the player's position
            player.row = nextRow;
            player.col = nextCol;

            return STATUS_TREASURE;

        case TILE_AMULET:
            map[nextRow][nextCol] = TILE_PLAYER;  // Update the map with the player's new position
            map[player.row][player.col] = TILE_OPEN;  // Update the old position to TILE_OPEN
            player.row = nextRow;
            player.col = nextCol;
            return STATUS_AMULET; // Handle amulet tile

        case TILE_DOOR:
            map[nextRow][nextCol] = TILE_PLAYER;  // Update the map with the player's new position
            map[player.row][player.col] = TILE_OPEN;  // Update the old position to TILE_OPEN
            player.row = nextRow;
            player.col = nextCol;
            return STATUS_LEAVE; // Handle door to the next level

        case TILE_EXIT:
            if (player.treasure > 0) {
                map[nextRow][nextCol] = TILE_PLAYER;  // Update the map with the player's new position
                map[player.row][player.col] = TILE_OPEN;  // Update the old position to TILE_OPEN
                player.row = nextRow;
                player.col = nextCol;
                return STATUS_ESCAPE; // Handle exit tile when the adventurer has treasure
            } else {
                return STATUS_STAY; // Treat the exit as a pillar when no treasure
            }

        case TILE_MONSTER:
            return STATUS_STAY; // Handle impassable tiles (monsters)
            
        default:
            return STATUS_STAY; // Default to stay if the tile is unrecognized
    }
}



/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
// edit this function 
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool playerKilled = false;

// smol Function to move monsters in a particular direction
    auto moveMonsters = [&](int rowChange, int colChange) {
        for (int i = player.row + rowChange, j = player.col + colChange; 
             i >= 0 && i < maxRow && j >= 0 && j < maxCol; 
             i += rowChange, j += colChange) {
            char tile = map[i][j];
            if (tile == TILE_PILLAR) {
                break;
            }
            if (tile == TILE_MONSTER) {
                map[i][j] = TILE_OPEN;
                map[i - rowChange][j - colChange] = TILE_MONSTER;
            }
        }
    };

    // Check for monsters in four directions from the player
    moveMonsters(-1, 0);  // Up
    moveMonsters(1, 0);   // Down
    moveMonsters(0, -1);  // Left
    moveMonsters(0, 1);   // Right

    // Check if the player is on a monster tile( they dead)
    if (map[player.row][player.col] == TILE_MONSTER) {
        playerKilled = true;
    }

    return playerKilled;
}
