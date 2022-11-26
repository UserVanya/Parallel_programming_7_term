import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os
def init_default():
  SMALL_SIZE = 16
  MEDIUM_SIZE = 18
  BIGGER_SIZE = 20

  plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
  plt.rc('axes', titlesize=SMALL_SIZE)     # fontsize of the axes title
  plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
  plt.rc('xtick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
  plt.rc('ytick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
  plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
  plt.rc('figure', titlesize=BIGGER_SIZE)  # fontsize of the figure title
  plt.rc('figure', figsize=[15, 10])

print(os.listdir("."))
dfs = {}
for file in os.listdir("."):
  if(file.endswith(".txt")):
    dfs[file[2:-4]] = pd.read_table(file, sep='\t', index_col = None, header = 0)
init_default()
for b, df in dfs.items():
  b = float(b)
  if (b <= 1):
    plt.plot(df['x'], df['y'], label=f"b = {b}")
plt.legend()
plt.grid()
plt.xlabel("x")
plt.ylabel("y")
plt.savefig("plot.png")
plt.close()
init_default()
for b, df in dfs.items():
  b = float(b)
  if (b > 1):
    plt.plot(df['x'], df['y'], label=f"b = {b}")
plt.legend()
plt.xlabel("x")
plt.ylabel("y")
plt.grid()
plt.savefig("plot_near_1.5.png")