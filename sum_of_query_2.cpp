

class Solution {
  public:
    // Function to build the segment tree
    void build(int i, int l, int r, vector<int> &sgt, int arr[]) {
        if (l == r) {
            sgt[i] = arr[l]; 
            return;
        }

        int mid = l + (r - l) / 2;
        build(2 * i + 1, l, mid, sgt, arr);
        build(2 * i + 2, mid + 1, r, sgt, arr);

        sgt[i] = sgt[2 * i + 1] + sgt[2 * i + 2];
    }

    // Function to query the segment tree in range [start, end]
    int query(int start, int end, int i, int l, int r, vector<int> &sgt) {
        // No overlap
        if (r < start || l > end) return 0;

        // Total overlap
        if (start <= l && r <= end) return sgt[i];

        // Partial overlap
        int mid = l + (r - l) / 2;
        return query(start, end, 2 * i + 1, l, mid, sgt) +
               query(start, end, 2 * i + 2, mid + 1, r, sgt);
    }

    
    vector<int> querySum(int n, int arr[], int q, int queries[]) {
        vector<int> sgt(4 * n, 0);  
        build(0, 0, n - 1, sgt, arr); 

        vector<int> ans;

        for (int i = 0; i < 2 * q; i += 2) {
            int start = queries[i] - 1;     
            int end = queries[i + 1] - 1;   

            int res = query(start, end, 0, 0, n - 1, sgt);
            ans.push_back(res);
        }

        return ans;
    }
};
