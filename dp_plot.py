import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

L = [0,0]
m = [0,0]
ext = "o2"
with open("params_"+ext+".csv", "r") as f:
    params = f.readline().strip().split(",")
    L[0] = float(params[0])
    L[1] = float(params[1])
    m[0] = float(params[2])
    m[1] = float(params[3])

time, phi1, phi2 = np.loadtxt("output_"+ext+".csv",delimiter=",",usecols=(0,1,2),unpack=True)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.xaxis.set_visible(False)
ax.yaxis.set_visible(False)

def animate(t):
    ax.clear()
    ax.set_xlim(-1.1*(L[0]+L[1]),1.1*(L[0]+L[1]))
    ax.set_ylim(-1.1*(L[0]+L[1]),1.1*(L[0]+L[1]))
    ax.set_aspect('equal')
    xpoints = [0,L[0]*math.sin(phi1[t]),L[0]*math.sin(phi1[t])+L[1]*math.sin(phi2[t])]
    ypoints = [0,-L[0]*math.cos(phi1[t]),-L[0]*math.cos(phi1[t])-L[1]*math.cos(phi2[t])]
    ax.plot(xpoints,ypoints,color="brown")

    ax.scatter([0],[0])
    circle1 = plt.Circle((xpoints[1],ypoints[1]),0.08,color='brown')
    circle2 = plt.Circle((xpoints[2],ypoints[2]),0.08,color='brown')
    ax.add_artist(circle1)
    ax.add_artist(circle2)

anim = animation.FuncAnimation(fig,animate,frames=len(time),interval=1,blit=False)
plt.show()
