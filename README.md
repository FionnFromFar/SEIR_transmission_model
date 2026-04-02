# SEIR Transmission Model
**Author:** Fionn Doheny | **Student ID:** 2568597 | **Version** v3.0

## Project Overview
This repository contains a comparative study of the SEIR (Susceptible, Exposed, Infected, Recovered) epidemic model. The project compares traditional mathematical models with spatial Agent-based models to analyse how movement patterns affect outbreak dynamics.

---

## Repository Structure
This project is structured into three distinct experimental environments:

* **part1/**: **Deterministic ODE's** 
* **part2/continuous/'**: **Brownian Motion Model**
* **part2/discrete/'**: **Lattice-Grid Model** 

---

## How the Simulation works

### ODE Model (part1/)
- Solves the SEIR differential equations using `odeint` function
- Produces smooth time evolution curves for S, E, I, and R populations

### Continuous Model (part2/continuous/)
Each timestep:
1. Agents move according to their assigned velocity (Brownian motion)
2. Distances between agents are calculated
3. If agents are within a transmission radius, infection may occur probabilistically
4. State transitions (E → I → R) occur stochastically

### Discrete Model (part2/discrete/)
Each Monte Carlo step:
1. Agents attempt to move to a random neighbouring lattice site
2. Movement only occurs if the target site is empty
3. Susceptible agents check neighbouring cells for infected agents
4. State transitions occur probabilistically
---

## Execution Instructions

### Prerequisites
* **C++:** 'g++' compiler (C++17 recommended).
* **Python 3:** 'pandas', 'matplotlib', 'numpy'.

## Running the simulations
Each spatial model contains its own 'Makefile' for ease of use.

1. **Navigate to a model directory:**
```bash
    cd part2/continuous  # or cd part2/discrete
```
2.  **Build the C++ simulation:**
```bash
    make # compiles all files
    make clean # removes the executable and object files (use for re-running simulation after changing paramters)
```
3.  **Run the engine:**
```bash
    ./simulation
```
4.  **Visualize Data & Animation:**
```bash
    python3 plot_continuous.py      #Generates SEIR graph for continuous model
    python3 model_plot_discrete.py  #Generates SEIR graph for discrete model
    python3 animation_continuous.py #Launches real-time animation for continuous model
    python3 lattice_animation.py    #Launches real-time animation for discrete model
```

---

## Customisation:
Simulation parameters such as:

- Number of agents (N)
- Simulation duration
- Transmission probability
- Movement parameters

can be modified directly in the source files before compilation.

## Key research features
* **Dynamic visualisations:** Real-time python bindings track the spatial evolution of "Infected" population.
* **Modular Design:** Seperate, organised source code and directories for high reporducability. 
* **Comparative Analysis:** I structured the project with two spatial simulations to make comparisons between "mean free path" dynamics (continuous) and "Local Clustering" (Discrete).

---

## Version History
* **v1.0-ode**: Python only ODE simulation (purely mathematical)
* **v1.0 - v1.3**: Continuous Brownian motion logic simulation developments
* **v2.0 - v2.2**: Lattice model implementation and bug fixes, finalising with addition of animation
* **v3.0**: **Final Release.** Consolidated directory structure and integrated animations for both models. This is the version within the main branch