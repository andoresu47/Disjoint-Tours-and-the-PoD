from z3 import *

def prove_case(n, s=0, t=None):
    if t is None:
        t = n - 1

    V = list(range(n))
    P = [0, 1]

    # x[p][i][j] = Bool: path p uses directed edge i->j
    x = {
        p: [[Bool(f"x_{p}_{i}_{j}") for j in V] for i in V]
        for p in P
    }

    # u[p][v] = Int: position of vertex v in path p
    u = {
        p: [Int(f"u_{p}_{v}") for v in V]
        for p in P
    }

    sol = Solver()

    # No self-loops
    for p in P:
        for i in V:
            sol.add(x[p][i][i] == False)

    # Degree constraints for Hamiltonian s-t path
    for p in P:
        for v in V:
            out_deg = Sum([If(x[p][v][j], 1, 0) for j in V])
            in_deg  = Sum([If(x[p][i][v], 1, 0) for i in V])

            if v == s:
                sol.add(in_deg == 0, out_deg == 1)
            elif v == t:
                sol.add(in_deg == 1, out_deg == 0)
            else:
                sol.add(in_deg == 1, out_deg == 1)

        # Order variables: permutation 0..n-1 with fixed endpoints
        for v in V:
            sol.add(u[p][v] >= 0, u[p][v] <= n - 1)
        sol.add(u[p][s] == 0)
        sol.add(u[p][t] == n - 1)
        sol.add(Distinct(u[p]))

        # MTZ-style: used edge implies forward movement in order
        for i in V:
            for j in V:
                if i != j:
                    sol.add(Implies(x[p][i][j], u[p][j] >= u[p][i] + 1))

    # Undirected edge-disjointness between the two paths
    for i in V:
        for j in V:
            if i < j:
                e0 = Or(x[0][i][j], x[0][j][i])
                e1 = Or(x[1][i][j], x[1][j][i])
                sol.add(Not(And(e0, e1)))  # can't both use {i,j}

    # Total cost in uniform line metric: d(i,j)=abs(i-j)
    def dist(i, j):
        return abs(i - j)

    total_cost = Int("total_cost")
    sol.add(
        total_cost ==
        Sum([
            If(x[p][i][j], dist(i, j), 0)
            for p in P for i in V for j in V
        ])
    )

    # Strict inequality: total_cost < 16*(n-1)/5  <=>  5*total_cost < 16*(n-1)
    sol.add(5 * total_cost < 16 * (n - 1))

    res = sol.check()
    if res == sat:
        m = sol.model()
        print(f"n={n}: SAT (counterexample found), total_cost =", m[total_cost])

        # Optional: print the two paths as sequences by sorting vertices by u[p][v]
        for p in P:
            order = sorted(V, key=lambda v: m[u[p][v]].as_long())
            print(f" path {p} order:", order)

    else:
        print(f"n={n}: UNSAT (no such pair exists).")

    return res

for n in [6, 7, 8]:
    prove_case(n)
