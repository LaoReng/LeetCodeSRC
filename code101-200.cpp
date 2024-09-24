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
};