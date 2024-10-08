class Solution {
public:
///*** No.102
	vector<vector<int>> levelOrder(TreeNode* root) {
        // 广度优先搜索，学习博客https://blog.csdn.net/weixin_43955293/article/details/126445861
		std::vector<std::vector<int>> res;
		if (root == NULL) {
			return res;
		}
		std::list<TreeNode*> NodeList = {root};
		do {
			std::vector<int> item;
			int size = NodeList.size();
			for (int i = 0; i < size; ++i) {
				TreeNode* temp = NodeList.front();
				NodeList.pop_front();
                if(temp == NULL)
                    continue;
				item.push_back(temp->val);
				if (temp->left != NULL)
					NodeList.push_back(temp->left);
				if (temp->right != NULL)
					NodeList.push_back(temp->right);
			}
			res.push_back(item);
		} while (NodeList.size() > 0);
		return res;
	}

///*** No.103
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		// 二叉树的层次遍历用队列来实现（广度优先搜索）
		std::vector<std::vector<int>> res;
		if (root == NULL)return res;
		std::list<TreeNode*>  NodeList = { root };

		int direction = 1;  // true:正向（左→右） false:逆向（右→左）
		do {
			int size = NodeList.size();
			std::vector<int> item;
			for (int i = 0; i < size; i++) {
				TreeNode* temp = NodeList.front();
				NodeList.pop_front();
				if (temp == NULL)continue;
				if (direction == 1) {
					item.push_back(temp->val);
				}
				else {
					item.insert(item.begin(), temp->val);
				}
				if (temp->left)
					NodeList.push_back(temp->left);
				if (temp->right)
					NodeList.push_back(temp->right);
			}
			direction *= -1;
			res.push_back(item);
		} while (!NodeList.empty());
		return res;
	}

///*** No.105
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		std::function<TreeNode* (int, int, int, int)> CreateTree =
			[&](int preorderBegin, int preorderEnd, int inorderBegin, int inorderEnd)->TreeNode* {
			if (preorderBegin > preorderEnd || inorderBegin > inorderEnd)
				return nullptr;
			if (preorderEnd - preorderBegin != inorderEnd - inorderBegin) {
				// 个数不同
				printf("E:前序和中序虚列的元素个数不同\n");
				return nullptr;
			}

			// 前序遍历的第一个节点是根节点
			int rootValue = preorder[preorderBegin];
			TreeNode* root = new TreeNode(rootValue, nullptr, nullptr);

			// 只有一个节点的判断
			if (preorderBegin == preorderEnd) {
				if (inorderBegin == inorderEnd && preorder[preorderBegin] == inorder[inorderBegin])
					return root;
				else
                    assert(false);
			}

			// 第二步：在中序遍历中找rootValue的位置，前面的既是这个root的左子树，后面的则是这个root的右子树
			int rootValueIndex = inorderBegin;
			while (rootValueIndex <= inorderEnd && rootValue != inorder[rootValueIndex])
				++rootValueIndex;

			if (rootValueIndex == inorderEnd && rootValue != inorder[rootValueIndex]) {
				// 断言或者异常
				assert(false);
			}
			int len = rootValueIndex - inorderBegin;
			if (len > 0) {
				// 有左子树
				root->left = CreateTree(preorderBegin + 1, preorderBegin + len,
					inorderBegin, rootValueIndex - 1);
			}
			if (len < inorderEnd - inorderBegin) {
				// 有右子树，因为len的长度不是数组的全部
				root->right = CreateTree(preorderBegin + len + 1, preorderEnd,
					rootValueIndex + 1, inorderEnd);
			}
			return root;
		};

		int preorderSize = preorder.size();
		int inorderSize = inorder.size();
		if (preorderSize != inorderSize) {
			printf("E:前序和中序虚列的元素个数不同\n");
			return nullptr;
		}
		return CreateTree(0, preorderSize - 1, 0, inorderSize - 1);
	}

