
void build(int i, int l, int r, int sgt[], int arr[]){
    
    if(l==r) {
        sgt[i]=arr[l];
        return;
    }
    
    int mid = l + (r-l)/2;
    build(2*i+1, l,mid,sgt,arr);
    build(2*i+2, mid+1, r,sgt,arr);
    
    sgt[i] = min(sgt[2*i+1],sgt[2*i+2]);
}

int *constructST(int arr[], int n) {
    int *sgt = new int[4*n];
    build(0,0,n-1,sgt,arr);
    return sgt;
}

int query(int a, int b, int i ,int l ,int r, int st[]){
    if(l>b || r<a) return 1e9;
    if(l>=a && r<=b) return st[i];
    
    int mid = l + (r-l)/2;
    
    return min(query(a,b,2*i+1,l,mid,st),query(a,b,2*i+2, mid+1,r,st));
}

int RMQ(int st[], int n, int a, int b) {
    return query(a,b,0,0,n-1,st);
}
