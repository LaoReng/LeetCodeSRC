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

///*** No.209
	int minSubArrayLen(int target, vector<int>& nums) {
		// 前缀和
		std::vector<int> qSum(nums.size());
		qSum[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			qSum[i] = nums[i] + qSum[i - 1];
		}

		int min = 0;
		int index = 0;
		for (int i = 0; i < qSum.size(); ++i) {
			if (qSum[i] >= target) {
				min = i + 1;
				index = i;
				break;
			}
		}
		if (!min)return min;

		for (int i = index; i < qSum.size(); ++i) {
			// 从这个位置往回减，如果减到大于最小值了，就直接丢弃
			int count = 0;
			for (int j = i - 1; j >= 0; --j) {
				++count;
				if (qSum[i] - qSum[j] >= target) {
					// 就可以把count和min取最小值
					if (min > count)
						min = count;
				}
				if (count > min)
					break;
			}
		}
		return min;
	}

///*** No.210
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		// 拓扑排序，与No.207类似
		std::map<int, int> mPre;
		std::vector<int> res;  // 最终上课的顺序
		for (int i = 0; i < numCourses; ++i) {
			mPre.insert(std::make_pair(i, 0));
		}

		for (auto it : prerequisites) {
			mPre[it[0]]++;
		}
		// 不仅map不为空，还要进去运行了，不要死循环空转
		bool isRunning = true;
		while (!mPre.empty() && isRunning) {
			isRunning = false;
			// 找到0入度的课程
			auto  mIt = mPre.begin();
			for (; mIt != mPre.end(); mIt++) {
				if (!mIt->second)break;
			}
			if (mIt == mPre.end())continue;
			isRunning = true;
			// 把mIt从map中移除
			int XXClass = mIt->first; // 先行课
			mPre.erase(mIt);

			res.push_back(XXClass);

			for (auto vIt = prerequisites.begin(); vIt != prerequisites.end(); ) {
				if ((*vIt)[1] == XXClass) {
					mPre[(*vIt)[0]]--;
					prerequisites.erase(vIt);
					vIt = prerequisites.begin();
				}
				else {
					vIt++;
				}
			}
		}

		if (!mPre.empty())
			res.clear();
		return res;
	}

///*** No.213
	int rob(vector<int>& nums) {
        // 第一和最后一家不能同时偷
		// 舍弃第一家求最大值
		// 舍弃最后一家求最大值
		if (nums.size() < 3) {
			return *std::max_element(nums.begin(), nums.end());
		}
		std::function<int(std::vector<int>)> maxRob = [&](std::vector<int> nums) {
			for (int i = 2; i < nums.size(); ++i) {
				nums[i] += *std::max_element(nums.begin(), nums.begin() + i - 1);
			}
			return *std::max_element(nums.begin(), nums.end());
		};

		return std::max(
			maxRob(std::vector<int>(nums.begin() + 1, nums.end())),
			maxRob(std::vector<int>(nums.begin(), nums.begin() + nums.size() - 1))
		);
	}

///*** No.216
	vector<vector<int>> combinationSum3(int k, int n) {
		std::vector<int> item;
		std::vector<std::vector<int>> res;

		std::function<void(int, int, int)> dfs = [&](int sum, int currentK, int currentValue) {
			if (sum >= n || currentK >= k) {
				if (sum == n && item.size() == k) {
					res.push_back(item);
				}
				return;
			}
			for (int i = currentValue + 1; i <= 9; ++i) {
				item.push_back(i);
				dfs(sum + i, currentK + 1, i);
				item.pop_back();
			}
		};

		for (int i = 1; i <= 9; ++i) {
			if (i <= n) {
				item.push_back(i);
				dfs(i, 1, i);
				item.pop_back();
			}
		}
		return res;
	}

///*** No.223
	int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
		// 点数据结果判断属于那个矩形
		class Point {
		public:
			Point() = default;
			Point(int val, int recName)
				: value(val)
				, rectangleName(recName)
			{}
			bool operator()(const Point& point1, const Point& point2) {
				return point1.value < point2.value;
			}
			int  value;
			int rectangleName;
		};

		// 总面积等于两个矩形面积减去相交的矩形面积
		int intersectArea = 0;
		do {
			// 如果不是一个矩形的两个顶点挨在一起排序，则它们就有相交的线段
			// 长和宽都是这么判断，当长和宽都有焦点则矩形成立，否则面积为0
			std::vector<Point> X = { {ax1,1}, {ax2,1},{bx1, 2},{bx2, 2} };
			std::vector<Point> Y = { {ay1, 1}, {ay2, 1},{by1, 2},{by2, 2} };
			std::sort(X.begin(), X.end(), Point());
			if (X[0].rectangleName == X[1].rectangleName)
				break;
			std::sort(Y.begin(), Y.end(), Point());
			if (Y[0].rectangleName == Y[1].rectangleName)
				break;
			intersectArea = (Y[2].value - Y[1].value) * (X[2].value - X[1].value);
		} while (false);
		return ((ax2 - ax1) * (ay2 - ay1)) + ((bx2 - bx1) * (by2 - by1)) - intersectArea;
	}
};
