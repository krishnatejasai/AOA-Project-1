# AOA Project 1 — Greedy and Divide & Conquer Problems (C++)

This repository contains implementations and experiments for two problems required by the assignment:

- Greedy algorithm: Forest fire prevention — minimum removals to avoid K consecutive trees (linear-time greedy)
- Divide & Conquer algorithm: Archaeological layer dating — binary search to find boundary layer (logarithmic-time)

Files:
- `src/main.cpp` — C++ program implementing both algorithms and an experiment harness that outputs CSVs
- `experiments/plot_results.py` — Python script to plot experimental timing results (requires matplotlib)
- `requirements.txt` — Python plotting dependency
- `report/main.tex` — LaTeX report template (IEEE-like) with placeholders for figures and code appendix

How to run experiments (on macOS with zsh):

1. Compile:
```bash
g++ -O2 -std=c++17 -pthread src/main.cpp -o bin/algos
```

2. Run experiments (creates `results.csv`):
```bash
mkdir -p results bin
./bin/algos --experiments --out results/results.csv
```

3. Plot (requires Python packages in `requirements.txt`):
```bash
python3 -m pip install -r requirements.txt
python3 experiments/plot_results.py results/results.csv results/plots
```

The LaTeX report in `report/` is a template you can open on Overleaf and complete.

Appendix in the LaTeX file contains the C++ code and plotting commands.
