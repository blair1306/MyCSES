#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * A data structure that can answer point updates and range minimum queries.
 *
 * Implementation notes / invariants:
 * - Uses a classic binary segment tree stored in a flat array (1-based tree index).
 * - External API uses 0-based indices for the input array / queries.
 * - segtree vector is sized to 4 * len to safely contain the tree for any len.
 * - combine() must be associative and commutative for correctness of this usage;
 *   here it is min().
 * - Precondition: len > 0 when building from an array or querying (no empty-array checks).
 * - Time complexity: build O(n), point update O(log n), range query O(log n) on average
 *   (worst-case O(log n) nodes visited).
 */
template <class T>
class MinSegmentTree {
private:
  // Identity element for min; returned for segments outside the query range.
  const T DEFAULT = std::numeric_limits<T>().max();

  int len;            // number of elements in the original array
  vector<T> segtree;  // flat storage for segment tree; index 0 unused (1-based)

  // Combine two child results to produce parent result. For min segment tree this is min.
  T combine(const T& a, const T& b)
  {
    return std::min(a, b);
  }

  // Recursively build the tree from arr into segtree at node `at` which covers [at_left,
  // at_right]. Complexity: visits each node once -> O(n).
  void build(const vector<T>& arr, int at, int at_left, int at_right)
  {
    if (at_left == at_right) {
      // Leaf node corresponds to a single array element.
      segtree[at] = arr[at_left];
      return;
    }
    int mid = (at_left + at_right) / 2;
    build(arr, 2 * at, at_left, mid);           // build left child
    build(arr, 2 * at + 1, mid + 1, at_right);  // build right child
    // parent = min(left, right)
    segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
  }

  // Internal recursive point update: set index `ind` to `val`.
  // `at` covers [at_left, at_right]. After updating child, recompute current node.
  // Complexity: O(log n) depth.
  void set(int ind, T val, int at, int at_left, int at_right)
  {
    if (at_left == at_right) {
      segtree[at] = val;
      return;
    }
    int mid = (at_left + at_right) / 2;
    if (ind <= mid) {
      set(ind, val, 2 * at, at_left, mid);
    } else {
      set(ind, val, 2 * at + 1, mid + 1, at_right);
    }
    segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
  }

  // Internal recursive range minimum query on [start, end] intersected with current node
  // [at_left, at_right]. Returns DEFAULT for disjoint segments so combine() preserves the other
  // side's value. Complexity: O(log n) amortized (visits at most ~4*log n nodes).
  T range_min(int start, int end, int at, int at_left, int at_right)
  {
    // No overlap
    if (at_right < start || end < at_left) {
      return DEFAULT;
    }
    // Fully covered
    if (start <= at_left && at_right <= end) {
      return segtree[at];
    }
    // Partial overlap -> query both children
    int mid = (at_left + at_right) / 2;
    T left_res = range_min(start, end, 2 * at, at_left, mid);
    T right_res = range_min(start, end, 2 * at + 1, mid + 1, at_right);
    return combine(left_res, right_res);
  }

public:
  // Construct empty tree with given length (all values initialized to DEFAULT).
  MinSegmentTree(int len) : len(len)
  {
    segtree = vector<T>(len * 4, DEFAULT);
  };

  // Construct tree from an initial array (build in O(n)).
  MinSegmentTree(const vector<T>& arr) : len(arr.size())
  {
    segtree = vector<T>(len * 4, DEFAULT);
    build(arr, 1, 0, len - 1);
  }

  /** Sets the value at ind (0-based) to val. Caller must ensure 0 <= ind < len. */
  void set(int ind, T val)
  {
    set(ind, val, 1, 0, len - 1);
  }

  /** @return the minimum element in the range [start, end] (0-based, inclusive). */
  T range_min(int start, int end)
  {
    return range_min(start, end, 1, 0, len - 1);
  }
};

int main()
{
  int arr_len;
  int query_num;
  std::cin >> arr_len >> query_num;
  vector<long long> arr(arr_len);
  for (long long& i : arr) {
    std::cin >> i;
  }

  MinSegmentTree<long long> segtree(arr);
  for (int q = 0; q < query_num; q++) {
    int type;
    std::cin >> type;
    if (type == 1) {
      int ind, val;
      std::cin >> ind >> val;
      // input is 1-based; internal structure is 0-based
      segtree.set(ind - 1, val);
    } else if (type == 2) {
      int start, end;
      std::cin >> start >> end;
      // convert to 0-based and print result
      cout << segtree.range_min(start - 1, end - 1) << '\n';
    }
  }
}