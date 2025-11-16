import pandas as pd  # Import pandas for data manipulation
import matplotlib.pyplot as plt  # Import matplotlib for plotting
from pathlib import Path  # Import Path for file path handling

# File definitions: mapping labels to data file paths
files = {
    "T = 1.0": "data_output/energy_hist_T1.txt",
    "T = 2.4": "data_output/energy_hist_T24.txt",
}

# Mapping labels to temperature values
temp_map = {"T = 1.0": 1.0, "T = 2.4": 2.4}

def read(files_map):
    parts = []  # List to collect DataFrames
    for label, rel_path in files_map.items():
        path = Path(rel_path)  # Create a Path object for the file
        df = pd.read_csv(
            path,
            sep=r"\s+",  # Use whitespace as separator
            header=None,  # No header in the file
            names=["bins", "probability"]  # Assign column names
        )
        df["label"] = label  # Add label column
        df["T"] = temp_map[label]  # Add temperature column
        parts.append(df)  # Append DataFrame to list
    return pd.concat(parts, ignore_index=True)  # Concatenate all DataFrames

# ---- Plotting ----
df = read(files)  # Read and combine data from files

for label, g in df.groupby("label"):  # Group data by label
    plt.figure(figsize=(7, 4))  # Create a new figure
    plt.bar(g["bins"], g["probability"], width=0.02)  # Plot histogram as bar chart
    plt.xlabel("Energy")  # X-axis label
    plt.xlim((-2 , 0))  # Set x-axis limits
    plt.ylabel("Probability")  # Y-axis label
    plt.title(f"Histogram for {label}")  # Plot title
    plt.grid(True, alpha=0.3)  # Add grid with transparency
    plt.tight_layout()  # Adjust layout
    plt.savefig(f"figs/histogram_for_{label}.pdf")  # Save figure as PDF
    plt.show()  # Display the plot
