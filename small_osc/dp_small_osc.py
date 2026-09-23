import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def get_omega(g,ell):
    wp = np.sqrt((2+np.sqrt(2))*g/ell)
    wm = np.sqrt((2-np.sqrt(2))*g/ell)
    return (wp,wm)

def get_theta1(t,alpha,beta,wp,wm):
    
    theta1_nmp = 0.5*(alpha-beta/np.sqrt(2))*np.cos(wp*t)
    theta1_nmm = 0.5*(alpha+beta/np.sqrt(2))*np.cos(wm*t)
    
    return theta1_nmp + theta1_nmm
    
    
def get_theta2(t,alpha,beta,wp,wm):
    
    theta2_nmp = -0.5*(alpha*np.sqrt(2)-beta)*np.cos(wp*t)
    theta2_nmm =  0.5*(alpha*np.sqrt(2)+beta)*np.cos(wm*t)
    
    return theta2_nmp + theta2_nmm
    
g = 9.81
ell = 1.0

alpha = ( 2 ) * np.pi/180
beta  = (   5  ) * np.pi/180
filename = "animation8.gif"

(wp,wm) = get_omega(g,ell)
print(wp,wm)
print(2*np.pi/wp, 2*np.pi/wm)

time = np.linspace(0,10,300)
theta1 = get_theta1(time,alpha,beta,wp,wm)
theta2 = get_theta2(time,alpha,beta,wp,wm)

fig = plt.figure(figsize=(7, 4))

grid = fig.add_gridspec(2, 2,width_ratios=[1, 1.85],left=0,right=0.95,top=0.9,wspace=0.15,hspace=0)

ax_pd = fig.add_subplot(grid[:, 0])
ax_th1 = fig.add_subplot(grid[0, 1])
ax_th2 = fig.add_subplot(grid[1, 1])

th1_max = np.abs(alpha)+np.abs(beta)/np.sqrt(2)

th2_max = np.abs(alpha*np.sqrt(2))+np.abs(beta)

def animate(t):
    ax_pd.clear()
    ax_th1.clear()
    ax_th2.clear()
    
    ax_pd.set_xlim(-ell/3,ell/3)
    ax_pd.set_ylim(-2.1*ell,0.1*ell)
    ax_pd.set_aspect("equal", adjustable="box")
    ax_pd.axis("off")
    
    ax_th1.set_xlim(0,time[-1])
    ax_th1.set_ylim(-1.05*th1_max,1.05*th1_max)
    ax_th1.set_ylabel("$\\theta_1$")
    ax_th1.set_yticks([])
    ax_th1.set_xticks([])
    ax_th1.set_title("Initial Angles: $\\alpha={:.1f}^\circ$, $\\beta={}^\circ$".format(alpha*180/np.pi,beta*180/np.pi))
    
    
    ax_th2.set_ylim(-1.05*th2_max,1.05*th2_max)
    ax_th2.set_xlim(0,time[-1])
    ax_th2.set_ylabel("$\\theta_2$")
    ax_th2.set_yticks([])
    ax_th2.set_xlabel("time")
    
    
    ax_th1.plot(time,theta1)
    ax_th1.scatter(time[t],theta1[t],color='red')
    
    ax_th2.plot(time,theta2)
    ax_th2.scatter(time[t],theta2[t],color='red')
    
    x1 = ell*np.sin(theta1[t])
    y1 = -ell*np.cos(theta1[t])
    
    x2 = x1 + ell*np.sin(theta2[t])
    y2 = y1 - ell*np.cos(theta2[t])
    ax_pd.plot([0,x1,x2],[0,y1,y2],color='brown')
    ax_pd.scatter([x1,x2],[y1,y2],color='brown',s=250)
    ax_pd.scatter(0,0,color='black',s=20)
    ax_pd.plot([-ell/4,ell/4],[0,0],color='black')
   
anim = animation.FuncAnimation(fig,animate,frames=len(time),interval=1,blit=False)

writergif = animation.PillowWriter(fps=24)
anim.save(filename,writer=writergif)

plt.show()
    
