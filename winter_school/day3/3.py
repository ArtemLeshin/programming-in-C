import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)

H = 10-np.sqrt(X**2 + Y**2)

x0, y0 = 2, 2
z0 =10-np.sqrt(x0**2 + y0**2)
print(f"z({x0}, {y0}) = {z0:.4f}")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, H, cmap='coolwarm')
ax.set_xlabel('x'); ax.set_ylabel('y'); ax.set_zlabel('z')
plt.show()