def convection(nt, nx, tmax, xmax, c):
   """
   more refined 1D convection program
   """
   #define the size of the time step and the size of the 
   #distance between each grid point
   dt = tmax/(nt-1)
   dx = xmax/(nx-1)

   # Initialise solution arrays with zeros
   import numpy as np
   u = np.zeros((nx,nt))
   x = np.zeros(nx)

   # define Boundary conditions
   u[0,:] = u[nx-1,:] = 1

   # Initial conditions. set u array equal to 2 over the 
   #interval as per the initial conditions
   for i in range(1,nx-1):
      if(i > (nx-1)/4 and i < (nx-1)/2):
         u[i,0] = 2
      else:
         u[i,0] = 1

   #apply the numerical scheme foward difference in time backwards in space 
   for n in range(0,nt-1):
      for i in range(1,nx-1):
         u[i,n+1] = u[i,n]-c*(dt/dx)*(u[i,n]-u[i-1,n])

   #populate x array
   for i in range(0,nx):
      x[i] = i*dx

   return u, x


#plot function
def plot_convection(u,x,nt,title):
   """
   Plots the 1D velocity field
   """

   import matplotlib.pyplot as plt
   plt.figure()
   for i in range(0,nt,10):
      plt.plot(x,u[:,i],'r')
      plt.xlabel('x (m)')
      plt.ylabel('u (m/s)')
      plt.ylim([0,2.2])
      plt.title(title)
      plt.show()

u,x = convection(151, 51, 0.5, 2.0, 0.5)
plot_convection(u,x,151,'Figure 1: c=0.5m/s, nt=151, nx=51, tmax=0.5s')