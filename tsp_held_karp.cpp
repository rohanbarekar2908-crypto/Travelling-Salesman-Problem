#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long INF = 1000000000000000LL;   // "no route" sentinel

class TravellingSalesman {
private:
    int n;
    vector<string> names;
    vector<vector<long long>> cost;

public:
    TravellingSalesman(const vector<string>& cityNames,
                       const vector<vector<long long>>& matrix)
        : n(static_cast<int>(cityNames.size())), names(cityNames), cost(matrix) {}

    void solve() const {
        if (n == 1) {
            cout << "\nOnly one city. Tour cost: 0\n";
            return;
        }

        const int FULL = 1 << n;

        // dp[mask][last] = cheapest way to start at city 0, visit exactly the
        // cities in mask (bit 0 is always set), and finish at city 'last'.
        vector<vector<long long>> dp(FULL, vector<long long>(n, INF));
        vector<vector<int>> from(FULL, vector<int>(n, -1));

        dp[1][0] = 0;

        for (int mask = 1; mask < FULL; mask += 2) {      // only masks containing city 0
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1 << last)) || dp[mask][last] >= INF) continue;

                for (int next = 1; next < n; ++next) {
                    if (mask & (1 << next)) continue;
                    if (cost[last][next] >= INF) continue;

                    int newMask = mask | (1 << next);
                    long long candidate = dp[mask][last] + cost[last][next];
                    if (candidate < dp[newMask][next]) {
                        dp[newMask][next] = candidate;
                        from[newMask][next] = last;
                    }
                }
            }
        }

        // Close the tour by returning to city 0.
        long long best = INF;
        int bestLast = -1;
        for (int last = 1; last < n; ++last) {
            if (dp[FULL - 1][last] >= INF || cost[last][0] >= INF) continue;
            long long total = dp[FULL - 1][last] + cost[last][0];
            if (total < best) {
                best = total;
                bestLast = last;
            }
        }

        if (bestLast == -1) {
            cout << "\nNo tour visits every city and returns to the start.\n";
            return;
        }

        // Rebuild the route by following the 'from' links backwards.
        vector<int> route;
        int mask = FULL - 1;
        int cur = bestLast;
        while (cur != -1) {
            route.push_back(cur);
            int prev = from[mask][cur];
            mask ^= (1 << cur);
            cur = prev;
        }
        reverse(route.begin(), route.end());
        route.push_back(0);

        cout << "\n========= BEST TOUR =========\n";
        cout << left << setw(16) << "From" << setw(16) << "To" << "Cost\n";
        cout << string(40, '-') << '\n';
        for (size_t i = 0; i + 1 < route.size(); ++i) {
            cout << left << setw(16) << names[route[i]]
                 << setw(16) << names[route[i + 1]]
                 << cost[route[i]][route[i + 1]] << '\n';
        }
        cout << string(40, '-') << '\n';
        cout << "Total cost: " << best << '\n';
    }
};

int main() {
    int n;
    cout << "Number of cities (1 to 16): ";
    if (!(cin >> n) || n < 1 || n > 16) {
        cerr << "Number of cities must be between 1 and 16.\n";
        return 1;
    }

    vector<string> names(n);
    cout << "Enter the city names (no spaces, first one is the start):\n";
    for (int i = 0; i < n; ++i) cin >> names[i];

    vector<vector<long long>> cost(n, vector<long long>(n, INF));
    cout << "Enter the " << n << "x" << n
         << " cost matrix (use -1 where there is no direct road):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long c;
            if (!(cin >> c)) {
                cerr << "Invalid cost value.\n";
                return 1;
            }
            if (c < -1) {
                cerr << "Costs must be non-negative, or -1 for no road.\n";
                return 1;
            }
            if (i != j && c != -1) cost[i][j] = c;
        }
    }

    TravellingSalesman tsp(names, cost);
    tsp.solve();
    return 0;
}

/*
Sample input:
4
A B C D
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

Expected: total cost 80 (for example A -> B -> D -> C -> A).
*/
