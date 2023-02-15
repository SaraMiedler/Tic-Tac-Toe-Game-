#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
    width = ofGetWidth();
    height = ofGetHeight();
    font.load("Arial", 40);
    won = false;
    
    
    cellWidth = width / SIZE;
    cellHeight = height / SIZE;
    clearBoard();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawBoard();

    checkWinner();

    if (boardFilled()) drawGameOver();
}

void ofApp::checkWinner() {
    // check rows for winner
    if (rowFilledByPlayer(0) == 1 || rowFilledByPlayer(1) == 1 || rowFilledByPlayer(2) == 1) drawGameWinner(1);
    else  if (rowFilledByPlayer(0) == 2 || rowFilledByPlayer(1) == 2 || rowFilledByPlayer(2) == 2) drawGameWinner(2);
    // check columns for winner
    else if (colFilledByPlayer(0) == 1 || colFilledByPlayer(1) == 1 || colFilledByPlayer(2) == 1) drawGameWinner(1);
    else if (colFilledByPlayer(0) == 2 || colFilledByPlayer(1) == 2 || colFilledByPlayer(2) == 2) drawGameWinner(2);
    // check diagonals for winner
    else if (diag1FilledByPlayer() == 1 || diag2FilledByPlayer() == 1) drawGameWinner(1);
    else if (diag1FilledByPlayer() == 2 || diag2FilledByPlayer() == 2) drawGameWinner(2);
}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (boardFilled())
        clearBoard();
    else if (won == true) {
        won = false;
        clearBoard();
    }
    else
        playerMove();
}


void ofApp::clearBoard() {
    for (int row=0; row<SIZE; row++)
        for (int col=0; col<SIZE; col++)
            board[row][col] = 0;
}

void ofApp::drawGameOver() {
    ofSetColor(0, 102, 153);
    //textAlign(CENTER, CENTER);
    std::string s = "Game Over!";
    ofRectangle r = font.getStringBoundingBox(s, 0, 0);
    font.drawString(s, width/2 - r.width/2,  height/4);
}

 void ofApp::drawGameWinner(int player) {
     won = true;
    ofSetColor(0, 102, 153);
    //textAlign(CENTER, CENTER);
    if (player == 1) {
        std::string s = "Winner Player 1";
        ofRectangle r = font.getStringBoundingBox(s, 0, 0);
        font.drawString(s, width/2 - r.width/2, height / 2);
    }

    if (player == 2) {
        std::string s = "Winner Player 2";
        ofRectangle r = font.getStringBoundingBox(s, 0, 0);
        font.drawString(s, width / 2 - r.width / 2, height / 2);
    }
 }





void ofApp::drawBoard() {
    for (int row=0; row<SIZE; row++)
        for (int col=0; col<SIZE; col++)
            drawCell(row, col);
}

void ofApp::drawCell(int row, int col) {
    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
    
    switch (board[row][col]) {
        case 1:
            ofDrawEllipse(col * cellWidth + cellWidth/2, row * cellHeight+ cellHeight/2, cellWidth, cellHeight);
            break;
        case 2:
            ofDrawLine(col * cellWidth, row * cellHeight, (col+1) * cellWidth, (row+1) * cellHeight);
            ofDrawLine((col+1) * cellWidth, row * cellHeight, col * cellWidth, (row+1) * cellHeight);
            break;
            
    }
}


void ofApp::playerMove() {
    int row = mouseY / cellHeight;
    int col = mouseX / cellWidth;
    
    if (board[row][col] == 0) {
        board[row][col] = player;
        player = oppositePlayer(player);
    }
}

int ofApp::oppositePlayer(int p) {
    return 3-p;
}

bool ofApp::boardFilled() {
    for (int row = 0; row < SIZE; row++) {
        if (!rowFilled(row))
            return false;
    }
    return true;
}

bool ofApp::rowFilled(int row) {
    for (int col = 0; col < SIZE; col++) {
        if (board[row][col] == 0) return false;
    }
    return true;
}
int ofApp::rowFilledByPlayer(int row) {
    bool p1win = false;
    bool p2win = false;
    int firstCell = board[row][0];

    for(int col=1;col<SIZE;col++) {
        if (board[row][col] == firstCell && firstCell != 0) {
            if (firstCell == 1)
                p1win = true;
            else if (firstCell == 2)
                p2win = true;
        }
        else {
            p1win = false;
            p2win = false;
            break;
        }
    }
    if (p1win) return 1;
    if (p2win) return 2;
}

int ofApp::colFilledByPlayer(int col) {
    bool p1win = false;
    bool p2win = false;
    int firstCell = board[0][col];

    for (int row = 1; row < SIZE; row++) {
        if (board[row][col] == firstCell && firstCell != 0) {
            if (firstCell == 1)
                p1win = true;
            else if (firstCell == 2)
                p2win = true;
        }
        else {
            p1win = false;
            p2win = false;
            break;
        }
    }
    if (p1win) return 1;
    if (p2win) return 2;
}

int ofApp::diag1FilledByPlayer() {
    bool p1win = false;
    bool p2win = false;
    int firstCell = board[0][0];

    for (int i = 1, j = 1; i < SIZE; i++, j++) {
        if (board[i][j] == firstCell && firstCell != 0) {
            if (firstCell == 1)
                p1win = true;
            else if (firstCell == 2)
                p2win = true;
        }
        else {
            p1win = false;
            p2win = false;
            break;
        }
    }
    if (p1win) return 1;
    if (p2win) return 2;
}

int ofApp::diag2FilledByPlayer() {
    bool p1win = false;
    bool p2win = false;
    int firstCell = board[0][SIZE-1];

    for (int i = 1, j = 2; i < SIZE; i++, j++) {
        if (board[i][SIZE - j] == firstCell && firstCell != 0) {
            if (firstCell == 1)
                p1win = true;
            else if (firstCell == 2)
                p2win = true;
        }
        else {
            p1win = false;
            p2win = false;
            break;
        }
    }
    if (p1win) return 1;
    if (p2win) return 2;
}
