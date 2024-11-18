#include "disjointSet.h"
#include "sampler.h"
#include "queue.h"
#include "output.cpp"
#include <cmath>
#include <stdexcept>
#include <cstdlib>

uint8_t maze[MAX_ROWS][MAX_COLS];
uint32_t nMazeRows;
uint32_t nMazeCols;

uint32_t getVWallY(uint32_t wallnum, uint32_t c) {
    return floor(wallnum/(c-1));
}

uint32_t getVWallLeftSide(uint32_t wallnum, uint32_t c) {
    return (wallnum%(c-1));
}

uint32_t getVWallRightSide(uint32_t wallnum, uint32_t c) {
    return (wallnum%(c-1))+1;
}

uint32_t getHWallUpSide(uint32_t wallnum, uint32_t c) {
    return floor(wallnum/c);
}

uint32_t getHWallDownSide(uint32_t wallnum, uint32_t c) {
    return floor(wallnum/c)+1;
}

uint32_t getHWallX(uint32_t wallnum, uint32_t c) {
    return (wallnum%c);
}

uint32_t convertToCellNumber(uint32_t r1, uint32_t c1, uint32_t c) {
    return r1*c+c1;
}

void generateTreeMaze(uint32_t r,uint32_t c) {
    uint8_t wall1, wall2;
    uint32_t r1,c1,r2,c2,e,cell1,cell2,nVWalls,nHWalls;
    for (uint32_t row=0; row<=r-1; row++) {
        for (uint32_t col=0; col<=c-1; col++) {
            maze[row][col] = 15;
        }
    }
    DisjointSet ds(r*c);
    nVWalls = r*(c-1);
    nHWalls = (r-1)*c;
    Sampler walls(nVWalls+nHWalls);
    uint32_t walls_checked = 0;
    for (uint32_t i=0; i<r*c-1; i++) {
        // For every cell
        while (ds.find(i)!=ds.find(r*c-1)&&walls_checked<nVWalls+nHWalls) { 
            // while that cell cannot reach the bottom right corner
            // and while there are still walls to remove
            e = walls.getSample(); // Select random wall
            if (e<nVWalls) { // Removing a vertical wall
                // Find the two cells on either side of the wall
                r1 = getVWallY(e,c);
                c1 = getVWallLeftSide(e,c);
                r2 = getVWallY(e,c); // Set r2,c2 to cell to the right of r1,c1
                c2 = getVWallRightSide(e,c);

                cell1 = convertToCellNumber(r1,c1,c); // Convert locations to single number
                cell2 = convertToCellNumber(r2,c2,c);

                wall1 = WALL_RIGHT;
                wall2 = WALL_LEFT;
            }
            else { // Removing a horizontal wall
                e = e-nVWalls; // Skip over the vertical walls
                r1 = getHWallUpSide(e,c);
                c1 = getHWallX(e,c);
                r2 = getHWallDownSide(e,c); // Set r2,c2 to cell below r1,c1
                c2 = getHWallX(e,c);

                cell1 = convertToCellNumber(r1,c1,c); // Convert locations to single number
                cell2 = convertToCellNumber(r2,c2,c);

                wall1 = WALL_DOWN;
                wall2 = WALL_UP;
            }
            if (ds.find(cell1)==ds.find(cell2)) { // those cells reach eachother already, don't remove this wall, mark as checked
                walls_checked++;
            }
            else { // those cells don't reach eachother, remove this wall, mark as checked
                ds.join(cell1,cell2); // removes the wall in the abstract space
                maze[r1][c1] -= (maze[r1][c1]&wall1); // removes the wall in the maze space
                maze[r2][c2] -= (maze[r2][c2]&wall2);
                walls_checked++;
            }
        } // Continue until all cells can reach the bottom right corner of the maze
    }
}

bool cellHasWall(uint32_t r, uint32_t c, uint8_t wall, uint8_t maze[MAX_ROWS][MAX_COLS]) {
    return (wall&maze[r][c])!=0;
}

void removeAdditionalWalls(int r, int c, int w) {
    uint8_t wall1, wall2;
    uint32_t nVWalls, nHWalls, e, r1, c1, r2, c2;
    bool haveWall;
    nVWalls = r*(c-1);
    nHWalls = (r-1)*c;
    Sampler walls(nVWalls+nHWalls);
    for (int i=0;i<=w-1;i++) {
        // for each additional wall to remove
        haveWall = false;
        while (!haveWall) {
            // get a cell with a wall
            e = walls.getSample();
            if (e<nVWalls) {
                r1 = getVWallY(e,c);
                c1 = getVWallLeftSide(e,c);
                r2 = getVWallY(e,c);
                c2 = getVWallRightSide(e,c);
                wall1 = WALL_RIGHT;
                wall2 = WALL_LEFT;
            }
            else {
                e = e-nVWalls;
                r1 = getHWallUpSide(e,c);
                c1 = getHWallX(e,c);
                r2 = getHWallDownSide(e,c);
                c2 = getHWallX(e,c);
                wall1 = WALL_DOWN;
                wall2 = WALL_UP;
            }
            if (cellHasWall(r1,c1,wall1,maze)) {
                haveWall = true;
            }
        }
        // remove the wall
        maze[r1][c1] -= maze[r1][c1]&wall1;
        maze[r2][c2] -= maze[r2][c2]&wall2;
    }
}