///*** No.106
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		// 二叉树构造API（递归）
		std::function<TreeNode* (int, int, int, int)> CreateTree =
			[&](int inorderBegin, int inorderEnd, int postorderBegin, int postorderEnd)->TreeNode* {
			// 后序遍历数组的最后一个元素是根节点
			int rootValue = postorder[postorderEnd];
			TreeNode* root = new TreeNode(rootValue, nullptr, nullptr);

			if (inorderBegin == inorderEnd) {
				// 只有一个元素了
				if (postorderBegin == postorderEnd && inorder[inorderBegin] == postorder[postorderBegin]) {
					return root;
				}
				else {
					assert(false);
					// throw std::exception("Invalid value");
				}
			}

			int rootInorderIndex = inorderBegin;
			while (rootInorderIndex <= inorderEnd && inorder[rootInorderIndex] != rootValue) {
				++rootInorderIndex;
			}
			if (rootInorderIndex == inorderEnd && rootValue != inorder[inorderEnd]) {
				assert(false);
				// throw std::exception("Invalid value");
			}


			int leftLen = rootInorderIndex - inorderBegin;
			if (leftLen > 0) {
				// 有左子树
				root->left = CreateTree(inorderBegin, rootInorderIndex - 1,
					postorderBegin, postorderBegin + leftLen - 1);
			}
			if (leftLen < inorderEnd - inorderBegin) {
				// 因为不是全部，所以有右子树
				root->right = CreateTree(rootInorderIndex + 1, inorderEnd,
					postorderBegin + leftLen, postorderEnd - 1);
			}
			return root;
		};

		int inorderSize = inorder.size();
		int postorderSize = postorder.size();
		if (inorderSize != postorderSize)
			return nullptr;
		return CreateTree(0, inorderSize - 1, 0, postorderSize - 1);
	}

///*** No.107
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res;
		if (root == NULL)return res;
		std::vector<std::vector<TreeNode*>> nodeList = { {root} };
		bool isValue = false;
		int index = 0;
		do {
			std::vector<TreeNode*> item;
			isValue = false;
			for (int i = 0; i < nodeList[index].size(); ++i) {
				if (nodeList[index][i]->left != NULL) {
					item.push_back(nodeList[index][i]->left);
					isValue = true;
				}
				if (nodeList[index][i]->right != NULL) {
					item.push_back(nodeList[index][i]->right);
					isValue = true;
				}
			}
            if(isValue)
                nodeList.push_back(item);
			++index;
		} while (isValue);
		for (int i = nodeList.size() - 1; i >= 0; --i) {
			vector<int> item;
			for (int j = 0; j < nodeList[i].size(); ++j) {
				item.push_back(nodeList[i][j]->val);
			}
			res.push_back(item);
		}
		return res;
	}

///*** No.113
	vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		std::vector<std::vector<int>> res;
		std::vector<int> nodeLists;

		std::function<void(TreeNode*, int, int)> dfs =
			[&](TreeNode* node, int targetSum, int  currentSum) {
			if (node == nullptr)return;
			// if(currentSum > targetSum)return;  这个判断为什么不能用，如果都是正数可以用否则不可以
			currentSum += node->val;
			nodeLists.push_back(node->val);
			// 一定要走到叶子节点，有可能出现虽然两个值相等但是不是叶子节点\
	        ，然后下面的数字可以当走到叶子节点时再次让其相等
			if (node->left == nullptr && node->right == nullptr) {
				// 这两个相等了，那就判断node是否是叶子节点
				if (currentSum == targetSum) {
					res.push_back(nodeLists);
				}
			}
			else {
				dfs(node->left, targetSum, currentSum);
				dfs(node->right, targetSum, currentSum);
			}
			nodeLists.pop_back();
			currentSum -= node->val;
		};

		if (root == nullptr)return res;
		dfs(root, targetSum, 0);
		return res;
	}

///*** No.114
	void flatten(TreeNode* root) {
		if (root == NULL)return;
		std::stack<TreeNode*> treeS;
		std::function<void(TreeNode*)> preorderTraversal = [&](TreeNode* node) {
			if (node == NULL)return;
			treeS.push(node);
			preorderTraversal(node->left);
			preorderTraversal(node->right);
		};

		// 使用栈来实现
		// 先序遍历，将每一个节点都放入栈中
		preorderTraversal(root);

		TreeNode* tempNode = NULL;
		while (!treeS.empty()) {
			TreeNode* rootNode = treeS.top();
			treeS.pop();
			rootNode->left = NULL;
			rootNode->right = tempNode;
			tempNode = rootNode;
		}
	}

