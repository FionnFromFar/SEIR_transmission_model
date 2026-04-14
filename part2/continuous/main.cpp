//CONTINUOUS BRANCH
#include <iostream>
#include <vector>
#include <random> //from week 20
#include "Agent.hpp" //calling in the agent header file
#include <fstream> //for outputting to csv

int main() {
    //setting up the simulation constants
    const int N = 100; //total number of people/agents
    const double L = 100.0; //size of the area
    const double dt = 0.1; //time step
    const double rho = 0.01; //1% chance of becoming susceptible again

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

        //making sure that initially, everyone is susceptible (correction!)
        State s = State::Susceptible;

        //mannually adding one initial infected agent
        if (i == 0) {
            s =State::Infected;
        }
    
        //creating a new agent with position and velocity and add it to the simulation
        agents.push_back(Agent(x, y, vx, vy, s));
    }

    //intialising simulation parameters
    const int total_steps = 1000; //number of monte carlo steps for now is 1000        
    std::cout << "Starting simulation with " << total_steps << " steps..." << std::endl;

    std::ofstream outFile("simulation_data.csv"); //for SEIR graph
    std::ofstream posFile("positions.csv");
    outFile << "Step,Susceptible,Exposed,Infected,Recovered\n"; //writing the header for the SEIR csv file
    posFile << "Step,ID,x,y,status\n"; //header for position csv file

    //The main time loop
    for (int step = 0; step < total_steps; ++step) {
        //looping through every agent in the vector
        for (Agent &a : agents) {                 
            //using &a reference so to be able to move the agent in the list
            //calling the propagation step defined in the header file
            //which updates x and y and behaves well at the boundaries
            a.move(dt, L);
            a.updateTime(dt); //adds dt to internal clock of each agent

            //adding the transmission from exposed to infected
            if (a.getStatus() == State::Exposed && a.getTime() > 5.0) {
                a.setStatus(State::Infected); //change to infected after 5 ticks
                a.resetTime(); //reset time in state (because state has changed)
                std::cout << "An agent has become Infectious!!!" << std::endl;
            }

            //adding the transmission from infected to recovered
            if (a.getStatus() == State::Infected && a.getTime() > 15.0) {
                a.setStatus(State::Recovered); //change to recovered after 15 ticks
                a.resetTime();
                std::cout << "An agent has recovered!!!" << std::endl;
            }

            //adding the re-infection process
            if (a.getStatus() == State::Recovered) {
                if (a.checkReinfection(rho, gen)) {
                    std::cout << "An agent has been re-infected" << std::endl; //confirmation of re-infection (keeping it consistent)
                }
            }
        }
        //interaction step
        double infection_radius = 2.0; //distance required for disease to spead
        double transmission_prob = 0.5; //50% chance of an interaction leading to transmission

        for (size_t i = 0; i < agents.size(); ++i) {
            for (size_t j = i + 1; j < agents.size(); ++j) {

                //checking if transmission is possible (interaction between infected and susceptible)
                if ((agents[i].getStatus() == State::Infected && agents[j].getStatus() == State::Susceptible) ||
                    (agents[j].getStatus() == State::Infected && agents[i].getStatus() == State::Susceptible)) {

                        //checking if distance is within range
                        if (agents[i].distanceTo(agents[j]) < infection_radius) {

                            //generate a random probability and comparing to 0.5 (flipping a coin basically)
                            std::uniform_real_distribution<double> roll(0.0, 1.0);
                            if (roll(gen) < transmission_prob) {
                                //small line to check if transmission mechanism is working
                                std::cout << "Agent " << j << " was exposed by Agent " << i << "!" << std::endl;
                                //change state from susceptible to exposed
                                if (agents[i].getStatus() == State::Susceptible)
                                    agents[i].setStatus(State::Exposed);
                                else
                                    agents[j].setStatus(State::Exposed);
                            }
                        }
                    }
                }
            }
      

    int S = 0, E = 0, I = 0, R = 0;
    for (const Agent &a : agents) {
        if (a.getStatus() == State::Susceptible) S++;               
        else if (a.getStatus() == State::Exposed) E++;
        else if (a.getStatus() == State::Infected) I++;
        else if (a.getStatus() == State::Recovered) R++;
    }
    for (size_t i = 0; i < agents.size(); ++i) {
        posFile << step << "," << i << ","
        << agents[i].getX() << ","
        << agents[i].getY() << ","
        << static_cast<int>(agents[i].getStatus()) << "\n";
    }
    //outputting these values into the csv file
    outFile << step << "," << S << "," << E << "," << I << "," << R << "\n";     
    }

    outFile.close(); //closing SEIR file after ending loop
    posFile.close(); //closing the position file after ending loop

    std::cout << "Initialised " << agents.size() << " agents with dt = " << dt << std::endl;

    return 0;
}