class Solution
{
///*** No.201
    int rangeBitwiseAnd(int left, int right) {
#if 0
        // 如果超过两个一位在里面，则这个数字就是0
        // 如果只有一个，则结果就是它
        // 如果没有，则结果就是离left最近的那个位数
        if(left==right)return left;
        
        int count = 0;
        unsigned int num = 1;
        unsigned int firstNum = 1;
        for(int i=0;i<31;++i){
            if(num>right)
                break;
            if(num>=left&&num<=right){
                // 存在在范围内
                if(!count)
                    firstNum = num;
                count++;
                if(count>=2)
                    return 0;
            }

            num *= 2;
        }
        if(count==1){
            if(left >= firstNum)
                return firstNum;
            else
                return 0;
        }
        long long res = left;
        for(long long i=left;i<=right;++i){
            res &= i;
        }
        return res;
#else
        // 与运算只会保存两个数字相同的位数，所以我们只需要找出它们相同的部分就可以了
        int shift = 0;
        while(left!=right){
            // 往右移动可以减位，把不一样的位移出去
            // 如果他俩不相等，则必然存在left+1也就是最后一位一定不相等
            left >>= 1;
            right >>= 1;
            ++shift;
        }
        // 把不一样的移除完之后，最后结果不得把位数补齐呀
        return left << shift;
#endif
    }
};
