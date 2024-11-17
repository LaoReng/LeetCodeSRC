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

///*** No.133
	Node* cloneGraph(Node* node) {
		// 用一个map标记，base图里面的节点有没有被访问，如果被访问了，那就直接放入到当前节点的neighbors中，没有的话就需要访问他
		// map => baseNodePtr -> newNodePtr
		if (!node)return NULL;

		std::map<Node*, Node*> mNode; // 用于记载遍历过的图节点
		// 深拷贝递归函数
		std::function<void(Node*, Node*)> dfs = [&](Node* baseNodePtr, Node* newNodePtr) {
			if (!baseNodePtr || !newNodePtr)return;
			// mNode.insert(std::make_pair(baseNodePtr, newNodePtr));
			std::vector<Node*>  _neighbors = baseNodePtr->neighbors;
			for (auto it : _neighbors) {
				auto item = mNode.find(it);
				if (item != mNode.end()) {
					// 就证明这个东西已经访问过了
					// 就直接将这个地址放入到当前这个新的newNodePtr的neighbors数组里面就可以了
					newNodePtr->neighbors.push_back(item->second);
				}
				else {
					// 创建这个新的节点
					Node* temp = new Node(it->val);
					// 将这个添加到映射表中
					mNode.insert(std::make_pair(it, temp));
					// 并将他添加到新的newNodePtr的neighbors数组里面
					newNodePtr->neighbors.push_back(temp);
					// 然后递归遍历这个新创建的节点
					dfs(it, temp);
				}
			}
		};

		Node* res = new Node(node->val);
		mNode.insert(std::make_pair(node, res));
		dfs(node, res);
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

///*** No.146
	class LRUCache {
	public:
		// 还是要使用一个链表，把新put的放在开头，当谁被访问了则把他移到开头
		// 如果是O(1)的时间复杂度，则需要借助哈希表来实现

		// 构造函数
		LRUCache(int capacity)
			: m_list(nullptr)
			, m_headPtr(nullptr)
			, m_tailPtr(nullptr)
			, m_capacity(capacity)
		{
		}
		// 获取值函数
		int get(int key) {
			auto val = m_hashKey.find(key);
			if (val == m_hashKey.end())return -1;
			// 需要把当前这个节点的位置移到开头
			moveNode(val->second);
			return val->second->value;
		}
		// 向缓存中插入值的函数
		void put(int key, int value) {
			// 如果这个key存在，则就是换一下里面的值，然后将这个节点在重新插入到头节点中
			auto val = m_hashKey.find(key);
			if (m_hashKey.find(key) != m_hashKey.end()) {
				// 这个key存在
				val->second->value = value;
				get(key);
				return;
			}

			int nodeSize = m_hashKey.size();
			// 新建一个元素直接插入到头部就可以了
			node* temp = new node(key, value);
			m_hashKey.insert(std::make_pair(key, temp));
			if (nodeSize == m_capacity) {
				// 缓存满了，就需要把链表最后一个元素删除，然后在头部插入一个元素
				// ,还要把hashmap里面对应的key给删除
				int key = deleteTailNode();
				m_hashKey.erase(key);
				insertHeadNode(temp);
			}
			else {
				if (nodeSize == 0) {
					// 这个就需要给两个链表指针进行赋值了
					m_headPtr = m_tailPtr = temp;
				}
				else {
					// 将他插入到头部
					insertHeadNode(temp);
				}
			}
		}
	private:
		// 双向链表
		struct node {
			int key;
			int value;
			node* next; // 指向后一个
			node* prev; // 指向前一个
			node(int key, int val)
				: key(key)
				, value(val)
				, next(NULL)
				, prev(NULL)
			{}
		};

		std::unordered_map<int, node*> m_hashKey;
		node* m_list;    // 双向链表实例
		node* m_headPtr; // 链表头指针
		node* m_tailPtr; // 链表尾指针
		int m_capacity;  // 缓冲区最大数

	private:
		// 移动链表中的节点
		void moveNode(node* ptr) {
			// 将ptr从链表中拆除，然后插入到头部
			if (ptr == m_headPtr) // 已经是头节点了就不需要移动了
				return;
			if (ptr == m_tailPtr) {
				// 这个是尾部节点
				m_tailPtr = ptr->prev;
				ptr->prev->next = NULL;
			}
			else {
				// 这个就是中间的节点
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
			}
			insertHeadNode(ptr);
		}
		// 删除链表中的尾部节点
		int deleteTailNode() {
			int key;
			if (m_tailPtr == m_headPtr) { // 链表中只有一个节点的情况处理
				key = m_tailPtr->key;
				m_tailPtr = m_headPtr = NULL;
				delete m_tailPtr;
				return key;
			}
			node* temp = m_tailPtr;
			m_tailPtr = m_tailPtr->prev;
			if (m_tailPtr)
				m_tailPtr->next = NULL;
			key = temp->key;
			delete temp;
			return key;
		}
		// 在链表头部插入节点
		void insertHeadNode(node* ptr) {
			ptr->next = m_headPtr;
			if (m_headPtr)
				m_headPtr->prev = ptr;
			m_headPtr = ptr;
			if (m_tailPtr == NULL)
				m_tailPtr = m_headPtr;
		}
	};

///*** No.147
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL)return NULL;
		// 链表排序
		ListNode* newHead = head;
		ListNode* basePtr = head->next;
		newHead->next = NULL;
		while (basePtr) {
			ListNode* temp = basePtr;
			basePtr = basePtr->next;
			// 拿着当前这个basePtr和newHead里面的节点进行比较，看把他插在哪里
			ListNode* p = newHead;
			ListNode* nextP = p->next;
			if (nextP == NULL) {  // 只有一个节点
				if (temp->val > p->val) {
					// 插入到后面
					p->next = temp;
					temp->next = NULL;
				}
				else {
					// 插入到前面
					temp->next = p;
					newHead = temp;
				}
			}
			else if (temp->val <= p->val) { // 比当前第一个节点就小，所以要他来当头节点
				temp->next = p;
				newHead = temp;
			}
			else {
				// 现在就是没有特殊情况了
				while (nextP) {
					if (nextP->val > temp->val)
						break;
					nextP = nextP->next;
					p = p->next;
				}
				// 现在的p就是当前要插入节点的前一个节点
				temp->next = p->next;
				p->next = temp;
			}
		}
		return newHead;
	}

