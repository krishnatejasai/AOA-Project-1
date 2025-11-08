#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <cmath>
using namespace std;
using steady_clock = chrono::steady_clock;

// Greedy problem: Given a binary array A (1 = tree present), remove minimum trees so that
// there are no K consecutive 1s. Greedy: scan left-to-right, keep a counter of consecutive ones;
// when counter == K, remove the current tree (count++ removals) and reset counter = 0.
// This yields minimum number of removals.

struct GreedyResult {
    int removals;
    long long operations; // simple op count
};

GreedyResult greedy_min_removals(const vector<int>& A, int K) {
    int n = (int)A.size();
    int cnt = 0;
    int removals = 0;
    long long ops = 0;
    for (int i = 0; i < n; ++i) {
        ops++;
        if (A[i] == 1) {
            cnt++;
            if (cnt == K) {
                // remove this tree
                removals++;
                cnt = 0; // after removal, consecutive surviving ones reset
            }
        } else {
            cnt = 0;
        }
    }
    return {removals, ops};
}

// Divide & Conquer problem: Archaeological dating (binary search).
// We model layers as an array 'ages' sorted nondecreasing with depth; given a threshold T,
// we want the largest index i such that ages[i] <= T (or -1 if none). Binary search counts queries.

struct DnCResult {
    int idx;
    int queries;
    long long operations;
};

DnCResult binary_search_last_leq(const vector<int>& ages, int T) {
    int lo = 0, hi = (int)ages.size() - 1;
    int ans = -1;
    int queries = 0;
    long long ops = 0;
    while (lo <= hi) {
        ops++;
        int mid = lo + (hi - lo) / 2;
        queries++;
        if (ages[mid] <= T) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return {ans, queries, ops};
}

// Utilities for experiments
static std::mt19937_64 rng((uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> random_binary_array(int n, double p_one) {
    vector<int> A(n);
    std::bernoulli_distribution d(p_one);
    for (int i = 0; i < n; ++i) A[i] = d(rng) ? 1 : 0;
    return A;
}

vector<int> random_monotonic_ages(int n, int max_step=5) {
    vector<int> ages(n);
    int cur = 0;
    uniform_int_distribution<int> step(1, max_step);
    for (int i = 0; i < n; ++i) {
        cur += step(rng);
        ages[i] = cur;
    }
    return ages;
}

int run_greedy_once(int n, int K, double p_one, long long &time_ns, long long &ops_out) {
    auto A = random_binary_array(n, p_one);
    auto t0 = steady_clock::now();
    auto res = greedy_min_removals(A, K);
    auto t1 = steady_clock::now();
    time_ns = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    ops_out = res.operations;
    return res.removals;
}

pair<int,int> run_dnc_once(int n, long long &time_ns, int &queries_out) {
    auto ages = random_monotonic_ages(n);
    // pick a random threshold T between min and max
    uniform_int_distribution<int> pick(0, ages.back());
    int T = pick(rng);
    auto t0 = steady_clock::now();
    auto res = binary_search_last_leq(ages, T);
    auto t1 = steady_clock::now();
    time_ns = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
    queries_out = res.queries;
    return {res.idx, T};
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool do_experiments = false;
    string out_csv = "results.csv";
    for (int i = 1; i < argc; ++i) {
        string s = argv[i];
        if (s == "--experiments") do_experiments = true;
        else if (s == "--out" && i + 1 < argc) { out_csv = argv[++i]; }
    }

    if (!do_experiments) {
        cout << "Run with --experiments --out PATH to run experiments and write CSV.\n";
        return 0;
    }

    // Experiment parameters
    vector<int> ns = {1000, 2000, 5000, 10000, 20000, 50000, 100000};
    int trials = 20;
    double p_one = 0.9; // fairly dense forest
    int K = 5; // avoid 5 consecutive trees

    // Prepare output CSV
    ofstream fout(out_csv);
    fout << "n,algorithm,avg_time_ms,avg_ops,avg_result\n";

    for (int n : ns) {
        // Greedy
        double sum_time_ms = 0;
        double sum_ops = 0;
        double sum_removals = 0;
        for (int t = 0; t < trials; ++t) {
            long long time_ns; long long ops_out;
            int rem = run_greedy_once(n, K, p_one, time_ns, ops_out);
            sum_time_ms += (double)time_ns / 1e6;
            sum_ops += (double)ops_out;
            sum_removals += rem;
        }
        fout << n << ",greedy," << (sum_time_ms / trials) << "," << (long long)(sum_ops / trials)
             << "," << (sum_removals / trials) << "\n";

        // D&C (binary search)
        sum_time_ms = 0; double sum_queries = 0; double sum_idx = 0;
        for (int t = 0; t < trials; ++t) {
            long long time_ns; int queries_out;
            auto res = run_dnc_once(n, time_ns, queries_out);
            sum_time_ms += (double)time_ns / 1e6;
            sum_queries += queries_out;
            sum_idx += res.first;
        }
        fout << n << ",dnc," << (sum_time_ms / trials) << "," << (long long)(sum_queries / trials)
             << "," << (sum_idx / trials) << "\n";
        cerr << "Completed n=" << n << "\n";
    }

    fout.close();
    cout << "Experiments completed, results written to: " << out_csv << "\n";
    return 0;
}
