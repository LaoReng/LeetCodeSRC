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
};