///*** No.148
	ListNode* sortList(ListNode* head) {
		int* valueArr = new int[50009];
		int* tempArr = new int[50009];

		// 不交换节点，使用归并排序来解决这个问题
		if (head == NULL)return NULL;
		// 首先用O(n)的时间复杂度吧数据提取出来
		ListNode* p = head;
		int size = 0;
		while (p) {
			++size;
			valueArr[size - 1] = p->val;
			p = p->next;
		}
		// 开始归并排序
		int gap = 1;  // 每组归并的数据个数
		while (gap < size) {
			// 进行子数组的合并，下一次开始合并的起始位置应该是移动两个子数组长度
			for (int j = 0; j < size; j += 2 * gap) {
				int begin1 = j, end1 = begin1 + gap - 1;
				int begin2 = end1 + 1, end2 = begin2 + gap - 1;

				// 处理特殊情况，防止数组越界（总数为奇数时会出现）
				if (end1 >= size || begin2 >= size) // 第一个子数组位置超过数组长度或者第二个数组的起始位置超过
					break;
				if (end2 >= size) {  // 第二个子数组的结束位置超过数组长度
					end2 = size - 1;
				}
				// 开始两个子数组的合并
				int i = j;
				while (begin1 <= end1 && begin2 <= end2) {
					if (valueArr[begin1] < valueArr[begin2]) {
						tempArr[i++] = valueArr[begin1++];
					}
					else {
						tempArr[i++] = valueArr[begin2++];
					}
				}
				// 尾部剩余元素的处理
				while (begin1 <= end1) {
					tempArr[i++] = valueArr[begin1++];
				}
				while (begin2 <= end2) {
					tempArr[i++] = valueArr[begin2++];
				}
				// 将合并的有序数据拷贝到原来指定的位置
				memcpy(valueArr + j, tempArr + j, sizeof(int) * (end2 - j + 1));
			}
			gap *= 2; // 下次合并都是上一次的二倍
		}
		p = head;
		int  i = 0;
		while (p) {
			p->val = valueArr[i++];
			p = p->next;
		}
		return head;
	}

