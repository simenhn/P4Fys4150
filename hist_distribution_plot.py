import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# File definitions
files = {
    "T = 1.0": "data_output/energy_hist_T1.txt",
    "T = 2.4": "data_output/energy_hist_T24.txt",
}

temp_map = {"T = 1.0": 1.0, "T = 2.4": 2.4}

def read(files_map):
    parts = []
    for label, rel_path in files_map.items():
        path = Path(rel_path)
        df = pd.read_csv(
            path,
            sep=r"\s+",
            header=None,
            names=["bins", "probability"]
        )
        df["label"] = label
        df["T"] = temp_map[label]
        parts.append(df)
    return pd.concat(parts, ignore_index=True)


# ---- Plotting ----
df = read(files)

for label, g in df.groupby("label"):
    plt.figure(figsize=(7, 4))
    plt.bar(g["bins"], g["probability"], width=0.02)
    plt.xlabel("Energy")
    plt.xlim((-2 , 0))
    plt.ylabel("Probability")
    plt.title(f"Histogram for {label}")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"figs/histogram_for_{label}.pdf")
    plt.show()



