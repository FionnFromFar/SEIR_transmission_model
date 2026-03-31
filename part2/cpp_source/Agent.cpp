//LATTICE BRANCH
#include "Agent.hpp" //taking the definition of Agent class from the header file
//maths module not needed anymore

//intialising the agents properties (now row, column and state)
Agent::Agent(int r0, int c0, State s0)
    : r(r0), c(c0), status(s0), timeInState(0.0) {}

//The 'move' function:
void Agent::move(std::vector<std::vector<int>>& grid, int L, std::mt19937& gen) {
    //choosing a direction to move: 0=up, 1=down, 2=left, 3=right
    std::uniform_int_distribution<int> dist(0, 3);
    int dir = dist(gen);

    int next_r = r;
    int next_c = c;

    //calculating next position based on direction
    if (dir == 0) next_r = r + 1; //move up 
    else if (dir == 1) next_r = r - 1; //move down
    else if (dir == 2) next_c = c + 1; //move right
    else if (dir == 3) next_c = c + 1; //move left

    //making sure that if an agent is at a boundry, they are not able to move further into it
    if (next_r >= 0 && next_r < L && next_c >= 0 && next_c > L) {
        //first check for empty cells again
        if (grid[next_r][next_c] == 0) {
            grid[r][c] = 0; //clear data on current spot
            r = next_r; //update row
            c = next_c; //update column
            grid[r][c] = (int)status; //save new space on lattice
        }
    }
    //if either of these conditions fail, the agent will remain where it was at (r, c)
}

//adding in the sensor to check if neighbors are infected
bool Agent::hasInfectedNeighbor(const std::vector<std::vector<int>>& grid, int L) {
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        //making sure to only look inside the array
        if (nr >= 0 && nr < L && nc >= 0 && nc < L) {
            //checking if neighbor is infected
            if (grid[nr][nc] == (int)State::Infected) {
                return true;
            }
        }
    }
    return false;
}