uint32_t convertToRow(uint32_t cellnum, uint32_t c) {
    return floor(cellnum/c);
}

uint32_t convertToCol(uint32_t cellnum, uint32_t c) {
    return cellnum%c;
}

void findPath(uint8_t _maze[MAX_ROWS][MAX_COLS], uint32_t r, uint32_t c) {
    uint32_t e, row, col, rowP, colP;
    Queue<uint32_t> q;
    int neighbors[4];
    int count[MAX_ROWS][MAX_COLS];
    
    for (uint32_t row=0; row<=r-1; row++) {
        for (uint32_t col=0; col<=c-1; col++) {
            count[row][col]=-1;
        }
    }
    e=r*c-1; // (r-1)*c+c-1, start at the end
    q.enqueue(e);
    count[r-1][c-1]=0; // mark 0 steps to get to the end (because we are at the end)

    while (!q.isEmpty()) {
        // for each neighbor of the cells in the queue
        e=q.dequeue();
        row=convertToRow(e,c);
        col=convertToCol(e,c);
        neighbors[0] = (row==0)?-1:convertToCellNumber(row-1,col,c);
        neighbors[1] = (col==c-1)?-1:convertToCellNumber(row,col+1,c);
        neighbors[2] = (row==r-1)?-1:convertToCellNumber(row+1,col,c);
        neighbors[3] = (col==0)?-1:convertToCellNumber(row,col-1,c);

        for (int neighbor=0;neighbor<4;neighbor++) {
            if (neighbors[neighbor]==-1) continue; // neighboring cell does not exist
            if (cellHasWall(row,col,1<<neighbor,maze)) continue; // wall between cells, check other neighbors
            rowP = convertToRow(neighbors[neighbor],c); // get neighboring cell
            colP = convertToCol(neighbors[neighbor],c);
            if (count[rowP][colP]==-1) { // found unsearched neighbor
                e=convertToCellNumber(rowP,colP,c); // put in queue to be searched
                q.enqueue(e);
                count[rowP][colP]=count[row][col]+1; // mark the amount of steps taken to get there
            }
        }
    }

    maze[0][0] = (maze[0][0]|VISITED);
    row = 0;
    col = 0;

    while (count[row][col]!=0) {
        // while not at the end (while count is not 0)
        neighbors[0] = (row==0)?-1:convertToCellNumber(row-1,col,c);
        neighbors[1] = (col==c-1)?-1:convertToCellNumber(row,col+1,c);
        neighbors[2] = (row==r-1)?-1:convertToCellNumber(row+1,col,c);
        neighbors[3] = (col==0)?-1:convertToCellNumber(row,col-1,c);
        for (int neighbor=0;neighbor<4;neighbor++) {
            if (neighbors[neighbor]==-1) continue; // neighbor does not exist at this cell
            if (cellHasWall(row,col,1<<neighbor,maze)) continue; // neighbor is not connected
            rowP = convertToRow(neighbors[neighbor],c); // get neighboring cell
            colP = convertToCol(neighbors[neighbor],c);
            if (count[rowP][colP]==count[row][col]-1) {
                row = rowP;
                col = colP;
                break;
            }
        }
        maze[row][col] = (maze[row][col]|VISITED);
    }
}

int main(int argc, char* argv[]) {
    if (argc!=4) {
        throw std::domain_error("Invalid Maze Dimensions");
    }

    int r = atoi(argv[1]); // rows
    int c = atoi(argv[2]); // columns
    int w = atoi(argv[3]); // extra walls to remove

    if (!(r<=MAX_ROWS)) {
        throw std::domain_error("too many rows in maze");
    }
    if (!(c<=MAX_COLS)) {
        throw std::domain_error("too many columns in maze");
    }
    if (!(w>=0)) {
        throw std::domain_error("extra removed walls cannot be negative");
    }

    nMazeRows = r;
    nMazeCols = c;

    generateTreeMaze(nMazeRows,nMazeCols);
    removeAdditionalWalls(nMazeRows,nMazeCols,w);
    findPath(maze,nMazeRows,nMazeCols);
    printMaze(maze,nMazeRows,nMazeCols);

    return 0;
}