import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.lines import Line2D


#loading the continuous data
try:
    df = pd.read_csv('positions.csv')
except FileNotFoundError:
    print("Error: brownian_results.csv not found in this directory.")
    exit()

#setting up the figure
fig, ax = plt.subplots(figsize=(10, 8))

#defining the colors (again same as part1-ode)
color_map = {0: 'green', 1: 'orange', 2: 'red', 3: 'skyblue'}
labels = ['Susceptible', 'Exposed', 'Infected', 'Recovered']

def update(frame_step):
    ax.clear()
    
    #filtering out the data for the current time step
    current_data = df[df['Step'] == frame_step]
    
    #plotting each state
    for state, color in color_map.items():
        subset = current_data[current_data['status'] == state]
        #using scatter for continuous coordinates (X, Y) 
        ax.scatter(subset['x'], subset['y'], c=color, s=40, edgecolors='black', linewidth=0.5, alpha=0.8)

    #setting up the figure
    ax.set_title(f"Continuous Brownian SEIR Simulation - Step {frame_step}", fontsize=14)
    ax.set_xlim(0, 100)  #matching to the size of the box in the continuous simulation
    ax.set_ylim(0, 100)
    ax.set_aspect('equal')
    
    #puttin in the legend
    legend_elements = [Line2D([0], [0], marker='o', color='w', label=l,
                              markerfacecolor=c, markersize=10) 
                       for l, c in zip(labels, color_map.values())]
    ax.legend(handles=legend_elements, loc='center left', bbox_to_anchor=(1.05, 0.5), title="Agent States")
    
    plt.tight_layout()
    plt.subplots_adjust(right=0.8)
    ax.axis('on') # Keep axis on for continuous space to show scale

    return []

#creating the animation (skip every 5 steps because this has far more steps than the discrete simulation)
unique_steps = df['Step'].unique()[::5]
ani = animation.FuncAnimation(fig, update, frames=unique_steps, interval=50, repeat=False)

print("Displaying continuous animation window...")
plt.show()

#saving as mp4
ani.save('continuous_infection.mp4', writer='ffmpeg', fps=20)