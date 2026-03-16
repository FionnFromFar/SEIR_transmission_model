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