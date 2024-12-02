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

///*** No.208
	class Trie {
	public:
		// 以树的结构，存储单词的每一个字母

		Trie()
			: subTrie(26)
			, isEnd(false)
		{}

		void insert(string word) {
			Trie* node = this;
			for (auto it : word) {
				int index = it - 'a';
				if (node->subTrie[index] == nullptr) {
					node->subTrie[index] = new Trie();
				}
				node = node->subTrie[index];
			}
			node->isEnd = true;
		}

		bool search(string word) {
			Trie* node = findWith(word);
			return node != nullptr && node->isEnd;
		}

		bool startsWith(string prefix) {
			return findWith(prefix) != nullptr;
		}
	private:
		// 查找字符串或前缀
		Trie* findWith(const std::string& word) {
			Trie* node = this;
			for (auto it : word) {
				int index = it - 'a';
				if (node->subTrie[index] == nullptr) {
					return nullptr;
				}
				node = node->subTrie[index];
			}
			return node;
		}
	private:
		std::vector<Trie*> subTrie; // 单词字母分支节点
		bool isEnd;  // 是否是某个单词的结束
	};

	class Solution {
	public:
		void deleteNode(ListNode* node) {
			// 把他下一个节点的值，复制给他，然后把下一个节点删除
			if (node->next == nullptr)return;
			node->val = node->next->val;
			node->next = node->next->next;
		}
	};

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

///*** No.215
	int findKthLargest(vector<int>& nums, int k) {
		// 详细题解见README.md的No.215图解
		std::function<int(std::vector<int>&, int)> quickSelect = [&](std::vector<int>& nums, int k)->int {
			int index = rand() % nums.size(); // 0;
			std::vector<int> L, mid, R;
			for (int num : nums) {
				if (num > nums[index]) {
					L.push_back(num);
				}
				else if (num < nums[index]) {
					R.push_back(num);
				}
				else {
					mid.push_back(num);
				}
			}

			if (k <= L.size()) {
				return quickSelect(L, k);
			}
			if (k - L.size() <= mid.size()) {
				return mid[0];
			}
			return quickSelect(R, k - (L.size() + mid.size())); // L.size + mid.size = nums.size - R.size
		};

		return quickSelect(nums, k);
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

///*** No.221
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.size() <= 0)return 0;
		if (matrix[0].size() <= 0)return 0;
		// 等于三个方向的最小值，加上当前位置的值
		std::vector<std::vector<int>> dp;
		for (int i = 0; i < matrix.size(); ++i) {
			std::vector<int> item(matrix[0].size(), 0);
			dp.push_back(item);
		}
		int maxSide = 0;
		for (int i = 0; i < matrix.size(); ++i) {
			dp[i][0] = matrix[i][0] - '0';
			if (matrix[i][0] - '0' > maxSide)
				maxSide = matrix[i][0] - '0';
		}
		for (int i = 0; i < matrix[0].size(); ++i) {
			dp[0][i] = matrix[0][i] - '0';
			if (matrix[0][i] - '0' > maxSide)
				maxSide = matrix[0][i] - '0';
		}
		for (int i = 1; i < dp.size(); ++i) {
			for (int j = 1; j < dp[i].size(); ++j) {
				if (matrix[i][j] == '1') {
					dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) +1;
					if (dp[i][j]  > maxSide)
						maxSide = dp[i][j];
				}
			}
		}

		return maxSide * maxSide;
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

///*** No.227
	int calculate(string s) {
		//  字符串转数字
		std::function<long long(std::string, int, int)> str2ll = [&](std::string str, int begin, int end)->long long {
			long long result = 0;
			for (int i = begin; i < end; ++i) {
				if (str[i] == ' ' || (str[i] < '0' || str[i]>'9'))continue;

				result = (result * 10) + (str[i] - '0');
			}
			return result;
		};

		// 可以用栈来实现
		// 先算*/法，然后把栈中剩下的进行相加
		std::stack<long long> sta;
		long long ret = 0;
		// int begin = 0;
		char fh = ' ';
		for (int i = 0; i < s.size(); ++i) {
			if (isdigit(s[i])) {
				ret = (ret * 10) + (s[i] - '0');
			}
			// 如果当前的不是数字也不是空
			if ((!isdigit(s[i]) && s[i] != ' ') || (i == s.size() - 1)) {
				// 当前符号是作用于下一个元素的
				// ret = str2ll(s, begin, i == s.size() - 1 ? s.size() : i); // 显然这个一起算是不行的，要边走边算
				switch (fh)
				{
				case '-':
					ret *= -1;
					break;
				case '*':
					// 把栈顶元素出栈与ret计算，然后把结果放回去
					if (!sta.empty()) {
						ret *= sta.top();
						sta.pop();
					}
					break;
				case '/':
					if (!sta.empty()) {
						ret = sta.top() / ret;
						sta.pop();
					}
					break;
				// +号和' '（相当于第一个元素）,对于他作用的后边的元素没有什么影响，直接存就可以
				/*case '+':
					break;
				default:
					// 没有符号，这是第一个，那就直接存栈里面 */
				}
				sta.push(ret); // 保存到栈中
				// begin = i + 1;
				fh = s[i]; // 更新符号
				ret = 0;  // 更新值
			}
		}

		int result = 0;
		while (!sta.empty()) {
			result += sta.top();
			sta.pop();
		}
		return result;
	}

