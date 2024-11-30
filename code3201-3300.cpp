class Solution
{
public:
///*** No.3232
    bool canAliceWin(vector<int>& nums) {
        int geSum = 0;
        int otherSum = 0;
        for(auto it : nums){
            if(!(it/10))
                geSum += it;
            else otherSum += it;
        }
        return geSum != otherSum;
    }
};