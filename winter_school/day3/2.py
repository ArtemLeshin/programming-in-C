import numpy as np
import matplotlib.pyplot as plt


x = np.linspace(-2, 2, 100)
y = np.linspace(-2, 2, 100)
X, Y = np.meshgrid(x, y)

T = 50*np.exp(-(X**2 + Y**2))+20

x0, y0 = 0.8, 0.6
z0 = 50*np.exp(-(x0**2 + y0**2))+20
print(f"z({x0}, {y0}) = {z0:.4f}")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, T, cmap='viridis')
ax.set_xlabel('x'); ax.set_ylabel('y'); ax.set_zlabel('z')
plt.show()