#Importing the nececary libraries
import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt

def seir(y, t, beta, sigma, gamma): #defining the SEIR equations in a function
    s, e, i, r = y #get the SEIR data from this list y

    dsdt = -beta * i * s # equation for susceptible [7]
    dedt = (beta * i * s) - (sigma * e) # equation for exposed [8]
    didt = (sigma * e) - (gamma * i) # equation for infected [9]
    drdt = gamma * i #equation for recovered

    return [dsdt, dedt, didt, drdt] 

#setting up model parameters (from assesment brief)
beta = 1.75 #infection rate
sigma = 1.0 #incubation rate
gamma = 0.75 #recovery rate

#setting up basic initial conditions for first run (as percentage of population)
s0 = 0.99 #initial susceptible
e0 = 0.01 #initial exposed
i0 = 0.0 #initial infected
r0 = 0.0 # intial recovered
R0 = (beta/gamma) * s0 #Initial growth rate

#setting up initial condisitons in the list y for the function
y0 = [s0, e0, i0, r0]

#creating a list to represent 100 days as per instructions to be fed into odeint
t = np.linspace(0, 100, 100)

#using odeint to solve the odes over the time array above
ret = odeint(seir, y0, t, args=(beta, sigma, gamma))

#extracting the results to ret (and transposing)
s, e, i, r = ret.T



#Making the plot
plt.figure(figsize=(10,8))

plt.plot(t, s, color="green", alpha=0.7, linewidth=2, label="Susceptible")
plt.plot(t, e, color="orange", alpha=0.7, linewidth=2, label="Exposed")
plt.plot(t, i, color="red", alpha=0.7, linewidth=2, label="Infected")
plt.plot(t, r, color="skyblue", alpha=0.7, linewidth=2, label="Recovered")

plt.xlabel("Time (days)")
plt.ylabel("Fraction of population")
plt.title(f"SEIR model with beta=1.75, sigma=1.0, gamma=0.75 (R0={R0:.2f})")
plt.legend()
plt.savefig("graphs/seir_R0_3_5.png", dpi=300) #having to save the graph as an image because im running in a linux terminal
print(f"The initial growth rate of this simulation was: {R0:.2f}")
print("Graph saved as 'seir_R0_3_5.png' in graphs folder")
