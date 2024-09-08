class Solution
{
public:
///*** No.977
    vector<int> sortedSquares(vector<int> &nums)
    {
        std::vector<int> res;
        // 因为有负数的原因，所以平方之后可能后面的比前面的还要大
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r)
        {
            int ltemp = nums[l] < 0 ? nums[l] * (-1) : nums[l];
            int rtemp = nums[r] < 0 ? nums[r] * (-1) : nums[r];
            if (ltemp < rtemp)
            {
                res.insert(res.begin(), rtemp * rtemp);
                --r;
            }
            else
            {
                res.insert(res.begin(), ltemp * ltemp);
                ++l;
            }
        }
        return res;
    }
};