import pandas as pd 
import matplotlib.pyplot as plt

try:
    df = pd.read_csv("simulation_data.csv")
except FileNotFoundError:
    print("Error: simulation_data.csv not found")
    exit()

plt.figure(figsize=(10, 6))

#keeping colors the same again for consistancy
plt.plot(df["Step"], df["Susceptible"], label="Susceptible", color="green", linewidth=2)
plt.plot(df["Step"], df["Exposed"], label="Exposed", color="orange", linewidth=2)
plt.plot(df["Step"], df["Infected"], label="Infected", color="red", linewidth=2)
plt.plot(df["Step"], df["Recovered"], label="Recovered", color="skyblue", linewidth=2)

plt.title("SEIR Model: Continuous (Brownian Motion) Totals", fontsize=14)
plt.xlabel("Time Step", fontsize=12)
plt.ylabel("Number of Agents", fontsize=12)
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)

#saving the plot as an image
plt.savefig("continuous_seir_plot.png", dpi=300)
print("Pplot saved as 'continuous_seir_plot'")
plt.show()