import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib import cm

mpl.rcParams['legend.fontsize'] = 10

def plot_3d(x, t, u, title):
   fig = plt.figure()
   ax = plt.axes(projection='3d')
   ax.plot_surface(x, t, u,
               rstride=1, cstride=1,
               cmap='viridis', edgecolor='none')
   ax.set_title(title)
   ax.set_xlabel('t')
   ax.set_ylabel('x')
   ax.set_zlabel('u')
   plt.show()

def u( x , y , t ):
	return -np.cos( 2*y )*np.sin ( 3*x )

def v(x, y , t ):
	return 3*np.cos( 3*x )*np.sin ( y )

def f ( x , y , t ):
	return 0

def beg_t0 ( x , y ):
	return 1 + np.tan(( y -np.pi / 3 )* 4 )

def W(arr, n , i , j, h_x):
	if arr[n][i][j]  > 0:
		return (arr[n][i][j] - arr[n][i-1][j]  ) / h_x
	else:
		return (arr[n][i+1][j] - arr[n][i][j]) / h_x

def Q(arr, n , i , j, h_y):
	if arr[n][i][j]  > 0:
		return (arr[n][i][j] - arr[n][i][j-1]  ) / h_y
	else:
		return (arr[n][i][j+1] - arr[n][i][j]) / h_y


x0 = 0
x1 = 2
y0 = 0
y1 = np.pi
t0 = 0
t1 = 1
Nx = 50
Ny = 50
Nt = 200
tay = (t1 -t0) / Nt
h_x = (x1 - x0) / Nx
h_y = (y1 - y0) / Ny
Xvector = range(int(x0), int(x1), int(Nx + 1) )
Yvector = range( y0 , int(y1) , int(Ny + 1) )
Tvector = range( t0 , t1 , int(Nt + 1) )

X, Y = np.meshgrid(Xvector, Yvector)


c = np.zeros ((Nt + 1 , Nx + 1 , Ny + 1))

for i in range(1, Nx + 1):
	for j in range(1, Ny + 1):
		c[1][i][j] = beg_t0(x0 + ( i - 1 ) * h_x, y0 + ( j - 1 ) * h_y )
c_up = c

for n in range(1, Nt):
	for i in range(2, Nx):
		for j in range(2, Ny):
			xi = x0 + ( i - 1 ) *h_x
			yj = y0 + ( j - 1 ) * h_y
			tn = t0 + ( n - 1 ) * tay

			c[n + 1][i][j]  = c[n][i][j] + tay*(f( xi , yj , tn )-u(xi, yj , tn)*
							(c[n][i+1][j]- c[n][i-1][j])/(2 *h_x)- v(xi, yj , tn )*( c[n][i][j + 1] - c[n][i][j-1]))/(2*h_y)
			
			c_up[n + 1][i][j] = c_up[n , i , j] + tay * ( f ( xi , yj , tn ) -
								u( xi , yj , tn )*W(c_up , n , i , j, h_x)-
								v( xi , yj , tn )*Q(c_up , n , i , j,h_y))


# Number of timesteps
nsteps = 101
# Output 4 figures at these timesteps
mfig = [0, 10, 50, 100]
fignum = 0
fig = plt.figure()
for m in range(nsteps):
    u0, u = do_timestep(u0, u)
    if m in mfig:
        fignum += 1
        print(m, fignum)
        ax = fig.add_subplot(220 + fignum)
        im = ax.imshow(u.copy(), cmap=plt.get_cmap('hot'), vmin=Tcool,vmax=Thot)
        ax.set_axis_off()
        ax.set_title('{:.1f} ms'.format(m*dt*1000))
fig.subplots_adjust(right=0.85)
cbar_ax = fig.add_axes([0.9, 0.15, 0.03, 0.7])
cbar_ax.set_xlabel('$T$ / K', labelpad=20)
fig.colorbar(im, cax=cbar_ax)
plt.show()

# plot_3d(X, Y, c[1][:][:], 'Время t = 0')