///*** No.150
	int evalRPN(vector<string>& tokens) {
		// 用栈来实现
		// 
		std::stack<int> s;
		for (int i = 0; i < tokens.size(); ++i){
			if (tokens[i].size() == 1 && (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")){
				// 这个是运算符，需要运算
				char ch = tokens[i][0];
				int b = s.top();
				s.pop();
				int a = s.top();
				s.pop();
				switch (ch)
				{
				case '+':
					s.push(a + b);
					break;
				case '-':
					s.push(a - b);
					break;
				case '*':
					s.push(a*b);
					break;
				case '/':
					s.push(a / b);
					break;
				default:
					break;
				}
			}
			else{
				s.push(atoi(tokens[i].data()));
			}
		}
		// std::cout << atoi("-11") << std::endl;

		return s.top();
	}

///*** No.151
	string reverseWords(string s) {
		std::string str;
		std::stack<std::string> sstr;
		s += " ";
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == ' ') {
				// 需要进行处理
				if (str.empty() == false) {
					sstr.push(str);
					str.clear();
				}
			}
			else {
				str += s[i];
			}
		}
		str.clear();
		while (!sstr.empty()) {
			str += sstr.top();
			sstr.pop();
			if (!sstr.empty())
				str += " ";
		}
		return str;
	}

///*** No.152
	int maxProduct(vector<int>& nums) {
		// 当前位置的最大值，等于上一个位置的最大值和本位置的值取最大值
        // 但是这个又和子序列最大和不一样，他有一个负数乘负数的情况，所以还要取一个最小值
		// fmax(i) = max(fmax(i-1)*a,fmin(i-1)*a, a)
		int max = nums[0];
		int min = nums[0];
		for (int i = 1; i < nums.size(); ++i){
            int oldMax = max, oldMin = min;
			max = std::max(oldMax*nums[i],std::max(oldMin*nums[i], nums[i]));
			min = std::min(oldMax*nums[i], std::min(oldMin*nums[i], nums[i]));
			nums[i] = max;
		}

		return *std::max_element(nums.begin(), nums.end());
		// return max;
	}

///*** No.153
	int findMin(vector<int>& nums) {
		int begin = 0;
		int end = nums.size()-1;
		while (begin < end) {
			int mid = (end - begin) / 2 + begin;
			if (nums[mid] > nums[end]) {
				begin = mid+1; // mid比end大，直接跳过mid
			}
			else {
				end = mid;
			}
		}
		return nums[end];
	}

///*** No.155
	class MinStack {
	public:
		std::multiset<int> m_mset;
		std::stack<int> m_stack;
		MinStack() {
			// 两个数据结构就可以了
			// 栈和可重复set

		}

		void push(int val) {
			m_stack.push(val);
			m_mset.insert(val);
		}

		void pop() {
			int top = m_stack.top();
			m_stack.pop();
			m_mset.erase(m_mset.find(top));
		}

		int top() {
			return m_stack.top();
		}

		int getMin() {
			return *m_mset.begin();
		}
	};

///*** No.162
	int findPeakElement(vector<int>& nums) {
		// mid 要是大于 mid+1 ，则峰值在mid的左侧
		// mid 要是小于 mid+1 ，则峰值在mid的右侧
		int l = 0;
		int r = nums.size() - 1;
		while (l < r) {
			int mid = (r - l) / 2 + l;
			if (nums[mid] < nums[mid + 1]) {
				l = mid + 1; // 往后移一个，就是表明mid不可能成为峰值
			}
			else {
				r = mid;
			}
		}
		return r;
	}

