#ifndef AGENT_HPP //header guard to prevent being called twice
#define AGENT_HPP

// defining the SEIR states
enum class State { Susceptible, Exposed, Infected, Recovered }; //using enum class to prevent leaking into global scope

class Agent {
private:
    // making it private so that only the agent can change its own values (this was in my feedback for test2)
    double x, y; //current positions in the box
    double vx, vy; //current velocities
    State status; //current health status (S, E, I or R)

public:
    //Constructor function to run and intialise a new agent with position, velocity and state
    Agent(double x0, double y0, double vx0, double vy0, State s0);

    //function to calculate distance between agents
    double distanceTo(const Agent& other) const;

    //getter functions to allow reading of the data without changing it
    double getX() const { return x; }
    double getY() const { return y; } //return both the x and y coords
    State getStatus() const { return status; } //returns health status

    //setter function whcih changes an agents health status if need be (ie becoming infected from susceptible when in contacted with an infected agent)
    void setStatus(State s) { status = s; }

    //movement logic used for updating position and also handling bouncing off the walls of the box instead of moving through it
    void move (double dt, double L);
    //dt is the time step
    //L is the length and width of the box

    //getting the state so that it can be changed if neccecary after infected/susceptible interatction
    State getState() const {return status; }
    void setState(State newState) { status = newState; }

};

#endif //eding the header guard