import pandas as pd 
import matplotlib.pyplot as plt 
import os

#importing the data
continuous_model = "continuous/brownian_results.csv"
discrete_model = "discrete/lattice_results.csv"

#checking if files loaded properly
if not os.path.exists(continuous_model) or not os.path.exists(discrete_model):
    print("Error: couldn't find the csv file")
    exit()

#reading data using pandas
df_cont = pd.read_csv(continuous_model)
df_disc = pd.read_csv(discrete_model)

#function to create plots
def save_plot(df, title, filename):
    plt.figure(figsize=(10,6))

    plt.plot(df["Step"], df["Susceptible"], label="Susceptible", color="green", linewidth=2)
    plt.plot(df["Step"], df["Exposed"], label="Exposed", color="orange", linewidth=2)
    plt.plot(df["Step"], df["Infected"], label="Infected", color="red", linewidth=2)
    plt.plot(df["Step"], df["Recovered"], label="Recovered", color="skyblue", linewidth=2)

    plt.title(title, fontsize=16)
    plt.xlabel("Time Step", fontsize=12)
    plt.ylabel("Number of Agents", fontsize=12)
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.legend(loc="upper right")

    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.close()
    print(f"saved: {filename}")

#continous model plot
save_plot(df_cont, "SEIR Model: Continuous (Brownian Motion)", "continuous_model.png")

#discrete model plot
save_plot(df_disc, "SEIR Model: Discrete (Lattice Grid)", "discrete_model.png")