///*** No.116
	Node* connect(Node* root) {
		if (root == NULL)return root;
		// 用队列进行广度优先遍历
        // 然后将本次节点指向下一个节点，最后一个指向空
		std::queue<Node*> nodeQ;
		nodeQ.push(root);

		while (!nodeQ.empty()) {
			int qSize = nodeQ.size();
			for (int i = 0; i < qSize; ++i) {
				Node* temp = nodeQ.front();
				if (temp->left) {
					nodeQ.push(temp->left);
				}
				if (temp->right) {
					nodeQ.push(temp->right);
				}
				nodeQ.pop();
				if (i == qSize - 1) {
					temp->next = NULL;
				}
				else {
					temp->next = nodeQ.front();
				}
			}
		}
		return root;
	}

///*** No.117
	Node* connect(Node* root) {
		if (root == NULL)return root;
		// 用队列来实现
		std::queue<Node*> nodeQ;
		nodeQ.push(root);

		while (!nodeQ.empty()) {
			int nodeSize = nodeQ.size();
			for (int i = 0; i < nodeSize; ++i) {
				Node* temp = nodeQ.front();
				nodeQ.pop();
				if (i == nodeSize - 1) {
					temp->next = NULL;
				}
				else {
					temp->next = nodeQ.front();
				}

				if (temp->left)
					nodeQ.push(temp->left);
				if (temp->right)
					nodeQ.push(temp->right);

			}
		}
		return root;
	}

///*** No.120
	int minimumTotal(vector<vector<int>>& triangle) {
		// 动态规划，让每一步的结果都是最小的，然后在底部找出最小值
		// 根据题意，那么当前位置的值就是 dps[i][j] += min(dps[i-1][j](值存在),dps[i-1][j-1](值存在)); 
		std::vector<std::vector<int>> dps = { {triangle[0][0]} };
		for (int i = 1; i < triangle.size(); ++i) {
			std::vector<int> temp = triangle[i];
			for (int j = 0; j < triangle[i].size(); ++j) {
				int min = 0;
				if (j < dps[i - 1].size()) {
					min = dps[i - 1][j];
					if (j - 1 >= 0 && j - 1 < dps[i - 1].size()) {
						min = min < dps[i - 1][j - 1] ? min : dps[i - 1][j - 1];
					}
				}
				else if (j - 1 >= 0 && j - 1 < dps[i - 1].size()) {
					min = dps[i - 1][j - 1];
				}
				temp[j] += min;
			}
			dps.push_back(temp);
		}

		return  *std::min_element(dps[triangle.size() - 1].begin(), dps[triangle.size() - 1].end());
	}

///*** No.122
	int maxProfit(vector<int>& prices) {
        // 当天的利润tmp = prices[i] - prices[i-1]
        // 如果利润大于0，就将tmp加入总利润中；  小于等于0，就什么都不做
        int tmp,res = 0;
        for(int i=1;i<prices.size();++i){
            tmp = prices[i] - prices[i-1];
            if(tmp>0)
                res += tmp;
        }
        return res;
    }

///*** No.126
    int fib(int n) {
			if (n <= 0)return 0;
			if (n == 1 || n == 2)
				return 1;
			int n1, n2, temp;
			n1 = n2 = 1;
			for (int i = 3; i <= n; i++) {
				temp = (n1 + n2)%1000000007;
				n1 = n2;
				n2 = temp;
			}
			return temp;
    }

///*** No.128
	int longestConsecutive(vector<int>& nums) {
		// 先用set集合去重
		// 然后访问数组中的每一个数nums[i]，如果nums[i+1]在这个集合里面就接着找并将计数+1
		// 当不在时，将其长度的计数与当前计数比较，取得最大值
		std::set<int> numsS;
		for (int i = 0; i < nums.size(); ++i) {
			numsS.insert(nums[i]);
		}

		int res = 0;
		for (auto it = numsS.begin(); it != numsS.end(); ++it) {
			
			int temp = *it;
			// 如果temp-1存在就不用看了，因为已经找过了
			if (numsS.count(temp - 1))continue;
			int tempLen = 1;
			while (numsS.count(temp + 1)) {
				// temp+1的个数大于0
				++temp;
				// numsS.erase(temp);
				++tempLen;
			}
			if (tempLen > res)
				res = tempLen;
		}
		return res;
	}

///*** No.129
	int sumNumbers(TreeNode* root) {
		int res = 0;
		std::function<void(TreeNode*, TreeNode*, int)> dfs = [&](TreeNode* root, TreeNode* node, int val){
			if (node == NULL){
				// 这个值就需要加入到结果中
				if (root->left == NULL&&root->right == NULL){
					res += val;
					std::cout << val << " ";
				}
				return;
			}
			dfs(node, node->left, val * 10 + node->val);
			if ((node->left == NULL) && (node->right == NULL)) // 防止多次重复值
				return;
			dfs(node, node->right, val * 10 + node->val);
		};

		if (root == NULL)
			return 0;
		// 递归遍历
		dfs(root, root, 0);
		return res;
	}

