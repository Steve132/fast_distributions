import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_points(file_path):
    points = []
    with open(file_path, 'r') as file:
        for line in file:
            points.append(list(map(float, line.strip().split())))
    return np.array(points)

def plot_points(points):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(points[:, 0], points[:, 1], points[:, 2], c='b', marker='o')

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    ax.set_title('3D Scatter Plot')

    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python plot_3d_points.py <path_to_points_file>")
        sys.exit(1)

    file_path = sys.argv[1]
    points = read_points(file_path)
    plot_points(points)
