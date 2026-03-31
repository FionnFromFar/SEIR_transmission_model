//LATTICE BRANCH
#include <iostream>
#include <vector>
#include <random> //from week 20
#include <fstream> //for output csv file
#include "Agent.hpp" //calling in the agent header file

int main() {
    //setting up the simulation constants
    const int N = 100; //total number of people/agents
    const int initial_infected = 15; //15 people initially infected
    const int L = 50; //adjusting the size of the grid to make it more dense
    const int total_steps = 1000; //total steps
    const double dt = 1.0; //time step altered to 1 for lattice (discrete)

    //Infection parameters 
    const double beta = 1.0; //infection probability (1 now because whenever there is an interaction, it leads to transmission)
    const double sigma_time = 5.0; //time for infection to kick in
    const double gamma_time = 15.0; //time that infection lasts

    //random number generation using the mersenne twister engine
    std:: random_device rd;
    std::mt19937 gen(rd()); //generating the randomn number based on hardware

    //making the distribution for integers
    std::uniform_int_distribution<int> dist_grid(0, L - 1);
    std::uniform_real_distribution<double> roll(0.0, 1.0);

    //making the empty 2D grid
    std::vector<std::vector<int>> grid(L, std::vector<int>(L, 0));

    //storing informaiton about agents
    std::vector<Agent> agents;

    //initialisation of placement loop
    std::cout << "Initialising agents..." << std::endl;
    for  (int i = 0; i < N; ++i) {
        int r, c;
        do {
            r = dist_grid(gen);
            c = dist_grid(gen);
        } while (grid[r][c] != 0); //keep trying to pick position if position is already taken

        //assigning infected state the first 'initial_infected' agents
        State s = (i < initial_infected) ? State::Infected : State::Susceptible;
    
        grid[r][c] = (int)s;
        agents.push_back(Agent(r, c, s));
    }

    //intialising data logging into csv file
    std::ofstream outFile("Simulation_data_d.csv"); //d for discrete version
    if (!outFile.is_open()) {
        std::cerr << "Error: cant open csv for writing" << std::endl; //trying to fix ts bug
        return 1;
    }
    outFile << "Step,Susceptible,Exposed,Infected,Recovered\n"; //header for csv file

    std::cout << "Starting lattice simulation..." << std::endl;

    //The main time loop
    for (int step = 0; step < total_steps; ++step) {
        //looping through every agent in the vector
        for (Agent &a : agents) {                 
            //movement and infection
            a.move(grid, L, gen);
            a.updateTime(dt); //adds dt to internal clock of each agent

            //check for infection if susceptible
            if (a.getStatus() == State::Susceptible) { //if one is susceptible
                if (a.hasInfectedNeighbor(grid, L)) { //and their neighbor is infected
                    if (roll(gen) < beta) { //and the 'coin flip' allows for it
                        a.setStatus(State::Exposed);
                        a.resetTime();
                        grid[a.getRow()][a.getCol()] = (int)State::Exposed;
                    }
                }
            }
        }
        //adding the transmission from susceptible to infected to recovered
        for (Agent &a : agents) {
            State current = a.getStatus();

            //infection process
            if (current == State::Exposed && a.getTime() > sigma_time) {
                a.setStatus(State::Infected);
                a.resetTime();
                grid[a.getRow()][a.getCol()] = (int)State::Infected;
            }
            //recovery process
            else if (current == State::Infected && a.getTime() > gamma_time) {
                a.setStatus(State::Infected);
                a.resetTime();
                grid[a.getRow()][a.getCol()] = (int)State::Recovered;
            }
        }
        
        //data tracking and logging
        int S = 0, E = 0, I = 0, R = 0;
        for (const Agent &a : agents) {
            State currentStatus = a.getStatus();

            if (currentStatus == State::Susceptible) S++;
            else if (currentStatus == State::Exposed) E++;
            else if (currentStatus == State::Infected) I++;
            else if (currentStatus == State::Recovered) R++;
        }
        outFile << step << "," << S << "," << E << "," << I << "," << R << std::endl;
        if (step % 100 == 0) std::cout << "Step " << step << " Processed..." << std::endl;
    }
    
    outFile.close();    
    std::cout << "Simulation complete, data saved to simulation_data_d.csv" << std::endl;

    return 0;
}