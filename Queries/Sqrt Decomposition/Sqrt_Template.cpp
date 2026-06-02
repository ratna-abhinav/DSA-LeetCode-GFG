#include <bits/stdc++.h>
using namespace std;

int n;

vector<long long> arr;
vector<long long> blockSum;
vector<long long> lazy;
vector<bool> hasLazy;

int blockSize = sqrt(n) + 1;
int blockCnt = (n + blockSize - 1) / blockSize;

// helper functions
auto getBlockId = [&](int index) { return index / blockSize; };
auto getLeft = [&](int blockId) { return blockId * blockSize; };
auto getRight = [&](int blockId) { return min(n - 1, (blockId + 1) * blockSize - 1); };

auto push = [&](int blockId) {
    // apply lazyValue to all elements of this block
    if (!hasLazy[blockId]) return;
    for (int i=getLeft(blockId); i<=getRight(blockId); i++) arr[i] = lazy[blockId];
    hasLazy[blockId] = 0;
};

auto reCalc = [&](int blockId) {
    blockSum[blockId] = 0;
    for (int i=getLeft(blockId); i<=getRight(blockId); i++) blockSum[blockId] += arr[i];
};

auto setBlockVals = [&](int blockId, int value) {
    hasLazy[blockId] = true;
    lazy[blockId] = value;
    blockSum[blockId] = 1LL * (getRight(blockId) - getLeft(blockId) + 1) * value;
};

signed main()
{
    int n; cin >> n;
    arr.resize(n);
    for (int i=0; i<n; i++) cin >> arr[i];
    
    blockSum.resize(blockCnt, 0);
    lazy.resize(blockCnt, 0);
    hasLazy.resize(blockCnt, false);

    // init blockSum
    for (int i=0; i<n; i++) blockSum[getBlockId(i)] += arr[i];


    // UPDATE: set a[l..r] = x
    // 1) find bl = getBlockId(l), br = getBlockId(r)
    // 2) if same block:
    //      push(bl)
    //      modify a[l..r]
    //      reCalc(bl)
    // 3) else:
    //      push(bl)
    //      modify a[l..R(bl)]
    //      reCalc(bl)
    //
    //      for every full block between bl+1 and br-1:
    //          setBlock(b, x)
    //
    //      push(br)
    //      modify a[L(br)..r]
    //      reCalc(br)


    // QUERY: sum a[l..r]
    // 1) find bl = getBlockId(l), br = getBlockId(r)
    // 2) if same block:
    //      push(bl)
    //      sum a[l..r] directly
    // 3) else:
    //      push(bl)
    //      sum a[l..R(bl)] directly
    //
    //      add blockSum for all full middle blocks
    //
    //      push(br)
    //      sum a[L(br)..r] directly
}