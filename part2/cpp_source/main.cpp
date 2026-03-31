#include <iostream>
#include <vector>
#include <random> //from week 20
#include "Agent.hpp" //calling in the agent header file

int main() {
    //setting up the simulation constants
    const int N = 100; //total number of people
    const double L = 100.0; //size of the area
    const double dt = 0.1; //time step

    //random number generation using the mersenne twister engine
    std:: random_device rd;
    std::mt19937 gen(rd()); //generating the randomn number based on hardware

    //defining uniform flaoting point distributions
    std::uniform_real_distribution<double> dist_pos(0.0, L); //position can be between 0 to L (size of the box)
    std::uniform_real_distribution<double> dist_vel(-5.0, 5.0); //for now velocity can be between plus and minus 5

    //storing informaiton about agents
    std::vector<Agent> agents;

    //initialisation loop
    for  (int i = 0; i < N; ++i) {
        //random initial positions and velocities for each of the people
        double x = dist_pos(gen);
        double y = dist_pos(gen);
        double vx = dist_vel(gen);
        double vy = dist_vel(gen);

        //making sure that initially, everyone is susceptible
        State s = State::Susceptible;
    
        //creating a new agent with position and velocity and add it to the simulation
        agents.push_back(Agent(x, y, vx, vy, s));
    }

    //intialising simulation parameters
    const int total_steps = 1000; //number of monte carlo steps for now is 1000        
    std::cout << "Starting simulation with " << total_steps << " steps..." << std::endl;

    //The main time loop
    for (int step = 0; step < total_steps; ++step) {
        //looping through every agent in the vector
        for (Agent &a : agents) {                 
            //using &a reference so to be able to move the agent in the list
            //calling the propagation step defined in the header file
            //which updates x and y and behaves well at the boundaries
            a.move(dt, L);
            
        }
    }

    std::cout << "Initialised " << agents.size() << " agents with dt = " << dt << std::endl;

    return 0;
}