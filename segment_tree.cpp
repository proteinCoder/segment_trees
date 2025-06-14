#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            // Leaf node
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            // Build left and right children
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            // Internal node: sum of children
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            // Outside the range
            return 0;
        }
        if (l <= start && end <= r) {
            // Completely inside the range
            return tree[node];
        }
        // Partially inside and outside
        int mid = (start + end) / 2;
        int left_sum = query(2 * node, start, mid, l, r);
        int right_sum = query(2 * node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            // Leaf node
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    int rangeSum(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void pointUpdate(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Sum of values in range [1, 3]: " << st.rangeSum(1, 3) << endl; // Output: 15
    st.pointUpdate(1, 10);  // arr[1] = 10
    cout << "After update, sum of values in range [1, 3]: " << st.rangeSum(1, 3) << endl; // Output: 22

    return 0;
}
