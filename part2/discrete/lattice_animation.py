import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
from matplotlib.colors import ListedColormap
import matplotlib.patches as mpatches


L = 50 #grid has to be same size as lattice in main loop
try:
    data = pd.read_csv("grid_animation_data.csv", header=None)
except FileNotFoundError:
    print("Error: could not find the animation file")
    exit()


colors = ["white", "green", "orange", "red", "skyblue"] #mathcing colors to the plots (white is empty)
cmap = ListedColormap(colors)
labels = ["Empty", "Susceptible", "Exposed", "Infected", "Recovered"]

fig, ax = plt.subplots(figsize=(12,8))

#labled color patches as the legend
legend_patches = [mpatches.Patch(color=colors[i], label=labels[i]) for i in range(len(colors))]
ax.legend(handles=legend_patches, loc="upper right", bbox_to_anchor=(1.25, 1))

def update(frame):
    ax.clear()
    grid_frame = np.array(data.iloc[frame]).reshape((L, L)) #shaping the row into a littice sized square
    img = ax.imshow(grid_frame, cmap=cmap, vmin=0, vmax=4) #displaying the lattice
    ax.legend(handles=legend_patches, loc="upper left", bbox_to_anchor=(1.02, 1), title="States")
    ax.set_title(f"Lattice SEIR simulation - Step {frame}") #re adding the legend as ax.clear removes it
    ax.axis("off")
    return[img]

#creating the animation
ani = animation.FuncAnimation(fig, update, frames=len(data), interval=50, blit=True)

#saving animation as a mp4 file so that i can take screenshots of individual frames for the report
print("Saving animiation... be patient pls ;)")

try:
    ani.save("Lattice_infection.mp4", writer="ffmpeg", fps=20)
    print("Animation Saved as 'Lattice_infection.mp4")
except:
    print("FFmpeg not found. Install it if you havent already. Displaying plot instead...")
    plt.show()