///*** No.229
	vector<int> majorityElement(vector<int>& nums) {
        // 摩尔投票的规律，
        // 如果多数大于n/2，则至多有1个多数
        // 如果多数大于n/3，则至多有2个多数
        // 如果多数大于n/m，则至多有m-1个多数

        int candidate1 = nums[0], count1 = 0;
        int candidate2 = nums[0], count2 = 0;
        std::vector<int> res;

        // 抵消算法
        for(int num : nums){
            if(num == candidate1){
                ++count1;
                continue;
            }
            if(num == candidate2){
                ++count2;
                continue;
            }

            if(count1 == 0){
                candidate1 = num;
                count1 = 1;
                continue;
            }
            if(count2 == 0){
                candidate2 = num;
                count2 = 1;
                continue;
            }
            --count1;
            --count2;
        }

        // 计数算法
        count1 = count2 = 0;
        for(int num : nums){
            if(candidate1 == num)
                ++count1;
            if(candidate2 == num)
                ++count2;
        }
        std::cout<<candidate1<<" "<<candidate2;

        if(count1 > nums.size() / 3) res.push_back(candidate1);
        if(count2 > nums.size() / 3 && candidate1 != candidate2) res.push_back(candidate2);
        return res;
    }

///*** No.230
	int kthSmallest(TreeNode* root, int k) {
        int result = 0;
        int index = 0;
        std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node){
            if (!node)return;
            if(index == k)return;
            inorderTraversal(node->left);
            if(index == k)return;
            ++index;
            result = node->val;
            inorderTraversal(node->right);
        };

		inorderTraversal(root);
		return result;
	}

///*** No.235
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		//** 这道题的本质就是找到目标元素所访问的节点，取两个访问节点列表的最后一个相同节点
		// 两个数组保存找到p和q这两个节点时，所走过的节点
		// 然后两个数组取交集
		// 交集的最后一个元素就是最近公共祖先
		std::vector<TreeNode*> findList; // 记录寻找target所访问的路径节点
		std::function<bool(TreeNode*, int)> findNode = [&](TreeNode* node, int target)->bool {
			if (!node)return false;
			findList.push_back(node);
			if (node->val < target)
				return findNode(node->right, target);
			if (node->val > target)
				return findNode(node->left, target);
			return true;
		};

		findNode(root, p->val);
		std::vector<TreeNode*> pList = findList;
		findList.clear();
		findNode(root, q->val);
		std::vector<TreeNode*> qList = findList;

		TreeNode* result = root;
		for (auto pIt : pList) {
			for (auto qIt : qList) {
				if (pIt == qIt) {
					result = pIt;
					break;
				}
			}
		}
		return result;
	}

///*** No.236
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// 就是寻找到这个目标元素的路径
		int isFind = false;
		std::vector<TreeNode*> findList;
		std::function<void(TreeNode*, TreeNode*)> findPath = [&](TreeNode* node, TreeNode* target) {
			if (isFind)return;
			if (node == nullptr)return;
			findList.push_back(node);
			if (node == target) {
				isFind = true;
				return;
			}
			if (isFind)return;
			findPath(node->left, target);
			if (isFind)return;
			findPath(node->right, target);
			if (isFind)return;
			findList.pop_back();
		};

		std::vector<TreeNode*> pList;
		std::vector<TreeNode*> qList;
		findPath(root, p);
		if (isFind) {
			isFind = false;
			pList = findList;
			findList.clear();
		}
		findPath(root, q);
		if (isFind) {
			isFind = false;
			qList = findList;
			findList.clear();
		}

		TreeNode* result = root;
		for (auto pIt : pList) {
			for (auto qIt : qList) {
				if (pIt == qIt)
					result = pIt;
			}
		}
		return result;
	}

///*** No.237
	void deleteNode(ListNode* node) {
		// 把他下一个节点的值，复制给他，然后把下一个节点删除
		if (node->next == nullptr)return;
		node->val = node->next->val;
		node->next = node->next->next;
	}
};
