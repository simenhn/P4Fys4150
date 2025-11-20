import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path

LATTICE_SIZE      = 8
GRID_LINE_WIDTH   = 1.2
ARROW_HEAD_WIDTH  = 0.2
ARROW_HEAD_LENGTH = 0.15
MARGIN            = 0.5

FIG_DIR = Path(__file__).parent.parent.absolute() / "figs"

def lattice(size):
    """Generate a 2D lattice of given size with random spins (+1 or -1)."""
    return np.random.choice([-1, 1], size=(size, size))

def plot_arrow_lattice(lat, shear_factor=0.3):
    """Plot the lattice as an arrow grid where arrows indicate spin direction.
    
    Args:
        lat: 2D array of spin values (+1 or -1)
        shear_factor: Amount of shear to apply (default 0.3)
    """
    fig, ax = plt.subplots(figsize=(8, 8))
    
    L = lat.shape[0]
    
    # Apply shear transformation to coordinates
    # Shear matrix: x' = x + shear_factor * y, y' = y
    def shear_transform(x, y):
        x_sheared = x + shear_factor * y
        y_sheared = y
        return x_sheared, y_sheared
    
    # Draw sheared grid lines
    for i in range(L):
        # Horizontal lines
        x_line = np.array([0, L - 1])
        y_line = np.array([i, i])
        x_sh, y_sh = shear_transform(x_line, y_line)
        ax.plot(x_sh, y_sh, color='black', linewidth=GRID_LINE_WIDTH, alpha=0.8)
        
        # Vertical lines
        x_line = np.array([i, i])
        y_line = np.array([0, L - 1])
        x_sh, y_sh = shear_transform(x_line, y_line)
        ax.plot(x_sh, y_sh, color='black', linewidth=GRID_LINE_WIDTH, alpha=0.8)
    
    # Plot arrows at sheared grid intersections (midpoint on grid)
    for i in range(L):
        for j in range(L):
            # Transform the grid intersection point
            x_grid, y_grid = shear_transform(j, i)
            
            # Arrow direction - straight up or down (NOT sheared)
            dx = 0
            dy = lat[i, j] * 0.4
            
            # Place arrow origin so that midpoint is at grid intersection
            x_orig = x_grid
            y_orig = y_grid - dy / 2
            
            color = 'blue' if lat[i, j] == 1 else 'red'
            ax.arrow(x_orig, y_orig, dx, dy, 
                    head_width=ARROW_HEAD_WIDTH, head_length=ARROW_HEAD_LENGTH, 
                    fc=color, ec=color, alpha=0.8, linewidth=1.5)

    ax.set_xlim(-MARGIN, L - 1 + shear_factor * (L - 1) + MARGIN)
    ax.set_ylim(-MARGIN, L - 1 + MARGIN)
    ax.set_aspect('equal')
    ax.invert_yaxis()
    ax.axis('off')
    
    return fig, ax

if __name__ == "__main__":
    lattice_size = 8
    lat = lattice(lattice_size)
    
    # Plot as arrow grid
    plot_arrow_lattice(lat)
    plt.tight_layout(pad=0.1)
    plt.savefig(FIG_DIR / "lattice_arrow_plot.pdf")
