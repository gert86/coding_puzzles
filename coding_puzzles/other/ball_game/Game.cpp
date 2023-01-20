#include "Game.h"
#include "Board.h"
#include "Piece.h"

void Game::init()
{
  _board = new Board();
}

int Game::mainLoop()
{
  showPrompt();
  std::string input;
  while (true) {
    getline(cin, input);

    if (input.empty()) {
      // "scrolling"
      cout << endl;
      continue;
    }
    else if (input == "h") {
      // HELP
      showPrompt();
    }
    else if (input == "d") {
      // DRAW BOARD
      _board->draw();
    }
    else if (input == "r") {
      // RESET BOARD
      delete _board;
      _board = new Board();
      cout << "Success: Reset board" << endl;
    }
    else if (input == "s") {
      // SHOW ALL PIECES
      _board->showAllPieces();
      cout << endl;
    }
    else if (input.size() > 2 && input.substr(0, 2) == "s ") {
      // SHOW DETAILS OF 1 PIECE
      char pieceId = ' ';
      bool success = parsePieceId(input.substr(2), pieceId);
      if (!success) {
        cerr << "Error: Usage is: " << endl << "s <piece_id>" << endl;
        continue;
      }
      _board->showPieceDetails(pieceId);
      cout << endl;
    }
    else if (input.size() > 2 && input.substr(0, 2) == "p ") {
      // PLACE 1 PIECE
      char pieceId = ' ';
      int configId = -1;
      Coord coordToPlace(-1, -1);
      bool success = parseIdsAndCoordinate(input.substr(2), pieceId, configId, coordToPlace);
      if (!success) {
        cerr << "Error: Usage is: " << endl << "p <piece_id> <config_id> <x> <y>" << endl;
        continue;
      }

      // check if piece still unplaced
      Piece* piece = nullptr;
      for (const auto& p : _board->getUnplacedPieces()) {
        if (p->id() == pieceId) {
          piece = p;
          break;
        }
      }
      if (!piece) {
        cerr << "Error: There is no unplaced piece with id " << pieceId << " among the "
             << _board->getUnplacedPieces().size() << " unplaced pieces" << endl;
        continue;
      }

      // check if piece has allows this configuration
      if (configId >= (int)piece->getNumGeometries()) {
        cerr << "Error: The piece with id " << pieceId << " has only " << piece->getNumGeometries()
             << " configurations, but index " << configId << " was requested!" << endl;
        continue;
      }

      // try to place it there
      auto result = _board->tryPlacePiece(piece, configId, coordToPlace);
      if (result) {
        cout << "Success -> placed " << pieceId << "@" << configId << " at pos" << coordToPlace.x << "/" << coordToPlace.y << endl;
      }
      else {
        cerr << "Error -> unable to place " << pieceId << "@" << configId << " at pos" << coordToPlace.x << "/" << coordToPlace.y << endl;
      }
    }
    else if (input.size() > 2 && input.substr(0, 2) == "x ") {
      // REMOVE 1 PIECE
      char pieceId = ' ';
      bool success = parsePieceId(input.substr(2), pieceId);
      if (!success) {
        cerr << "Error: Usage is: " << endl << "s <piece_id>" << endl;
        continue;
      }

      // check if piece is placed
      Piece* piece = nullptr;
      for (const auto& [p, coord] : _board->getPlacedPieces()) {
        if (p->id() == pieceId) {
          piece = p;
          break;
        }
      }
      if (!piece) {
        cerr << "Error: There is no placed piece with id " << pieceId << " among the "
             << _board->getPlacedPieces().size() << " placed pieces" << endl;          continue;
      }


      if(_board->removePlacedPiece(piece)) {
        cout << "Success -> removed piece " << piece->id() << " from board" << std::endl;
      }
      else {
        cout << "Error -> could not remove piece " << piece->id() << " from board " << std::endl;
      }
    }
    else if (input == "f") {
      // FIND A SOLUTION FOR ALL UNPLACED PIECES
      if (_board->solveGame()) {
        cout << "Success -> solved the board" << std::endl;
      }
      else {
        cerr << "Error -> could not solve the board" << std::endl;
      }
      cout << endl;
    }
    else if (input == "q") {
      cout << "Quit!" << endl;
      return 0;
    }
    else {
      cerr << "Error: unknown command: " << input << endl;
    }
    cout << endl;
  }

  return -1;
}

void Game::showPrompt() const
{
  cout << "Enter a command: " << endl;
  cout << "h ... show this help text" << endl;
  cout << "d ... draw board" << endl;
  cout << "r ... reset board to empty" << endl;
  cout << "s ... show all pieces (in base configuration)" << endl;
  cout << "s <piece_id> ... show details for piece" << endl;
  cout << "p <piece_id> <config_id> <x> <y> ... place a piece" << endl;
  cout << "x <piece_id> ... remove a piece" << endl;
  cout << "f ... find a placement for all unplaced pieces" << endl;
  cout << "q...quit" << endl;
}

bool Game::parsePieceId(const string &inputStr, char &pieceId)
{
  istringstream ss(inputStr);
  bool success = false;
  if(ss >> pieceId) {
    success = true;
    //cout << "Parsed: pieceId=" << pieceId << endl;    
  }
  return (success==true && pieceId!=' ');
}

bool Game::parseIdsAndCoordinate(const string &inputStr, char &pieceId, int &configId, Coord &coord)
{
  istringstream ss(inputStr);
  bool success = false;
  if(ss >> pieceId >> configId >> coord.x >> coord.y) {
    success = true;
    //cout << "Parsed: pieceId=" << pieceId
    //     << "; configId=" << configId
    //     << "; xBoard=" << coord.x
    //     << "; yBoard=" << coord.y << endl;
  }
  return (success==true && pieceId!=' ' && configId!=-1 && coord.x!=-1 && coord.y!=-1);
}
