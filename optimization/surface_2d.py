from matplotlib import animation
from matplotlib.colors import LogNorm
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d


# 3D Surface Plot
def createSurfacePlot(x, y, f, minXY, minF, minMaxX, minMaxY):
    fig = plt.figure(figsize=(8, 5))
    ax = plt.axes(projection='3d', elev=50, azim=-50)
    ax.plot_surface(x, y, z, 
        norm=LogNorm(),
        rstride=1, cstride=1, 
        edgecolor='none', alpha=.8, 
        cmap=plt.cm.jet)
    # ax.plot(lineX, lineY, lineF, 
    #     marker='*', color='r', 
    #     alpha=.4, label='Gradient descent')
    ax.plot(*minXY, minF, 'r*', markersize=10)

    ax.set_xlabel('$x$')
    ax.set_ylabel('$y$')
    ax.set_zlabel('$z$')

    ax.set_xlim(minMaxX)
    ax.set_ylim(minMaxY)
    plt.show()


#2D Contour Plot and Gradient Vector Field
def createControurPlot(x, y, z, minXY, minMaxX, minMaxY, path):
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.contour(x, y, z, 
        levels=np.logspace(0, 5, 35), norm=LogNorm(),
        cmap=plt.cm.jet)
    ax.quiver(path[0,:-1], path[1,:-1], 
            path[0,1:]-path[0,:-1], path[1,1:]-path[1,:-1], 
            scale_units='xy', angles='xy', scale=1, color='k')

    ax.plot(*minXY, 'r*', 
        markersize=18)

    ax.set_xlabel('$x$')
    ax.set_ylabel('$y$')

    ax.set_xlim(minMaxX)
    ax.set_ylim(minMaxY)

    plt.show()

    # cp = ax.contour(X, Y, Z, 
    #     colors='black', linestyles='dashed', linewidths=1)
    # ax.clabel(cp, inline=1, fontsize=10)
    # cp = plt.contourf(X, Y, Z)
    # plt.colorbar(cp, ax=ax)

def createControurAnim(x, y, z, minXY, minMaxX, minMaxY, path):
    fig, ax = plt.subplots(figsize=(10, 6))

    ax.contour(x, y, z, 
        levels=np.logspace(0, 5, 35), norm=LogNorm(), cmap=plt.cm.jet)
    ax.plot(*minXY, 'r*', markersize=18)

    line, = ax.plot([], [], 'b', label='Newton-CG', lw=2)
    point, = ax.plot([], [], 'bo')

    ax.set_xlabel('$x$')
    ax.set_ylabel('$y$')
    ax.set_xlim(minMaxX)
    ax.set_ylim(minMaxY)

    ax.legend(loc='upper left')

    def init():
        line.set_data([], [])
        point.set_data([], [])
        return line, point

    def animate(i):
        line.set_data(*path[::,:i])
        point.set_data(*path[::,i-1:i])
        return line, point

    anim = animation.FuncAnimation(fig, animate, init_func=init,
            frames=path.shape[1], interval=60, 
            repeat_delay=5, blit=True)
    plt.show()

def createSurfaceAnim(x, y, z, f, minXY, minMaxX, minMaxY, path):
    fig = plt.figure(figsize=(8, 5))
    ax = plt.axes(projection='3d', elev=50, azim=-50)
    ax.plot_surface(x, y, z, 
        norm=LogNorm(),
        rstride=1, cstride=1, 
        edgecolor='none', alpha=.8, 
        cmap=plt.cm.jet)
    ax.plot(*minXY, f(*minXY), 'r*', markersize=10)

    
    line, = ax.plot([], [], [], 'b', label='Newton-CG', lw=2)
    point, = ax.plot([], [], [], 'bo')

    def init():
        line.set_data([], [])
        line.set_3d_properties([])
        point.set_data([], [])
        point.set_3d_properties([])
        return line, point

    def animate(i):
        line.set_data(path[0,:i], path[1,:i])
        line.set_3d_properties(f(*path[::,:i]))
        point.set_data(path[0,i-1:i], path[1,i-1:i])
        point.set_3d_properties(f(*path[::,i-1:i]))
        return line, point

    ax.set_xlabel('$x$')
    ax.set_ylabel('$y$')
    ax.set_zlabel('$z$')

    ax.set_xlim(minMaxX)
    ax.set_ylim(minMaxY)

    anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=path.shape[1], interval=60, 
                               repeat_delay=5, blit=True)

    plt.show()
