from pydoc import getpager
from matplotlib import pyplot as plt
import pandas as pd
import numpy as np
import argparse
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
colormap = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
results_folder = "results"
if not os.path.isdir(results_folder):
  os.mkdir(results_folder)
  
def plot_efficiency():
  i = 0
  init_default()
  plt.figure(figsize=[15, 10])
  for file_name in os.listdir(results_folder):
    if ".txt" in file_name:
      df = pd.read_table(f"./{results_folder}/{file_name}", sep='\t', index_col = None, header = 0)
      matrix_size = int(file_name[3:-4])
      color = colormap[i]
      T1 = np.array(df[df["ThreadsNumber"] == 1]["ElapsedTime"])[0]
      S = T1 / np.array(df["ElapsedTime"]); 
      p = np.array(df["ThreadsNumber"])
      plt.plot(p, S / p, 'o-', color=color, markerfacecolor=(1, 0, 0, 0), 
                    markeredgecolor=color, ms = 10, label=f"matrix_size = {matrix_size}")
      i += 1
  plt.xlabel("ThreadsNumber")
  plt.ylabel("Efficiency")
  plt.grid()
  plt.legend()
  plt.tight_layout()
  plt.savefig(f"./{results_folder}/efficiency.png")

def plot_acceleration():
  i = 0
  init_default()
  plt.figure(figsize=[15, 10])
  for file_name in os.listdir(results_folder):
    if ".txt" in file_name:
      df = pd.read_table(f"./{results_folder}/{file_name}", sep='\t', index_col = None, header = 0)
      matrix_size = int(file_name[3:-4])
      color = colormap[i]
      T1 = np.array(df[df["ThreadsNumber"] == 1]["ElapsedTime"])[0]
      S = T1 / np.array(df["ElapsedTime"]); 
      p = np.array(df["ThreadsNumber"])
      plt.plot(p, S, 'o-', color=color, markerfacecolor=(1, 0, 0, 0), 
                    markeredgecolor=color, ms = 10, label=f"matrix_size = {matrix_size}")
      i += 1
  plt.xlabel("ThreadsNumber")
  plt.ylabel("Acceleration")
  plt.grid()
  plt.legend()
  plt.tight_layout()
  plt.savefig(f"./{results_folder}/acceleration.png")


def plot_time():
  i = 0
  init_default()
  plt.figure(figsize=[15, 10])
  for file_name in os.listdir(results_folder):
    if ".txt" in file_name:
      df = pd.read_table(f"./{results_folder}/{file_name}", sep='\t', index_col = None, header = 0)
      matrix_size = int(file_name[3:-4])
      color = colormap[i]
      T = np.array(df["ElapsedTime"]); 
      p = np.array(df["ThreadsNumber"])
      plt.plot(p, T, 'o-', color=color, markerfacecolor=(1, 0, 0, 0), 
                    markeredgecolor=color, ms = 10, label=f"matrix_size = {matrix_size}")
      i += 1
  plt.xlabel("ThreadsNumber")
  plt.ylabel("ElapsedTime")
  plt.yscale('log')
  plt.grid()
  plt.legend()
  plt.tight_layout()
  plt.savefig(f"./{results_folder}/elapsed_time.png")

plot_efficiency()
plot_acceleration()
plot_time()