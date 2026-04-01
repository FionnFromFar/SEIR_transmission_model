# SEIR Transmission Model
**Author:** [Fionn Doheny] | **Student ID:** 2568597
**Version** v3.0

## Project Overview
This repository contains a comparative study of the SEOR (Susceptible, Exposed, Infected, Recovered) epidemic model. The project compares traditional mathematical models with spatial Agent-based models to analyse how movement patterns affect outbreak dynamics.

---

## Repository Structure
This project is structured into three distinct experimental environments:

* **'part1/'**: **Deterministic ODE's** Python implementation using 'odeint' to establish mathematical baseline for the infection curve.
* **part2/continuous/'**: **Brownian Motion Model** C++ engine simulation agents assigned random position and velocity within a 2D space. Infection is determined by proximety between agents (collision based). Includes Python binding for animation.
* **part2/discrete/'**: **Lattice-Grid Model** C++ engine simulating agents on a $L \times L$ grid. Movement of agents is determined by checking for empty adjascent spaces on the grid. Infection spreads via neighborhood sensing. Includes Python a heatmap animation.

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
    make
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
```

---

## Key research features
* **Dynamic visualisations:** Real-time python bindings track the spatial evolution of "Infected" population.
* **Modular Design:** Seperate, organised source code and directories for high reporducability. 
* **Comparative Analysis:** I structured the project with two spatial simulations to make comparisons between "mean free path" dynamics (continuous) and "Local Clustering" (Discrete).

---

## Version History
* **v1.0-ode**: Python only ODE simulation (purely mathematical)
* **v1.0 - v1.3**: Continuous Brownian motion logic simulation developments
* **v2.0 - v2.2**: Lattice model implementation and bug fixes, finalising with addition of animation
* **v3.0**: **Final Release.** Consolidated directory structure and integrated animations for both models.