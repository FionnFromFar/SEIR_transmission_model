#Importing the nececary libraries
import numpy as np
from scipy.integrate import odeint

def seir(y, t, beta, sigma, gamma): #defining the SEIR equations in a function
    s, e, i, r = y #get the SEIR data from this list y

    dsdt = -beta * i * t # equation for susceptible [7]
    dedt = (beta * i * s) - (sigma * e) # equation for exposed [8]
    didt = (sigma * e) - (gamma * i) # equation for infected [9]
    drdt = gamma * i #equation for recovered

    return [dsdt, dedt, didt, drdt] 

#setting up model parameters (from assesment brief)
beta = 1.0 #infection rate
sigma = 1.0 #incubation rate
gamma = 0.1 #recovery rate

#setting up basic initial conditions for first run (as percentage of population)
s0 = 0.99 #initial susceptible
e0 = 0.01 #initial exposed
i0 = 0.0 #initial infected
r0 = 0.0 # intial recovered

#setting up initial condisitons in the list y for the function
y0 = [s0, e0, i0, r0]

#creating a list to represent 100 days as per instructions
t = np.linspace(0, 100, 100)