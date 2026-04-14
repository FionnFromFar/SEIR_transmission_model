//CONTINUOUS BRANCH
#include "Agent.hpp" //taking the definition of Agent class from the header file
#include <cmath> //maths module neeeded for distance caluculations

//intialising the agents properties directly with an initialisation list
Agent::Agent(double x0, double y0, double vx0, double vy0, State s0)
    : x(x0), y(y0), vx(vx0), vy(vy0), status(s0), timeInState(0.0) {}

//The 'move' function the main propagation step of the simulation
void Agent::move(double dt, double L) {
    //update position using current veolicty and timestep dt (x = x0+vt)
    x += vx * dt;
    y += vy * dt;

    //making sure that boundaries cause reflection if/when agents hit a wall
    //this was an error i didnt account for in test 2 hehe
    //horizontal boundary
    if (x <= 0 || x >= L) {
        vx = -vx; //flips direction of velocity at horizontal boundaries

        //making sure the agent cant get stuck outside the box (horizontal)
        if (x < 0) x = 0;
        if (x > L) x = L;
    }

    //vertical boundary
    if (y <= 0 || y >= L) {
        vy = -vy; //flips direction at vertical boundaries

        //making sure the agent cant get stuck outside the box (vertical)
        if (y < 0) y = 0;
        if (y > L) y = L; //little bug fix making sure the agent cant get stuck outside the box
    }
}

//The'distance between' function
double Agent::distanceTo(const Agent& other) const {
    double dx = x - other.x; //dx is difference in x cords
    double dy = y - other.y; //dy is difference in y cords
    return std::sqrt(dx*dx + dy*dy);
}

//re-infection function: gives recovered agents a small change of becoming susceptible again
bool Agent::checkReinfection(double rho, std::mt19937& gen) {
    std::uniform_real_distribution<double> roll(0.0, 1.0); //random number between 0 and 1
    if (status == State::Recovered && roll(gen) < rho) { //if agent is recovered AND the roll value is less than rho
        status = State::Susceptible; //agent becomes susceptible again
        resetTime(); //resets the agents internal clock
        return true; //tells main.cpp that re-infection has occured
    }
    return false; //no reinfection occurred
}