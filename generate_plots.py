#!/usr/bin/env python3
"""Simple plotting without pandas dependency"""
import csv
import matplotlib.pyplot as plt
import os

def create_plots():
    # Read CSV manually
    greedy_n, greedy_time, greedy_ops = [], [], []
    dnc_n, dnc_time, dnc_ops = [], [], []
    
    with open('results/results.csv', 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row['n'])
            time_ms = float(row['avg_time_ms'])
            ops = int(row['avg_ops'])
            
            if row['algorithm'] == 'greedy':
                greedy_n.append(n)
                greedy_time.append(time_ms)
                greedy_ops.append(ops)
            else:  # dnc
                dnc_n.append(n)
                dnc_time.append(time_ms)
                dnc_ops.append(ops)
    
    # Ensure output directories exist
    os.makedirs('results/plots', exist_ok=True)
    os.makedirs('report', exist_ok=True)
    
    # Plot 1: Runtime log-log
    plt.figure(figsize=(8, 6))
    plt.loglog(greedy_n, greedy_time, 'o-', label='Greedy O(n)', markersize=8, linewidth=2)
    plt.loglog(dnc_n, dnc_time, 's-', label='Binary Search O(log n)', markersize=8, linewidth=2)
    plt.xlabel('Input Size n (log scale)', fontsize=12)
    plt.ylabel('Average Runtime (ms, log scale)', fontsize=12)
    plt.title('Algorithm Runtime Comparison', fontsize=14)
    plt.legend(fontsize=11)
    plt.grid(True, which='both', alpha=0.3)
    plt.tight_layout()
    
    # Save to both locations
    plt.savefig('results/plots/time_loglog.png', dpi=300, bbox_inches='tight')
    plt.savefig('report/time_loglog.png', dpi=300, bbox_inches='tight')
    plt.close()
    
    # Plot 2: Operations count
    plt.figure(figsize=(8, 6))
    plt.plot(greedy_n, greedy_ops, 'o-', label='Greedy Operations', markersize=8, linewidth=2)
    plt.plot(dnc_n, dnc_ops, 's-', label='Binary Search Queries', markersize=8, linewidth=2)
    plt.xlabel('Input Size n', fontsize=12)
    plt.ylabel('Average Operations Count', fontsize=12)
    plt.title('Operation Count Verification', fontsize=14)
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    # Save to both locations
    plt.savefig('results/plots/ops.png', dpi=300, bbox_inches='tight')
    plt.savefig('report/ops.png', dpi=300, bbox_inches='tight')
    plt.close()
    
    print("Plots generated successfully!")
    print("- results/plots/time_loglog.png")
    print("- results/plots/ops.png")
    print("- report/time_loglog.png (for Overleaf)")
    print("- report/ops.png (for Overleaf)")

if __name__ == '__main__':
    create_plots()