///*** No.130
	void solve(vector<vector<char>>& board) {
		// 可以反过来想，我们首先找到不可被围绕的区域，将其标记一下
		// 剩下的不就是可以被围绕的吗

		std::vector<std::vector<char>> temp = board; // 用于寻找不能围绕的区域

		std::function<void(int, int)> changeBoard = [&](int rowIndex, int columnIndex) {
			if (rowIndex < 0 || rowIndex >= board.size() ||
				columnIndex < 0 || columnIndex >= board[0].size())
				return;

			if (temp[rowIndex][columnIndex] == 'O') {
				temp[rowIndex][columnIndex] = 'X'; // 把找过的变成X防止重复寻找
				board[rowIndex][columnIndex] = 'O';
				// 并访问它的上下左右
				changeBoard(rowIndex, columnIndex + 1);
				changeBoard(rowIndex, columnIndex - 1);
				changeBoard(rowIndex + 1, columnIndex);
				changeBoard(rowIndex - 1, columnIndex);
			}
		};

		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				board[i][j] = 'X';
			}
		}

		// 找4个边界，看有没有'0'
		// 上边界&下边界
		for (int i = 0; i < board[0].size(); ++i) {
			if (temp[0][i] == 'O') {
				// 有'0'就找他们的上下左右
				changeBoard(0, i);
			}
			if (temp[board.size() - 1][i] == 'O') {
				changeBoard(board.size() - 1, i);
			}
		}
		// 左边界&右边界
		for (int i = 0; i < board.size(); ++i) {
			if (temp[i][0] == 'O') {
				changeBoard(i, 0);
			}
			if (temp[i][board[0].size() - 1] == 'O') {
				changeBoard(i, board[0].size() - 1);
			}
		}
	}

///*** No.131
	vector<vector<string>> partition(string s) {
#define DEBUG_OUTPUT 0
		// 回溯，
		// 起始是： 1个 2个 3个 ...
		// 那第一个举例： 如果1个是回文字符串，然后接着往后找一个、二个、三个...直到字符串末尾为止
		// 如果不是就直接返回

		std::vector<std::vector<std::string>> res;
		std::vector<std::string> item;

		// 判断回文串
		std::function<bool(std::string)> isPalindromeString = [&](std::string s)->bool{
			int l = 0, r = s.size() - 1;
			while (l < r){
				if (s[l] != s[r])
					return false;
				++l;
				--r;
			}
			return true;
		};

		std::function<void(int, int)> dfs = [&](int begin, int len){
			if (begin >= s.size() || begin + len > s.size())
				return;

			std::string temp(s.begin() + begin, s.begin() + begin + len);
#if DEBUG_OUTPUT
			printf("begin:%d, len:%d ", begin, len);
			std::cout << "temp:" << temp.c_str() << std::endl;
#endif
			if (isPalindromeString(temp)){
				// 这个是回文串
				item.push_back(temp);
#if DEBUG_OUTPUT
				printf("begin=%d,len=%d,size=%d\n", begin, len, s.size());
				for (auto it : item){
					std::cout << it.c_str() << " ";
				}
				std::cout << "\n\n";
#endif
				if (s.begin() + begin + len == s.end()){
					// 可以放入结果集中了
					res.push_back(item);
				}
				else{
					// 接着找
					for (int i = 1; i <= s.size() - (begin + len); ++i){
						dfs(begin + len, i);
					}
				}
				item.pop_back();
			}
		};

		for (int i = 1; i <= s.size(); ++i){
			dfs(0, i);
		}
		return res;
	}

///*** No.134
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		// 题解：https://leetcode.cn/problems/gas-station/solutions/488622/134-jia-you-zhan-tan-xin-jing-dian-ti-mu-xiang-jie/
		int size = gas.size();
        int cunOil = 0;  // 当前位置油箱中的剩油
		int startIndex = 0;  // 起始位置
		int  sum = 0; // 总消耗的油
		for (int i = 0; i < size; ++i) {
			int temp = gas[i] - cost[i];
			sum += temp;
			cunOil += temp;
			if (cunOil < 0) {
				// 证明从0到i，这个区间补油是大于用油的
				// 那么将起点切换到i+1位置，cunOil置0，继续寻找i的位置
				startIndex = i + 1;
				cunOil = 0;
			}
		}
		if (sum < 0) return -1;
		return startIndex;
	}

