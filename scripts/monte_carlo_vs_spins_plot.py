import pandas as pd
import matplotlib.pyplot as plt



#  Load datasets directly into pandas DataFrames
files = {
    "T=1.0 random":  "data_output/energy_T1_random.txt", #here we import the 4 different files into a dataframe we are creating
    "T=1.0 ordered": "data_output/energy_T1_not-random.txt",
    "T=2.4 random":  "data_output/energy_T2_random.txt",
    "T=2.4 ordered": "data_output/energy_T2_not-random.txt",
}

dfs = {}
for label, path in files.items():
    dfs[label] = pd.read_csv(path, sep=r"\s+", names=["cycle", "E_inst", "E_mean"]) # Here we segment the files with the correct labels into corretly being opened.

for name, df in dfs.items():
    print(name, "min/max of columns:") #this is something for printing out the results of the data
    print(df[["E_inst", "E_mean"]].min(), "\n", df[["E_inst", "E_mean"]].max(), "\n") #here we print out the minimum and the max vales for our E_inst and E_mean


plt.figure(figsize=(9,6))
for label, df in dfs.items():
    plt.plot(df["cycle"], df["E_inst"], "--", alpha=0.7, lw=1.2, label=label) #We plot the cycles with the E_inst


#this is the polish for the plotting
plt.xscale("log")
plt.xlabel("Monte Carlo cycles")
plt.ylabel("Instantaneous energy per spin")
plt.title("Instantaneous energy per spin vs Monte Carlo cycles")
plt.grid(True, ls="--", alpha=0.4)
plt.legend()
plt.tight_layout()
plt.savefig("figs/burnin_cycle_e-inst.pdf")

#now we plot the 2nd figure that is the mean values of E based on the cycles
plt.figure(figsize=(9,6))
for label, df in dfs.items():
    plt.plot(df["cycle"], df["E_mean"], lw=2, label=label)
#and again polish for the plotting.
plt.xscale("log")
plt.xlabel("Monte Carlo cycles")
plt.ylabel("Running mean energy per spin")
plt.title("Running mean energy per spin vs Monte Carlo cycles")
plt.grid(True, ls="--", alpha=0.4)
plt.legend()
plt.tight_layout()
plt.savefig("figs/burnin_cycle_e-mean.pdf")