///*** No.164
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2)return 0;
		std::sort(nums.begin(), nums.end());

		for (int i = 0; i < nums.size() - 1; i++) {
			nums[i] = nums[i + 1] - nums[i];
		}
		nums[nums.size() - 1] = -9999999;
		return *std::max_element(nums.begin(), nums.begin() + nums.size() - 1);
	}

///*** No.165
	int compareVersion(string version1, string version2) {
		// 思路，把里面的'.'变成'\0'，然后记录'\0'的位置
		// 将每一段转化成数字
		char* verStr1 = (char*)version1.c_str();
		char* verStr2 = (char*)version2.c_str();

		std::queue<int> verQue1;
		std::queue<int> verQue2;
		verQue1.push(-1);
		verQue2.push(-1);

		for (int i = 0; i < version1.size(); ++i) {
			if (verStr1[i] == '.') {
				verStr1[i] = '\0';
				verQue1.push(i);
			}
		}
		for (int i = 0; i < version2.size(); ++i) {
			if (verStr2[i] == '.') {
				verStr2[i] = '\0';
				verQue2.push(i);
			}
		}
		while (!verQue1.empty() || !verQue2.empty()) {
			int  ver1 = 0, ver2 = 0;
			if (!verQue1.empty()) {
				ver1 = atoi(verStr1 + verQue1.front() + 1);
				verQue1.pop();
			}
			if (!verQue2.empty()) {
				ver2 = atoi(verStr2 + verQue2.front() + 1);
				verQue2.pop();
			}
			if (ver1 < ver2)
				return -1;
			if (ver1 > ver2)
				return 1;
		}
		return 0;
	}

///*** No.166
	string fractionToDecimal(int numerator, int denominator) {
		// 如果出现过之前出现的**余数**，则表示开始循环

		if (!numerator)return "0";
		std::string res; // 最后结果
		std::map<long long, int> mapFractionalPart; // 用来判断循环
		std::string strFractionalPart;  // 小数部分
		// 处理之前首先扩大存储，防止溢出
		long long llNumerator = numerator;
		long long llDenominator = denominator;
		// 首先把符号去掉
		int symbol = 1;
		llNumerator < 0 ? (symbol *= -1, llNumerator *= -1) : 0;
		llDenominator < 0 ? (symbol *= -1, llDenominator *= -1) : 0;
		if (symbol == -1)res += '-';
		// 整数部分
		char buf[40] = "";
		sprintf(buf, "%lld", llNumerator / llDenominator);
		res += buf;
		// 小数部分
		do {
			if (llNumerator % llDenominator != 0)res += '.';
			else break;

			// 把他的余数拿过来*10，然后这就是小数部分
			long long remainder = llNumerator % llDenominator;
			while (remainder) {
				remainder *= 10;
				// 先在map中查找存在remainder吗
				auto item = mapFractionalPart.find(remainder);
				if (item != mapFractionalPart.end()) {
					// 这是存在的情况
					strFractionalPart.insert(item->second, "(");
					strFractionalPart += ')';
					break;
				}
				// 这是不存在的情况
				char buf[40] = "";
				sprintf(buf, "%lld", remainder / llDenominator);
				mapFractionalPart.insert(std::make_pair(remainder, strFractionalPart.size()));
				strFractionalPart += buf;
				remainder %= llDenominator;
			}
		} while (false);
		res += strFractionalPart;
		return res;
	}

///*** No.167
	vector<int> twoSum(vector<int>& numbers, int target) {
		// 双指针
		// 如果两个数相加大于target就往后移动
		// 如果两个数相加小于target就往前移动
		int l = 0;
		int r = numbers.size() - 1;
		while (l < r) {
			if (numbers[l] + numbers[r] > target) {
				--r;
			}
			else if (numbers[l] + numbers[r] < target) {
				++l;
			}
			else
				break;
		}
		return std::vector<int>{l + 1, r + 1};
	}

