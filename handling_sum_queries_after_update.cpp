class Solution {
public:
    typedef long long ll;

    void build(int i, int segStart, int segEnd, vector<int>& nums1,
               vector<int>& seg) {
        if (segStart == segEnd) {
            seg[i] = nums1[segStart];
            return;
        }

        int mid = segStart + (segEnd - segStart) / 2;

        build(2 * i + 1, segStart, mid, nums1, seg);
        build(2 * i + 2, mid + 1, segEnd, nums1, seg);

        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    void push(int i, int segStart, int segEnd, vector<int>& seg,
              vector<int>& lazy) {
        if (lazy[i]) {
            seg[i] = (segEnd - segStart + 1) - seg[i];
            if (segStart != segEnd) {
                lazy[2 * i + 1] = !lazy[2 * i + 1];
                lazy[2 * i + 2] = !lazy[2 * i + 2];
            }
            lazy[i] = 0;
        }
    }

    void update(int i, int segStart, int segEnd, int& l, int& r,
                vector<int>& seg, vector<int>& lazy) {
        push(i, segStart, segEnd, seg, lazy);

        if (r < segStart || segEnd < l)
            return; // no overlap

        if (l <= segStart && segEnd <= r) {
            lazy[i] = !lazy[i];
            push(i, segStart, segEnd, seg, lazy);
            return;
        }

        int mid = segStart + (segEnd - segStart) / 2;
        update(2 * i + 1, segStart, mid, l, r, seg, lazy);
        update(2 * i + 2, mid + 1, segEnd, l, r, seg, lazy);

        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2,
                                  vector<vector<int>>& queries) {
        int n = nums1.size();
        vector<int> seg(4 * n), lazy(4 * n, 0);

        ll sum = accumulate(nums2.begin(), nums2.end(), 0LL);

        int i = 0; // segment tree index
        build(i, 0, n - 1, nums1, seg);

        // performing queries
        vector<ll> res;
        for (auto& q : queries) {

            if (q[0] == 1) {
                int l = q[1], r = q[2];
                update(0, 0, n - 1, l, r, seg, lazy);
            } else if (q[0] == 2) {
                int p = q[1];
                sum += (ll)seg[0] * q[1];
            } else {
                res.push_back(sum);
            }
        }
        return res;
    }
};