///*** No.137
	int singleNumber(vector<int>& nums) {
		int res = nums[0];
		std::multiset<int> mtemp;
		std::set<int> temp;
		for (auto it : nums){
			mtemp.insert(it);
			temp.insert(it);
		}

		for (auto it : temp){
			if (mtemp.count(it) < 3){
				res = it;
			}
		}
		return res;
	}

///*** No.138
	Node* copyRandomList(Node* head) {
		if (head == NULL)return NULL;
#if 0
		// 方法一
		std::vector<Node*> nodeArr;
		std::map<Node*, int> nodeMap;
		cpHead = new Node(head->val);
		Node* p = head->next;
		int index = 0;
		nodeMap.insert(std::make_pair(p, index++));
		Node* q = cpHead;
		nodeArr.push_back(q);
		while (p != NULL) {
			q->next = new Node(p->val);
			p = p->next;
			q = q->next;
			nodeArr.push_back(q);
			nodeMap.insert(std::make_pair(p, index++));
		}

		p = head;
		q = cpHead;
		while (p != NULL) {
			q->random = nodeArr[nodeMap[p->random]];
			p = p->next;
			q = q->next;
		}
		return cpHead;
#else
		// 方法二：大神解法
		// 使用哈希表：里面的键值对是{旧的地址，新的地址}
		// 在遍历一遍，通过这个哈希表来构造深拷贝的链表
		std::map<Node*, Node*> mBaseNewNode;
		Node* p = head;
		while (p) {
			mBaseNewNode.insert(std::make_pair(p, new Node(p->val)));
			p = p->next;
		}
		p = head;
		while (p) {
			// p就是当前的位置
			// 通过旧地址找到新对应地址的位置，然后在通过旧地址的next和random在索引到对应的新地址【妙】
			mBaseNewNode[p]->next = mBaseNewNode[p->next];
			mBaseNewNode[p]->random = mBaseNewNode[p->random];
			p = p->next;
		}
		return mBaseNewNode[head];
#endif
	}

///*** No.139
	bool wordBreak(string s, vector<string>& wordDict) {
		// 字符串匹配函数
		std::function<bool(const std::string&, const std::string&)> strCmp = [](const std::string& str1, const std::string& str2)->bool {
			int str2Size = str2.size();
			if (str1.size() < str2Size)
				return false;

			for (int i = 0; i < str2Size; ++i) {
				if (str1[i] != str2[i])
					return false;
			}
			return true;
		};


		// wordDict里面的单词可不可以组合出s来
		if (s == "")return true;
		std::vector<int> bs(s.size(), -1);
		std::function<bool(int)> dfs = [&](int index)->bool {
			// 当前这个位置有没有进行匹配过需要记录一下
			// printf("%s(%d):%s\n", __FILE__, __LINE__, s.c_str());
			if (s.size() <= index)return true;
			if (bs[index] != -1)return bs[index];
			for (auto str : wordDict) {
				// 如果当前这个位置匹配了，就接着这个位置往后找
				if (strCmp(s.data() + index, str) && dfs(index + str.size())) {
					bs[index] = true;
					return true;
				}
			}
			bs[index] = false;
			return false;
		};
		return dfs(0);
	}

///*** No.142
	ListNode* detectCycle(ListNode* head) {
		// 如果它访问的next在集合里面就证明有环
		std::set<ListNode*> sNode;
		while (head) {
			if (sNode.find(head) != sNode.end()) {
				return head;
			}
			sNode.insert(head);
			head = head->next;
		}
		return NULL;
	}

///*** No.143
	void reorderList(ListNode* head) {
        if(head == NULL)return;
		// 访问链表中的元素保存到数组中，然后使用双指针重组链表
		std::vector<ListNode*> NodeArr;
		ListNode* p = head;
		while (p){
			NodeArr.push_back(p);
			p = p->next;
		}
		p = head;
		int l = 1, r = NodeArr.size() - 1;
		while (l <= r){
			p->next = NodeArr[r];
			p = p->next;
			p->next = NodeArr[l];
			p = p->next;
			++l;
			--r;
		}
        p->next = NULL;
	}
};