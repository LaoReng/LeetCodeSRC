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

///*** No.207
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		// 拓扑排序，选择入度为0的，为第一个可以学习的课
		// 然后将以这科为入度的结点减一，循环执行上面步骤，直到没有入度大于0的为止
		std::map<int, int> mCou;

		for (int i = 0; i < numCourses; ++i) {
			mCou.insert(std::make_pair(i, 0));
		}

		for (auto it : prerequisites) {
			mCou[it[0]]++;
		}

		bool running = false;
		do {
			running = false;
			// 找到second为0的
			auto it = mCou.begin();
			for (; it != mCou.end(); ++it) {
				if (it->second == 0)
					break;
			}
			if (it != mCou.end()) {
				running = true;
				// 把这个是0的，从map中移除
				int zero = it->first;
				mCou.erase(it);

				for (auto vIt = prerequisites.begin(); vIt != prerequisites.end(); ) {
					if ((*vIt)[1] == zero) {
						
						mCou[(*vIt)[0]]--;
						prerequisites.erase(vIt);
						vIt = prerequisites.begin();
					}
					else {
						vIt++;
					}
				}
			}
		} while (!mCou.empty() && running);

		if (mCou.empty())return true;

		return false;
	}
};
