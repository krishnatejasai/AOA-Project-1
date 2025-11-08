#!/usr/bin/env python3
import sys
import os
import pandas as pd
import matplotlib.pyplot as plt

def plot(csv_in, out_dir):
    df = pd.read_csv(csv_in)
    os.makedirs(out_dir, exist_ok=True)

    # Separate algorithms
    greedy = df[df.algorithm == 'greedy']
    dnc = df[df.algorithm == 'dnc']

    plt.figure(figsize=(6,4))
    plt.plot(greedy.n, greedy.avg_time_ms, marker='o', label='Greedy (time)')
    plt.plot(dnc.n, dnc.avg_time_ms, marker='o', label='D&C (time)')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('n (log scale)')
    plt.ylabel('avg time (ms, log scale)')
    plt.title('Runtime vs n (log-log)')
    plt.legend()
    plt.grid(True, which='both', ls='--', lw=0.5)
    p1 = os.path.join(out_dir, 'time_loglog.png')
    plt.savefig(p1, dpi=200, bbox_inches='tight')
    print('Saved', p1)

    # Ops plot (linear x)
    plt.figure(figsize=(6,4))
    plt.plot(greedy.n, greedy.avg_ops, marker='o', label='Greedy (ops)')
    plt.plot(dnc.n, dnc.avg_ops, marker='o', label='D&C (queries)')
    plt.xlabel('n')
    plt.ylabel('avg ops (count)')
    plt.title('Operation counts vs n')
    plt.legend()
    plt.grid(True, ls='--', lw=0.5)
    p2 = os.path.join(out_dir, 'ops.png')
    plt.savefig(p2, dpi=200, bbox_inches='tight')
    print('Saved', p2)

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: plot_results.py results.csv out_dir')
        sys.exit(1)
    plot(sys.argv[1], sys.argv[2])
