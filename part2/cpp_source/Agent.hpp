//LATICE BRANCH
#ifndef AGENT_HPP //header guard to prevent being called twice
#define AGENT_HPP

#include <vector>
#include <random>

// defining the SEIR states as per assessment brief (0 is just an empty position)
enum class State { Susceptible = 1, Exposed = 2, Infected = 3, Recovered = 4 }; //using enum class to prevent leaking into global scope

class Agent {
private:
    // making it private so that only the agent can change its own values (this was in my feedback for test2)
    int r, c; //changed from doubles of x and y position to row and column for the lattice
    State status; //current health status (S, E, I or R)
    double timeInState; //tracks the time spent in any state (these two are the same as im gonna use them in the same way)

public:
    //Constructor function to run and intialise a new agent with row, column and state
    Agent(int r0, int c0, State s0);

    //move function checks adjascent positions are empty to determine which can be moved into
    void move(std::vector<std::vector<int>>& grid, int L, std::mt19937& gen);

    //new function to check for infected neighbors
    bool hasInfectedNeighbor(const std::vector<std::vector<int>>& grid, int L)

    //getter functions to allow reading of the data without changing it
    int getRow() const { return r; }
    int getCol() const { return c; } //return both the x and y coords
    State getStatus() const { return status; }//returns health status

    //setter function whcih changes an agents health status if need be (ie becoming infected from susceptible when in contacted with an infected agent)
    void setStatus(State s) { status = s; }

    //timer functions remain the same
    void updateTime(double dt) {timeInState += dt; }
    void resetTime() {timeInState = 0.0; }
    double getTime() const {return timeInState; }
};

#endif //eding the header guard