#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();


		void mousePressed(int x, int y, int button);
  
        // Global variables
        int width;
        int height;
        static const int SIZE = 3;
        int board[SIZE][SIZE]; // Game board 3x3 array
        int cellWidth, cellHeight; // Cell size computed from window size
        int player = 1;
        ofTrueTypeFont font;
        bool won;
        
        // Functions
        void clearBoard();
        void drawBoard();
        void drawCell(int row, int col);
        void drawGameOver();
        void drawGameWinner(int player);
		void playerMove();
        int oppositePlayer(int p);
        bool boardFilled();
        bool rowFilled(int row);
        int rowFilledByPlayer(int row);
        int colFilledByPlayer(int col);
        int diag1FilledByPlayer();
        int diag2FilledByPlayer();
        void checkWinner();
};
