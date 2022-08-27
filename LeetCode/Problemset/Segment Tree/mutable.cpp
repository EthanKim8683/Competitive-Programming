using I = int;

const I N = 3e4;

class NumArray {
public:
  I segs[2 * N];
  I n;

  NumArray(vector<I>& nums) {
    n = nums.size();
    for (I i = 0; i < n; i++)
      asn(i, nums[i]);
    bld();
  }
  
  void asn(I i, I val) {
    segs[i + n] = val;
  }

  void bld() {
    for (I i = n - 1; i >= 0; i--)
      segs[i] = segs[i << 1] + segs[i << 1 | 1];
  }
  
  void update(I index, I val) {
    for (segs[index += n] = val; index > 1; index >>= 1)
      segs[index >> 1] = segs[index] + segs[index ^ 1];
  }
  
  I sumRange(I left, I right) {
    right++;
    I res = 0;
    for (left += n, right += n; left < right; left >>= 1, right >>= 1) {
      if (left & 1)
        res += segs[left++];
      if (right & 1)
        res += segs[--right];
    }
    return res;
  }
};