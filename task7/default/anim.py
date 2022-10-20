import argparse
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import argparse


def get_parsed() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description='size')
  parser.add_argument('m', type=int, 
                    help='number of rows')
  parser.add_argument('n', type=int, 
                    help='number of cols')                  
  args = parser.parse_args()
  return args

def animate_heat_map():
    fig = plt.figure()
    with open("out.txt") as f:
      args = get_parsed()
      lines = [ " ".join(line.split()).split(" ") for line in f if " ".join(line.split()) != '']
      lines = [[float(num) for num in line] for line in lines]
      data = lines[0:args.m]
      ax = sns.heatmap(data, vmin=0, vmax=1)
      def init():
        plt.clf()
        ax = sns.heatmap(data, vmin=0, vmax=1)

      def animate(i):
        plt.clf()
        data = lines[args.m * (i): args.m * (i + 1)]
        ax = sns.heatmap(data, vmin=0, vmax=1)

      anim = animation.FuncAnimation(fig, animate, frames = range(int(len(lines)/args.m)), init_func=init, interval=1, repeat=False)

      plt.show()


if __name__ == "__main__":
    animate_heat_map()