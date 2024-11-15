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

void generateTreeMaze(uint32_t r,uint32_t c) {
    uint8_t wall1, wall2;
    uint32_t r1,c1,r2,c2,e,cell1,cell2,nVWalls,nHWalls;
    for (uint32_t row=0; row<=r-1; row++) {
        for (uint32_t col=0; col<=c-1; col++) {
            maze[row][col] |= 15;
        }
    }
    DisjointSet ds(r*c);
    nVWalls = r*(c-1);
    nHWalls = (r-1)*c;
    Sampler walls(nVWalls+nHWalls);
    for (uint32_t i=0;i<=r*c-1;i++) {
        do {
            e = walls.getSample(); // Select random wall
            if (e<nVWalls) { // Removing a vertical wall

                // Find the two cells on either side of the wall
                r1 = floor(e/(c-1));
                c1 = e%(c-1);
                r2 = r1; // Set r2,c2 to cell to the right of r1,c1
                c2 = c1+1;

                cell1 = r1*c+c1; // Convert locations to single number
                cell2 = r2*c+c2;

                wall1 = WALL_RIGHT;
                wall2 = WALL_LEFT;
            }
            else { // Removing a horizontal wall
                e = e-nVWalls; // Skip over the vertical walls
                r1 = floor(e/c);
                c1 = e%c;
                r2 = r1+1; // Set r2,c2 to cell below r1,c1
                c2 = c1;

                cell1 = r1*c+c1; // Convert locations to single number
                cell2 = r2*c+c2;

                wall1 = WALL_DOWN;
                wall2 = WALL_UP;
            }
        } while (ds.find(cell1)==ds.find(cell2)); // Continue until cells aren't already connected

        ds.join(cell1,cell2);

        maze[r1][c1] -= (maze[r1][c1]&wall1);
        maze[r2][c2] -= (maze[r2][c2]&wall2);
    }
}

void removeAdditionalWalls(int r, int c, int w) {
    uint8_t wall1, wall2;
    uint32_t nVWalls, nHWalls, e, r1, c1, r2, c2;
    bool haveWall;
    nVWalls = r*(c-1);
    nHWalls = (r-1)*c;
    Sampler walls(nVWalls+nHWalls);
    for (int i=0;i<=w-1;i++) {
        haveWall = false;
        while (!haveWall) {
            e = walls.getSample();
            if (e<nVWalls) {
                r1 = floor(e/(c-1));
                c1 = e%(c-1);
                r2 = r1;
                c2 = c1+1;
                wall1 = WALL_RIGHT;
                wall2 = WALL_LEFT;
            }
            else {
                e = e-nVWalls;
                r1 = floor(e/c);
                c1 = e%c;
                r2 = r1+1;
                c2 = c1;
                wall1 = WALL_DOWN;
                wall2 = WALL_UP;
            }
            if ((wall1&maze[r1][c1])!=0) {
                haveWall = true;
            }
        }
        
        maze[r1][c1] -= maze[r1][c1]&wall1;
        maze[r2][c2] -= maze[r2][c2]&wall2;
    }
}

void FindPath(uint32_t** _maze, uint32_t r, uint32_t c) {
    uint32_t e, row, col, rowP, colP;
    Queue<uint32_t> q;
    int neighbors[4];
    int count[MAX_ROWS][MAX_COLS];
    
    for (uint32_t row=0; row<=r-1; row++) {
        for (uint32_t col=0; col<=c-1; col++) {
            count[row][col]=-1;
        }
    }
    e=(r-1)*c+c-1;
    q.enqueue(e);
    count[r-1][c-1]=0;

    while (!q.isEmpty()) {
        e=q.dequeue();
        row=floor(e/c);
        col=e%c;
        neighbors[0] = row<1?-1:(row-1)*c+col;
        neighbors[1] = col>=c?-1:(row)*c+col+1;
        neighbors[2] = row>=r?-1:(row+1)*c+col;
        neighbors[3] = col<1?-1:(row)*c+col-1;

        for (int neighbor=0;neighbor<4;neighbor++) {
            if (neighbors[neighbor]<0) continue;
            rowP = floor(neighbors[neighbor]/c);
            colP = neighbors[neighbor]%c;
            if ((maze[row][col]&(1<<neighbor))==0&&count[rowP][colP]==-1) {
                e=rowP*c+colP;
                q.enqueue(e);
                count[rowP][colP]=count[row][col]+1;
            }
        }
    }

    maze[0][0] |= VISITED;
    row = 0;
    col = 0;

    while (count[row][col]!=0) {
        neighbors[0] = row<1?-1:(row-1)*c+col;
        neighbors[1] = col>=c?-1:(row)*c+col+1;
        neighbors[2] = row>=r?-1:(row+1)*c+col;
        neighbors[3] = col<1?-1:(row)*c+col-1;
        for (int neighbor=0;neighbor<4;neighbor++) {
            if (neighbors[neighbor]<0) continue;
            if ((maze[row][col]&(1<<neighbor))!=0) continue;
            rowP = floor(neighbors[neighbor]/c);
            colP = neighbors[neighbor]%c;
            if (count[rowP][colP]==count[row][col]-1) {
                row = rowP;
                col = colP;
                break;
            }
        }

        maze[row][col] |= VISITED;
    }
}

int main(int argc, char* argv[]) {
    if (argc!=4) {
        throw std::domain_error("Invalid Maze Dimensions");
    }

    int r = atoi(argv[1]);
    int c = atoi(argv[2]);
    int w = atoi(argv[3]); // extra walls to remove

    if (r>MAX_ROWS) {
        throw std::overflow_error("too many rows in maze");
    }
    if (c>MAX_COLS) {
        throw std::overflow_error("too many columns in maze");
    }
    if (w<0) {
        throw std::underflow_error("extra removed walls cannot be negative");
    }

    nMazeRows = r;
    nMazeCols = c;

    generateTreeMaze(nMazeRows,nMazeCols);
    //removeAdditionalWalls(nMazeRows,nMazeCols,w);
    printMaze(maze,nMazeRows,nMazeCols);

    return 0;
}