///*** No.169
	int majorityElement(vector<int>& nums) {
        // 摩尔投票算法
        // 这个算法的本质意思就是当这个候选数是众数时，他与其它非众数的和应该大于0
        // 所以就假定候选数，然后计算候选数与非候选数的和，当等于0时更换候选数
        int candidate; // 候选的多数
        int sum = 0; // 总和

        for(auto it:nums){
            if(sum ==0) candidate = it;
            sum += (it==candidate?1:-1);
        }

        int count = 0;
        for(auto it:nums)
            if(candidate==it)++count;

        return count>nums.size()/2?candidate:0;
    }

///*** No.172
	int trailingZeroes(int n) {
		// 实际上就是5*2的个数，2一定是比5多的，所以直接判断阶乘中包含多少个5就可以了
		int res = 1;
		int zeroNum = 0;
		for (int i = 1; i <= n; ++i){
			int temp = i;
			// 提取5
			while (true){
				if (temp % 5 == 0){
					++zeroNum;
					temp /= 5;
				}
				else{
					
					break;
				}
			}
		}
		return zeroNum;
	}

///*** No.173
	class BSTIterator {
	public:
		BSTIterator(TreeNode* root) {
			inorderTraversal(root);
			index = 0;
		}

		int next() {
			return treeNodeValue[index++];
		}

		bool hasNext() {
			return index >= treeNodeValue.size() ? false : true;
		}
	private:
		void inorderTraversal(TreeNode* node) {
			if (!node)return;
			inorderTraversal(node->left);
			treeNodeValue.push_back(node->val);
			inorderTraversal(node->right);
		}

	private:
		std::vector<int> treeNodeValue;
		size_t index;
	};

///*** No.176
	{
		# 方法一：先找到最大值，然后删除最大值，limit限制为1
		SELECT MAX(salary) AS SecondHighestSalary FROM Employee 
			WHERE id NOT IN(SELECT id FROM Employee WHERE salary in( SELECT MAX(salary) FROM Employee)) LIMIT 1;

		# 方法二：寻找第二大薪水，让寻找的薪水值小于最大的薪水
		SELECT MAX(salary) AS SecondHighestSalary FROM Employee WHERE salary < (SELECT MAX(salary) FROM Employee);
	}

///*** No.177
	{
		CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
		BEGIN
			SET N = N - 1;
			RETURN (
				# Write your MySQL query statement below.
				SELECT DISTINCT salary FROM Employee ORDER BY salary DESC LIMIT N, 1
			);
		END
	}

///*** No.178
	{
		# 窗口函数
		SELECT score, dense_rank() OVER(ORDER BY score desc) AS 'rank' FROM Scores;
	}

///*** No.179
	string largestNumber(vector<int>& nums) {
        class Compare {
        public:
            bool operator()(const std::string& str1, const std::string& str2) {
                // 两个字符串正反拼接，那个拼出来的大谁就在前面

                std::string str1str2 = str1 + str2;
                std::string str2str1 = str2 + str1;
                for(int i = 0; i < str1str2.size(); ++i){
                    if(str1str2[i] > str2str1[i])
                        return true;
                    else if(str1str2[i] < str2str1[i])
                        return false;
                }
                return false;
            }
        };

		// 自定义排序函数
		std::vector<std::string> numsArr;
        // 数字字符串化
		for (int i = 0; i < nums.size(); ++i) {
			char buf[15] = "";
            sprintf(buf, "%d", nums[i]);
			numsArr.push_back(buf);
		}

		std::sort(numsArr.begin(), numsArr.end(), Compare());
        // 全是0就直接返回0
        if(numsArr[0] == "0" && numsArr[numsArr.size()-1] == "0")
            return "0";
        
		std::string str;
		for (auto it : numsArr) {
			std::cout << it << std::endl;
			str += it;
		}

		return str;
	}

