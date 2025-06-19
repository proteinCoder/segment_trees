#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
long long seg[4 * MAXN];
long long lazy[4 * MAXN];

// Build the segment tree
void build(vector<int>& arr, int node, int segStart, int segEnd) {
    if (segStart == segEnd) {
        seg[node] = arr[segStart];
    } else {
        int mid = (segStart + segEnd) / 2;
        build(arr, 2 * node, segStart, mid);
        build(arr, 2 * node + 1, mid + 1, segEnd);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
}

// Push any pending lazy updates
void push(int node, int segStart, int segEnd) {
    if (lazy[node] != 0) {
        seg[node] += (segEnd - segStart + 1) * lazy[node];
        if (segStart != segEnd) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// Internal update function: adds `val` to range [l, r]
void update(int node, int segStart, int segEnd, int l, int r, long long val) {
    push(node, segStart, segEnd);

    if (r < segStart || segEnd < l)
        return;

    if (l <= segStart && segEnd <= r) {
        lazy[node] += val;
        push(node, segStart, segEnd);
        return;
    }

    int mid = (segStart + segEnd) / 2;
    update(2 * node, segStart, mid, l, r, val);
    update(2 * node + 1, mid + 1, segEnd, l, r, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}

// Internal query function: returns sum over [l, r]
long long query(int node, int segStart, int segEnd, int l, int r) {
    push(node, segStart, segEnd);

    if (r < segStart || segEnd < l)
        return 0;

    if (l <= segStart && segEnd <= r)
        return seg[node];

    int mid = (segStart + segEnd) / 2;
    long long leftSum = query(2 * node, segStart, mid, l, r);
    long long rightSum = query(2 * node + 1, mid + 1, segEnd, l, r);
    return leftSum + rightSum;
}

// Public wrappers for ease of use
void updateRange(int l, int r, long long val, int n) {
    update(1, 0, n - 1, l, r, val);
}

long long queryRange(int l, int r, int n) {
    return query(1, 0, n - 1, l, r);
}

void buildTree(vector<int>& arr) {
    build(arr, 1, 0, arr.size() - 1);
}