///*** No.180
	{
		# 使用lag()窗口函数，获取当前行的前两行，如果内容一致则表示至少出现了三次
		# 还需要去一下重
		SELECT DISTINCT c.num AS ConsecutiveNums FROM (
			select num, lag(num, 1)over() as a, lag(num, 2)over () as b from Logs
			) AS c 
			WHERE c.num = c.a AND c.a = c.b;
	}

///*** No.184
	{
		SELECT T.name AS Department, e.name AS Employee, e.salary AS Salary 
			FROM Employee AS e LEFT JOIN  (
				SELECT d.id AS id, d.name AS name, MAX(e.salary) AS sa 
					FROM Employee AS e, Department AS d 
					WHERE e.departmentId = d.id  GROUP BY d.id 
			) AS T ON e.departmentId = T.id
			WHERE T.sa = e.salary;
	}

///*** No.187
	vector<string> findRepeatedDnaSequences(string s) {
        std::vector<std::string> res;
        if(s.size()<10)return res;
        // 用哈希表进行保存，如果这个DNA序列再次出现就表示出现了不止一次
		std::map<std::string, bool> mDNA;
		
		for (int i = 0; i <= s.size() - 10; ++i) {
			std::string temp = s.substr(i, 10);
			auto item = mDNA.find(temp);
			std::cout << temp << "	" << s.substr(i, 10) << std::endl;
			if (item == mDNA.end()) {
				// 表示这个里面没有这10位
				mDNA.insert(std::make_pair(temp, false));
			}
			else {
				// 表示这个里面存在这10位
				if (!item->second) {
					// 没有加入过结果数组
					item->second = true;
					res.push_back(temp);
				}
			}
		}
		return res;
	}

///*** No.189
	void rotate(vector<int>& nums, int k) {
		k = k % nums.size();
		if (!k)return;
#if 1
		// 位置计算
		std::function<int(int)> indexCalculate = [&](int currentIndex)->int {
			int toIndex = -1;
			if (currentIndex >= 0 && currentIndex < nums.size() - k) {
				toIndex = currentIndex + k;
			}
			else if (currentIndex >= nums.size() - k && currentIndex < nums.size()) {
				toIndex = currentIndex - nums.size() + k;
			}
			return toIndex;
		};
		
		std::vector<int> tempArr = nums;
		int curIndex = 0;

		while (curIndex < nums.size()) {
			// 先计算这个元素要放的位置
			int toIndex = indexCalculate(curIndex);
			// 如果要去的位置和当前位置一样或者toIndex为-1就结束循环
			if (toIndex == curIndex || toIndex == -1)
				break;
			// 把这个位置的元素放到nums中对应的位置
			nums[toIndex] = tempArr[curIndex++];
		}
#else
		// 方法二，利用数组反转函数
		// 反转函数
		std::reverse(nums.begin(), nums.end());
		std::reverse(nums.begin(), nums.begin() + k);
		std::reverse(nums.begin() + k, nums.end());
#endif
	}

///*** No.198
	int rob(vector<int>& nums) {
        // 只要不是当前位置的前一个，它可以从前面的任意位置过来，最高就是找前面位置最大的
		for (int i = 2; i < nums.size(); ++i) {
			nums[i] += *std::max_element(nums.begin(), nums.begin() + (i - 1));
		}
		return *std::max_element(nums.begin(), nums.end());
	}

///*** No.199
	vector<int> rightSideView(TreeNode* root) {
        // 广度优先遍历，每次输出本层最右边的节点
		std::vector<int> res;
		if (root == NULL)return res;
		std::queue<TreeNode*> temp;
		temp.push(root);
		while (!temp.empty()) {
			res.push_back(temp.back()->val);
			int size = temp.size();
			for (int i = 0; i < size; ++i) {
				TreeNode* p = temp.front();
				temp.pop();
				if (p->left)
					temp.push(p->left);
				if (p->right)
					temp.push(p->right);
			}
		}
		return res;
	}
};