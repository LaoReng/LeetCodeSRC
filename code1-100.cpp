class Solution {
public:
///*** No.1
#if 1
    vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> ret;
      auto it = nums.begin();
        for(int i=0;i<nums.size();i++){
          for(int j=i+1;j<nums.size();j++){
            if(nums[i]+nums[j]==target){
              ret.push_back(i);
              ret.push_back(j);
              return ret;
            }
          }
        }
        return ret;
    }
#endif
#if 0
  // TODO: 有问题待修改
  vector<int> twoSum(vector<int>& nums, int target) {
	  vector<int> ret;
	  map<int, int> num_index;
	  for (int i = 0; i < nums.size(); i++) {
		  if (nums[i] <= target) {
			  num_index.insert(map<int, int>::value_type(i, nums[i]));
		  }
	  }
	  for (auto it = num_index.begin(); it != num_index.end() ; it++) {
      auto _it  = ++it;
      --it; 
		  for(; _it!=num_index.end(); _it++){
        if((*it).second+(*_it).second==target){
          ret.push_back((*it).first);
              ret.push_back((*_it).first);
              return ret;
        }
      }
	  }
    return ret;
  }
#endif

///*** No.2
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *l = NULL, *p = NULL; // l 返回的ListNode对象指针变量
        int sumval = l1->val + l2->val, jinwei = 0; // sumval 保存指定位上的相加和，jinwei表示指定位上向前的进位值
        l = new ListNode(sumval % 10); p = l;
        l1 = l1->next; l2 = l2->next;
        while(true){
            jinwei = sumval / 10;
            if(!l1 && !l2 && !jinwei) // 链表及进位都为空返回
                break;
            sumval = jinwei;
            if(l1){ // 防止l1为空造成运行时错误
                sumval += l1->val;
                l1 = l1->next;
            }
            if(l2){
                sumval += l2->val;
                l2 = l2->next;
            }
            p->next = new ListNode(sumval % 10);
            p = p->next;
        }
        return l;
    }

///*** No.3
    char m_index[256];
    int strLen() {
        int len = 0;
        for (int i = 0; i < sizeof(m_index); i++)
            if (m_index[i] != -1)
                len++;
        return len;
    }
public:
    Solution() {
        memset(m_index, -1, sizeof(m_index));
    }
    int lengthOfLongestSubstring(std::string s) {
        int subStrMax = 0;
        int subStrLen = 0;
        for (int i = 0; i < s.size(); i++) {
            if (m_index[s[i]] != -1) { // 这里面有值
                subStrLen = strLen();
                subStrMax < subStrLen ? subStrMax = subStrLen : NULL;
                for (int j = m_index[s[i]]; j >= 0; j--)
                    m_index[s[j]] == j ? m_index[s[j]] = -1 : NULL;
                m_index[s[i]] = i;
            }
            else {
                m_index[s[i]] = i;
            }
        }
        subStrLen = strLen();
        subStrMax < subStrLen ? subStrMax = subStrLen : NULL;
        return subStrMax;
    }

///*** No.4
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size = nums1.size() + nums2.size();
	    int zho = size / 2;
	    for (int i = 0; i < nums2.size(); i++) {
		    nums1.push_back(nums2[i]);
	    }
	    std::sort(nums1.begin(), nums1.end());
	    if (size % 2 == 0) {
		    // 偶数个
		    return (nums1[zho - 1] + nums1[zho]) / 2.0;
	    }
	    else {
		    // 奇数个
		    return nums1[zho] * 1.0;
	    }
    }

///*** No.5
    bool IsPalindrome(string& s, int beginIndex, int endIndex) {
        int length = endIndex - beginIndex + 1;
        for(int i = 0; i < length / 2; i++) {
            if(s[beginIndex + i] != s[endIndex - i])
                return false;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int MaxLength = 1, MaxBeginIndex = 0;
	    int strLength = s.size();
        string MaxStr;
	    for (int i = 0; i < strLength; i++) {
		    for (int j = strLength - 1; j > i; j--) {
                if(j-i+1<MaxLength)
                    break;
			    if (s[i] == s[j]) {
				    if (true == IsPalindrome(s, i, j)) {
					    int length = j - i + 1;
					    if (length > MaxLength) {
						    MaxLength = length;
						    MaxBeginIndex = i;
					    }
				    }
			    }
		    }
	    }
	    MaxStr.resize(MaxLength);
	    memcpy((char*)MaxStr.c_str(), s.c_str()+ MaxBeginIndex, MaxLength);
	    return MaxStr;
    }

///*** No.6
    string convert(string s, int numRows) {
	    int strSize = s.size();
	    if (numRows == 1 || strSize <= numRows)
		    return s;
	    multimap<int, char> resultMap; // multimap会自动按照key的大小进行升序排列元素
	    int index = -1;
	    int jinwei = 1;
	    for (int i = 0; i < strSize; i++) {
            // 将每个字符和它应该对应的下标联系起来
            /*
            * numRows等于4时对应下标
            * PAYPALISHIRING
            * 01232101232101
            */
		    index += jinwei;
		    resultMap.insert(make_pair(index, s[i]));
		    if (index == numRows - 1) {
			    jinwei *= -1;
		    }
		    else if (!index && jinwei == -1) {
			    jinwei *= -1;
		    }
	    }
        s.clear();
	    auto it = resultMap.begin();
	    for (; it != resultMap.end(); it++) {
		    s += (*it).second;
	    }
	    return s;
    }

///*** No.7
    int reverse(int x) {
        long long result = 0;
	    int boundary = 2147483647; // 32位有符号整数的边界值 2^31 − 1
	    char Minus = 1; // x为负数该值为-1，x为正数该值为1
	    if (x < 0) {
		    Minus = -1;
	    }
	    while (x != 0) {
		    result = result * 10 + x % 10;
		    x /= 10;
	    }
	    return (result*Minus)>boundary?0:result;
    }

///*** No.8
    int myAtoi(string s) {
      long long result = 0;
      char fuhao = '\0';
      int i = 0;
      while(s[i] == ' ')
        i++;
      if(s[i] == '-' || s[i] == '+'){
        fuhao = s[i];
        i++;
      }
      while(s[i] >= '0' && s[i] <= '9'){
        result = result * 10 + (s[i] - '0');
        if(result > 2147483647){
          return fuhao == '-' ? -2147483648 : 2147483647;
        }
        i++;
      }
      return fuhao == '-' ? -1 * result : result;
    }

///*** No.9
    bool isPalindrome(int x) {
        if(x < 0)
            return false;
        long long result = 0;
        int _x = x;
        while(_x > 0){
            result = result * 10 + _x % 10;
            _x /= 10;
        }
        if(result - x == 0)
            return true;
        return false;
    }

///*** No.11
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
		 int max = -9999;
		 bool b = false;
		 while (l <= r) {
			 b = false;
			 int  res = (height[l] < height[r] ? height[l] : height[r]) * (r - l);
			 if (max < res)
				 max = res;
			 if (height[l] < height[r]) {  // 这里为什么要移动那个短的：因为短的移动到它的下一个，那个下一个可能比他长，也就是说\
             它可以有更大的几率让这个面积变大，如果不变大也没关系因为有兜底的，两头有一个短的就把他移动
				 l++;
			 }
			 else
				 r--;
		 }
		 return max;
    }

///*** No.12
    std::string intTo(int num, int index) {
		std::string res;

		if (index == 4) {
			for (int i = 0; i < num; i++) {
				res += 'M';
			}
			return res;
		}

		for (int i = 1; i < index; i++) {
			num *= 10;
		}
		if (index == 1) {
			// 1位的处理
			if (num == 4) {
				return "IV";
			}
			if (num == 9)return "IX";
			while (num > 0) {
				if (num >= 5) {
					res += 'V';
					num -= 5;
					continue;
				}
				res += 'I';
				num -= 1;
			}
			return  res;
		}

		if (index == 2) {
			// 2位的处理
			if (num == 40) {
				return "XL";
			}
			if (num == 90)return "XC";
			while (num > 0) {
				if (num >= 50) {
					res += 'L';
					num -= 50;
					continue;
				}
				res += 'X';
				num -= 10;
			}
			return res;
		}

		if (index == 3) {
			// 3位的处理
			if (num == 400) {
				return  "CD";
			}
			if (num == 900)return  "CM";
			while (num > 0) {
				if (num >= 500) {
					res += 'D';
					num -= 500;
					continue;
				}
				res += 'C';
				num -= 100;
			}
			return res;
		}
		return "";
	}

    string intToRoman(int num) {
        // 可以先将位数拆出来，
        // 第一个规则：不是4和9，对应的做法就是找同位的一直减，直到为0为止
        // 第二个规则：如果是4和9开头，就有对应的值匹配
        // 第三个规则：如果只有1，10，100，1000这样的话，只能有所代表的表示，不能有5+5这种的
        std::string res;
		int index = 1;
		while (num > 0) {
			res = intTo(num % 10, index++) + res;
			num /= 10;
		}
		return res;
    }

///*** No.15
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 三数之和
		// 先将数据排序
		// 然后固定一位，后面用双指针进行遍历
		// 出来的三个数进行相加处理，
		// 如果加出来的数大于0，则需要将后面的指针向前移动
		// 如果加出来的数小于0，则需要将前面的指针向后移动
		// 直到两个指针相聚为止
		std::vector<std::vector<int>> res;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); ) {
			int l = i + 1, r = nums.size() - 1;
			while (l < r) {
				int temp = nums[i] + nums[l] + nums[r];
				if (temp == 0) {
					std::vector<int> item = { nums[i], nums[l], nums[r] };
					res.push_back(item);
					l++;
					r--;
					// break;
					while (l < r) {
						if (nums[l] == nums[l - 1]) {
							l++;
						}
						else break;
					}
					while (l < r) {
						if (nums[r] == nums[r + 1]) {
							r--;
						}
						else break;
					}
				}
				else if (temp < 0) {
					// 这三个数小了，就需要把左边的变大
					l++;
					while (l < r) {
						if (nums[l] == nums[l - 1]) {
							l++;
						}
						else break;
					}
				}
				else {
					r--;
					while (l < r) {
						if (nums[r] == nums[r + 1]) {
							r--;
						}
						else break;
					}
				}
			}
			i++;
			while (i < nums.size()) {
				if (nums[i] == nums[i - 1]) {
					i++;
				}
				else
					break;
			}
		}
		return res;
    }

///*** No.16
    #define ABS(n)  ((n)>0?(n):(-1*(n)))
	static int threeSumClosest(vector<int>& nums, int target) {
		std::vector<int> temp = nums;
		int res               = temp[0] + temp[1] + temp[2];
		int size              = temp.size();
		// 就三个元素，进行特殊处理
		if (size == 3) return res;
		std::sort(temp.begin(), temp.end());
		for (int i = 0; i < size; i++) {
			int l = i + 1, r = size - 1;
			while (l < r) {
				int t = temp[i] + temp[l] + temp[r];
				if (ABS(res - target) > ABS(t - target)) {
					res = t;
				}
				if (t > target) r--;
				else l++;
			}
		}
		return res;
	}

///*** No.17
    // 构造函数
	Solution() {
		std::vector<char> strArr = { '2', '3', '4', '5', '6', '7', '8', '9' };
		std::vector<std::vector<char>> arr = {
			{ 'a', 'b', 'c' },
			{ 'd', 'e', 'f' },
			{ 'g', 'h', 'i' },
			{ 'j', 'k', 'l' },
			{ 'm', 'n', 'o' },
			{ 'p', 'q', 'r', 's' },
			{ 't', 'u', 'v' },
			{ 'w', 'x', 'y', 'z' }
		};
		for (int i = 0; i < strArr.size(); i++) {
			mNum2ch.insert(std::make_pair(strArr[i], arr[i]));
		}
	}
	vector<string> letterCombinations(string digits) {
		/**
		* 思路：分配原则
		* 原理：将这个数字对应的每一位分配到，当前的结果数组中，本轮分配完之后将结果数组进行替换得到新的组合元素\
		* 然后接着对下一个数字对应的字母进行逐一分配直到结束
		*/
		std::vector<std::string> res;
		for (auto d : digits) {
			std::vector<char> temp = mNum2ch[d];
			size_t tempSize = temp.size(), resSize = res.size();
			if (resSize <= 0) {  // 里面什么都没有证明这是第一次
				for (int j = 0; j < tempSize; j++) {
					std::string str;
					str += temp[j];
					res.emplace_back(str);
				}
			}
			else {
				// 里面有东西，就需要把他们分别加一遍这个数字，然后在重新存回数组中
				std::vector<std::string> tempRes;
				for (int j = 0; j < tempSize; j++) {
					for (int n = 0; n < resSize; n++) {
						std::string str = res[n];
						str += temp[j];
						tempRes.emplace_back(str);
					}
				}
				res = tempRes;
			}
		}
		return res;
	}
private:
	std::map<char, std::vector<char>> mNum2ch;  // 数字→字母映射表

///*** No.18
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
		// 先进行排序，然后固定两位用双指针进行遍历查找
		// 跳过重复的数字
		std::vector<long long> temp;
		for (auto it : nums){
			temp.push_back(it);
		}
		std::vector<std::vector<int>> res;
		std::sort(temp.begin(), temp.end());
		int i = 0;
		while (i < temp.size()){
			int j = i + 1;
			while (j < temp.size()){
				// 里面进行双指针遍历
				int l = j + 1, r = temp.size() - 1;
				while (l < r){
					long long resNum = temp[i] + temp[j] + temp[r] + temp[l];
					if (resNum > target) {
						// 把后面指针的值变小
						r--;
						// 跳过重复的数字 【如果当前移动到的元素，和他上一个元素相等，则需要进行移动】
						while (l < r) if (temp[r] == temp[r + 1]) r--; else break;
					}
					else if (resNum < target){
						// 把前面的指针变大
						l++;
						// 跳过重复的数字
						while (l < r) if (temp[l] == temp[l - 1]) l++; else break;
					}
					else {
						// 插入到数组,将这四个数字插入到数组中
						std::vector<int> item = { (int)temp[i], (int)temp[j], (int)temp[r], (int)temp[l] };
						res.push_back(item);
						l++;
						r--;
						// 跳过重复的数字
						while (l < r) if (temp[r] == temp[r + 1]) r--; else break;
						while (l < r) if (temp[l] == temp[l - 1]) l++; else break;
					}
				}
				j++;
				// 在这里去重
				while (j < temp.size())if (temp[j] == temp[j - 1])j++; else break;
			}
			i++;
			// 在这里对i进行去重
			while (i < temp.size()) if (temp[i] == temp[i - 1])i++; else break;
		}
		return res;
	}

///*** No.19
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 使用双指针实现，
		ListNode *delIndex = head, *moveIndex = head;
		for (int i = 1; i < n; i++){
			moveIndex = moveIndex->next;
		}
		// 然后两个指针一起移动
		ListNode* perIndex = NULL;  // 要删除元素的前一个结点
		while (moveIndex->next != NULL){
			perIndex = delIndex;
			delIndex = delIndex->next;
			moveIndex = moveIndex->next;
		}
		// 将要删除的元素删除
		if (delIndex == head){
			// head = NULL;
            head = head->next;
		}
		else
			perIndex->next = delIndex->next;
        return head;
    }

///*** No.22
    vector<string> generateParenthesis(int n) {
		int check = 0;  // 检测括号，'('+1 ')'-1
		std::string str;
		std::vector<std::string> res;
		// 函数包装器
		std::function<void(char)> dfs = [&](char c) { // =,&str, &res,&check
			if ('(' == c) ++check;
			else          --check;
			if (check < 0) {
				++check;  // check检查点，小于0了，那么返回的时候就需要将他还原回来
				return;
			}
			// 长度达到边界
			if (str.size() >= 2 * n) {
				// 这个时候就需要返回了
				if (check == 0) {
					// 把他放到结果数组中
					res.push_back(str);
					// std::cout << str << std::endl;
				}
				return;
			}
			str += c; // 将新加入的添加上
			// 继续进行匹配
			dfs('(');
			dfs(')');
			// 最后的时候，要把最后一个给取出，在加入别的
			char temp = str.back();
			str.pop_back();
			if ('(' == temp) --check;
			else             ++check;
		};
		dfs('(');
		return res;
	}

///*** No.24
    ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL)
			return head;

		ListNode* temp = new ListNode;
		temp->next = head;
		ListNode* per = temp,* p = per->next, *q = p->next;
		while (q != NULL) {
			p->next = q->next;
			q->next = p;
			per->next = q;

			// 将指针移动
			per = per->next;
			per = per->next;
			p = p->next;
			q = q->next;
			q = q->next;
			if (q)
				q = q->next;
		}
		head = temp->next;
		delete temp;
		return head;
	}

///*** No.26
    int removeDuplicates(vector<int>& nums) {
        list<int> values(nums.begin(), nums.end());
        values.unique();
        nums.assign(values.begin(), values.end());
        return values.size();
    }

///*** No.27
    int removeElement(vector<int>& nums, int val) {
        list<int> values(nums.begin(), nums.end());
        values.remove(val);
        nums.assign(values.begin(), values.end());
        return values.size();
    }

///*** No.29
    int divide(int dividend, int divisor) {
		// 可以用减法一直减
		// 但是对于负数需要特殊处理
		long long max = 2147483647, min = 2147483648;
		min *= -1;
		long long dind = dividend, dior = divisor;
		// 将他们两个去符号
		dind = dind < 0 ? (-1 * dind) : dind;
		dior = dior < 0 ? (-1 * dior) : dior;
		// 如果两个都是正数或者都是负数，则结果为正数
		// 如果两个异号，则结果为负数
		int fu = 1;
		if ((dividend >= 0 && divisor >= 0) || (dividend < 0 && divisor < 0)){
			// 当前为同号
			fu = 1;
		}
		else{
			fu = -1;
		}
		if (dividend == divisor){
			return fu * 1;
		}
		if (divisor == -1 || divisor == 1){
			// 
			long long res = fu* dind;
			if (res>max){
				res = max;
			}
			else if (res < min){
				res = min;
			}

			return res;
		}
		// 线性减
		long long temp = 0;
		long long count = 0;
		long long res = 0;
		while (dind >= dior){

			temp += dior;
			++count;

			dind -= temp;
			res += count;

			// dind -= dior;
			// ++res;
		}
		// 存在减多的情况
		if (dind < 0){
			// 减多了
			while (dind < 0){
				dind += dior;
				--res;
			}
		}

		res = fu*res;
		if (res>max){
			res = max;
		}
		else if (res < min){
			res = min;
		}

		return res;
		/*std::cout << dividend / (divisor*1.0) << std::endl;
		return 0;*/
	}

///*** No.31
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1)return;
		// 找到代价最小可以调换的数字

		// 将这个数组看成是一个数字，找它的下一个排列就是找下一个最接近比他大的数字
		// 首先需要找到当前排列的点，也就是从后往前第一个相邻的后面比前面大的数的地方
		// 比如说这个位置我们叫i,j；那么这样[j,end)这个范围内的数字一定都是降序的
		// 下面我要这个增幅最小，那就需要在这个[j,end)的区间中找第一个大于i的数k，也就是对应着从后往前查找
		// 这样将i和k所对应的数字进行交换，这样就使得交换的增幅最小
		// 现在区间[j,end)数字依然是降序的，那么我要下一个排列对应的增幅最小，只需要再将[j,end)范围内的数字变成升序就可以了

		int i = nums.size() - 2, j = nums.size() - 1, k = nums.size() - 1;
		while (i >= 0) {
			if (nums[i] < nums[j]) {
				break;
			}
			--i;
			--j;
		}
		if (i >= 0) {
			while (k >= j) {
				if (nums[i] < nums[k]) {
					// 交换
					int temp = nums[i];
					nums[i] = nums[k];
					nums[k] = temp;
					break;
				}
                --k;
			}
		}
		// 将j到end范围的数据进行调换
		k = nums.size()-1;
		while (j < k) {
			int temp = nums[j];
			nums[j] = nums[k];
			nums[k] = temp;
			++j;
			--k;
		}
    }

///*** No.33
    int search(vector<int>& nums, int target) {
		// 如果第一个元素大于最后一个元素就证明，他是有旋转的
		int res = -1;
		const int size = nums.size();
		if (size <= 1) {
			if (nums[0] == target)
				return 0;
			return -1;
		}
		// 二分查找函数包装器
		std::function<int(int, int)> binarySearch = [&](int begin, int end)->int {
			int l = begin, r = end;
			int index = -1;
			while (l <= r) {
				int mid = (r - l) / 2 + l;
				if (nums[mid] > target) {
					// 把右边的变小
					r = mid - 1;
				}
				else if (nums[mid] < target) {
					// 把左边的变大
					l = mid + 1;
				}
				else {
					index = mid;
					break;
				}
			}
			return index;
		};
		if (nums[0] > nums[size - 1]) {
			// 有旋转，那就是前面那一部分进行二分，后面那一部分进行二分
			int index = 0;
			for (int i = 0; i < size - 1; ++i) {
				if (nums[i] > nums[i + 1]) {
					// 这个就是分界点
					index = i;
					break;
				}
			}
			res = binarySearch(0, index);
			if (res >= 0) {
				return res;
			}
			res = binarySearch(index + 1, size - 1);
		}
		else {
			// 没有旋转，整个数组进行二分
			res = binarySearch(0, size - 1);
		}
		return res;
	}

///*** No.34
    vector<int> searchRange(vector<int>& nums, int target) {
		std::vector<int> res = { -1, -1 };
		// 二分查找函数包装器
		std::function<int(int, int)> rBinarySearch = [&](int begin, int end)->int {
			int l = begin, r = end;
			int index = -1;
			while (l <= r) {
				int mid = (r - l) / 2 + l;
				if (nums[mid] > target) {
					// 把右边的变小
					r = mid - 1;
				}
				else if (nums[mid] < target) {
					// 把左边的变大
					l = mid + 1;
				}
				else {
					index = mid;
					r = mid - 1;
				}
			}
			return index;
		};
		std::function<int(int, int)> lBinarySearch = [&](int begin, int end)->int {
			int l = begin, r = end;
			int index = -1;
			while (l <= r) {
				int mid = (r - l) / 2 + l;
				if (nums[mid] > target) {
					// 把右边的变小
					r = mid - 1;
				}
				else if (nums[mid] < target) {
					// 把左边的变大
					l = mid + 1;
				}
				else {
					index = mid;
					l = mid + 1;
				}
			}
			return index;
		};

		int lNum = rBinarySearch(0, nums.size() - 1);
		if (lNum == -1){
			return res;
		}
		res[0] = lNum;
		lNum = lBinarySearch(0, nums.size() - 1);
		res[1] = lNum;


		// std::cout << binarySearch(0, nums.size() - 1) << std::endl;
		return res;
	}

///*** No.35
    int searchInsert(vector<int>& nums, int target) {
        int begin = 0, end = nums.size() - 1, mid;
        if (nums[end] < target) {
            return end + 1;
        }
        if (nums[begin] > target) {
            return 0;
        }
        while (begin < end) {
            mid = ((end - begin) / 2) + begin;
            if (nums[mid] > target) {
                end = mid - 1;
            }
            else if (nums[mid] < target) {
                begin = mid + 1;
            }
            if (nums[mid] == target) {
                return mid;
            }
        }
        if (nums[begin] >= target) {
            return begin;
        }
        else {
            return begin + 1;
        }
    }

///*** No.36
    bool isValidSudoku(vector<vector<char>>& board) {
		int lineLen = board.size();    // 行长度
		int colLen = board[0].size();  // 列长度

		// 有效数组的判断
		std::function<bool(int[9])> validArrJudge = [](int judgeArr[9])->bool {
			for (int i = 0; i < 9; i++) {
				if (judgeArr[i] > 1)
					return false;
			}
			return true;
		};
		// 行判断
		std::function<bool(int)> lineJudge = [&](int lineNum)->bool {
			int judgeArr[9] = { 0 }, colLen = board[lineNum].size();
			for (int i = 0; i < colLen; i++) {
				if (board[lineNum][i] != '.')
					++judgeArr[board[lineNum][i] - '1'];
			}
			return validArrJudge(judgeArr);
		};
		// 列判断
		std::function<bool(int)> columnJudge = [&](int colNum)->bool {
			int judgeArr[9] = { 0 };
			for (int i = 0; i < lineLen; i++) {
				if (board[i][colNum] != '.')
					++judgeArr[board[i][colNum] - '1'];
			}
			return validArrJudge(judgeArr);
		};
		// 3x3二维数组判断
		std::function<bool(int, int)>twoDimArray3X3Judge = [&](int beginLineNum, int beginColNum)->bool {
			int judgeArr[9] = { 0 };
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; ++j) {
					if (board[beginLineNum + i][beginColNum + j] != '.')
						++judgeArr[board[beginLineNum + i][beginColNum + j] - '1'];
				}
			}
			return validArrJudge(judgeArr);
		};

		// 需要写一个行判断
		// 一个列判断
		// 3X3二维数组判断

		bool ret = false;
		for (int i = 0; i < lineLen; i++) {
			ret = lineJudge(i);
			if (!ret) {
				return false;
			}
		}
		for (int i = 0; i < colLen; i++) {
			ret = columnJudge(i);
			if (!ret) {
				return false;
			}
		}
		for (int j = 0; j < lineLen; j += 3) {
			for (int i = 0; i < colLen; i += 3) {
				ret = twoDimArray3X3Judge(j, i);
				if (!ret) {
					return false;
				}
			}
		}
		return true;
	}

///*** No.38
    // 要求出n的数列，就需要知道n-1的序列是什么，依次类推求出结果
	string countAndSay(int n) {
		int destN = n - 1;
		if (destN == 0) {
			return strArr[destN];
		}
		if (strArr[destN - 1] == "") {
			// 也就是说它的前一个我们不知道
			// 那我们就要把他的前一个求出来
			countAndSay(n - 1);
		}
		// 然后再求我们要求的这个
		int index = 0, perStrLen = strArr[destN - 1].size();
		std::string destStr = "";  // 目标字符串
		while (index < perStrLen) {
			// 两个步骤，计数和这个字母是啥
			char dest = strArr[destN - 1][index++];
			int count = 1;
			for (; index < perStrLen; ++index) {
				if (strArr[destN - 1][index] != dest)
					break;
				++count;
			}
			destStr += ('1' + (count - 1));
			destStr += dest;
		}
		strArr[destN] = destStr;
		return strArr[destN];
	}
private:
	std::string strArr[30] = { "1" };

///*** No.39
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		// 可以用回溯来实现
		// 先把数组排个序，去掉大于target的数
		int sum;
		int candSize = candidates.size();
		std::vector<int> item;
		std::vector<int> can;
		std::vector<std::vector<int>> res;
		std::sort(candidates.begin(), candidates.end());
		for (int i = 0; i < candSize; ++i) {
			if (candidates[i] <= target) {
				can.push_back(candidates[i]);
			}
		}
		int canSize = can.size();
		// 需要进行数组的去重处理
		std::function<void(std::vector<int>&)> pushBack = [&](std::vector<int>& item) {
			// 先把数组排序
			std::vector<int> temp = item;
			std::sort(temp.begin(), temp.end());
			int tempSize = temp.size();
			int resSize = res.size();
			for (int i = 0; i < resSize; ++i) {
				if (res[i].size() == tempSize) {
					// 进行比较
					int j = 0;
					for (; j < tempSize; ++j) {
						if (res[i][j] != temp[j]) {
							break;
						}
					}
					if (j == tempSize) {
						// 比较到最后他们一样
						return;
					}
				}
			}
			res.push_back(temp);
		};
		// 回溯
		std::function<void(int)> dfs = [&](int n) {
			if (sum + n > target) {
				return;
			}
			sum += n;
			item.push_back(n);
			if (sum == target) {
				// 这个时候就要把item存放到结果列表中
				pushBack(item);
				item.pop_back();
				sum -= n;
				return;
			}
			for (int i = 0; i < canSize; ++i) {
				dfs(can[i]);
			}
			item.pop_back();
			sum -= n;
		};
		for (int i = 0; i < canSize; ++i) {
			sum = 0;
			dfs(can[i]);
		}
		return res;
	}

///*** No.40
    struct canS{
		int value;
		bool isUse;   // false就是没有使用
		canS(int val){
			value = val;
			isUse = false;
		}
	};
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		int sum;							// 计算的和
		std::vector<canS> can;
		std::vector<int> item;
		std::vector<std::vector<int>> res;

		std::function<void(int, int)> dfs = [&](int val, int index){   // 递归遍历，需要有当前的值和当前的索引
			if (sum + val > target){
				return;
			}
			sum += val;
			item.push_back(val);
			if (sum == target){
				// 需要把它入队列
				res.push_back(item);
				sum -= val;
				item.pop_back();
				return;
			}
			// 这一深度开始没，需要确定一下
			int start = false;
			for (int i = index; i < can.size(); i++){
				if (!can[i].isUse){
					if (i>0 && start){
						if (can[i - 1].value == can[i].value){
							continue;
						}
					}
					start = true;
					can[i].isUse = true;
					dfs(can[i].value, i);
					can[i].isUse = false;
				}
			}
			item.pop_back();
			sum -= val;
		};
		// 把这个出队列，
		// 先排序将不满足的去除
		std::sort(candidates.begin(), candidates.end());
		for (int i = 0; i < candidates.size(); ++i){
			if (candidates[i] <= target){
				can.push_back(canS(candidates[i]));
			}
			else
				break;
		}
		// 求和
		for (int i = 0; i < can.size(); ++i){
			sum += can[i].value;
		}
		if (sum < target){
			return res;
		}

		// 用没用过做标记
		for (int i = 0; i < can.size(); ++i) {
			if (i > 0){
				if (can[i - 1].value == can[i].value){
					continue;
				}
			}
			can[i].isUse = true;
			sum = 0;
			dfs(can[i].value, i);
			can[i].isUse = false;
		}
		return res;
	}

///*** No.43
    // 字符串乘法
	string multiply(string num1, string num2) {
		// 字符串一位乘法
		std::function<std::string(std::string, char)> mul1 = [&](std::string mul, char muled)->std::string {
			if (muled == '0')
				return "0";
			int carry = 0;  // 进位
			int mulLen = mul.size();
			std::string res;
			for (int j = mulLen - 1; j >= 0; --j) {
				int temp = (mul[j] - '0') * (muled - '0') + carry;
				carry = temp / 10;
				res = char((temp % 10) + '0') + res;
			}
			if (carry > 0) {
				res = char(carry + '0') + res;
			}
			return res;
		};
		// 字符串加法
		std::function<std::string(std::string, std::string)> strSum = [&](std::string sum1, std::string sum2)->std::string {
			// 补位，把它们补成位数相同的
			int sum1Len = sum1.size();
			int sum2Len = sum2.size();
			if (sum1Len > sum2Len) {
				int cha = sum1Len - sum2Len;
				for (int i = 0; i < cha; ++i) {
					sum2 = '0' + sum2;
				}
			}
			else {
				int cha = sum2Len - sum1Len;
				for (int i = 0; i < cha; ++i) {
					sum1 = '0' + sum1;
				}
			}
			// 进行加法运算
			int carry = 0;    // 进位
			sum1Len = sum1.size();
			std::string sum;  // 加法结果
			for (int i = sum1Len - 1; i >= 0; --i) {
				int temp = (sum1[i] - '0') + (sum2[i] - '0') + carry;
				sum = char((temp % 10) + '0') + sum;
				carry = temp / 10;
			}
			if (carry > 0) {
				sum = char(carry + '0') + sum;
			}
			return sum;
		};

		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		// 一位一位乘，然后结果保存一下
		std::string res = "0";
		int index = 0;  // 每一数列需要向前进的位数
		int num2Len = num2.size();
		for (int i = num2Len - 1; i >= 0; --i) {
			std::string mul = mul1(num1, num2[i]);
			for (int j = 0; j < index; j++) {
				mul += '0';
			}
			res = strSum(res, mul);
			++index;
		}
		return res;
	}

///*** No.45
    // 从最后一个往回找，找到谁最远可以跳到这里
	// 然后再从这个位置往回找，找到谁最远可以跳到这里

    /// 题目理解
    // ① 从后面开始看，看前面那个“最远”位置可以跳到这里
    // ② 来到这个位置，然后我们继续进行步骤①，
    // ③ 知道回到原点起始位置为止

	int jump(vector<int>& nums) {
		int endIndex = nums.size() - 1;
		int jumpNum = 0;
		while (endIndex > 0) {
			int count = 1;
			int index = 0;
			for (int i = endIndex - 1; i >= 0; --i) {
				if (nums[i] >= count) {
					// 能跳到现在的位置
					index = i;
				}
				++count;
			}
			endIndex = index;  // 这也就是从身后最远的位置跳到这里
			jumpNum++;
		}
		return jumpNum;
	}

///*** No.46
    struct S {
		int val;
		bool isUse;
		S(int val)
			: val(val)
			, isUse(false)
		{}
	};
	vector<vector<int>> permute(vector<int>& nums) {
		std::vector<S> vals;
		std::vector<int> item;
		std::vector<std::vector<int>> res;
		int numsSize = nums.size();
		// 全排列回溯
		std::function<void(int)> dfs = [&](int val) {
			item.push_back(val);
			for (int i = 0; i < numsSize; ++i) {
				if (vals[i].isUse == false) {
					vals[i].isUse = true;
					dfs(vals[i].val);
					vals[i].isUse = false;
				}
			}
			if (item.size() == numsSize)
				res.push_back(item);
			item.pop_back();
		};
		for (int i = 0; i < numsSize; ++i) {
			vals.push_back(S(nums[i]));
		}
		for (int i = 0; i < numsSize; ++i) {
			vals[i].isUse = true;
			dfs(vals[i].val);
			vals[i].isUse = false;
		}
		return res;
	}

///*** No.47
    struct S {
		int val;
		bool isUse;
		S(int val)
			: val(val)
			, isUse(false)
		{}
	};
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		std::vector<S> vals;
		std::vector<int> item = nums;
		std::vector<std::vector<int>> res;
		int numsSize = nums.size();
		// 全排列回溯
		std::function<void(int)> dfs = [&](int val) {
			item.push_back(val);
			int start = 0;
			int per;  // 给他的前一个值保存一下
			for (int i = 0; i < numsSize; ++i) {
				if (vals[i].isUse == false) {
					if (i > 0) {
						if (start != 0) {
							if (vals[i].val == per)
								continue;
						}
					}
					start = 1;
					per = vals[i].val;
					vals[i].isUse = true;
					dfs(vals[i].val);
					vals[i].isUse = false;
				}
			}
			if (item.size() == numsSize)
				res.push_back(item);
			item.pop_back();
		};
		
		std::sort(item.begin(), item.end());
		for (int i = 0; i < numsSize; ++i) {
			vals.push_back(S(item[i]));
		}
		item.clear();
		for (int i = 0; i < numsSize; ++i) {
			if (i > 0) {
				if (vals[i].val == vals[i - 1].val)
					continue;
			}

			vals[i].isUse = true;
			dfs(vals[i].val);
			vals[i].isUse = false;
		}
		return res;
	}

///*** No.48
    void rotate(vector<vector<int>>& matrix) {
        std::vector<std::vector<int>> temp = matrix;
		for (int i = 0; i < temp[0].size(); i++) {
			for (int j = temp.size()-1; j >= 0; --j) {
				matrix[i][temp.size()-j-1] = temp[j][i];
			}
		}
    }

///*** No.49
    static const std::string itoa(int n) {
		std::string res;  // 566
		if (n == 0)return  "0";
		while (n > 0) {
			res = (char)('0' + n % 10) + res;
			n /= 10;
		}
		return  res;
	}
	// 把位置转换为数组对应的，然后将其转化为字符串，然后比较
	static const std::string str2CompStr(const std::string& str) {
		int arr[26] = { 0 };
		std::string res;
		for (int i = 0; i < str.size(); i++) {
			arr[str[i] - 'a']++;
		}
		for (int i = 0; i < 26; i++) {
			res += itoa(arr[i] * (i + 1));
		}
		return res;
	}
	struct indexStr
	{
		std::string str;
		int index;
		bool operator()(const indexStr& str1, const indexStr& str2) {
			return str1.str < str2.str;
		}
	};
	static vector<vector<string>> groupAnagrams(vector<string>& strs) {
		std::vector<std::string> temp = strs, item;
		std::vector<std::vector<std::string>> res;
		do {
			if (temp.size() <= 1) {
				item = temp;
				res.push_back(item);
				break;
			}
			std::vector<indexStr> arr1;
			// 先都给他们转化完，然后结构体排序，结构体里面是位置和转化字符串
			for (int i = 0; i < temp.size(); i++) {
				indexStr is;
				is.index = i;
				is.str = str2CompStr(temp[i]);
				arr1.push_back(is);
			}
			std::sort(arr1.begin(), arr1.end(), indexStr());
			// 现在组已经分出来了，下面就是拆分往里面放
			for (int i = 0; i < arr1.size(); i++) {
				item.push_back(temp[arr1[i].index]);
				if ((i + 1 != arr1.size()) && (arr1[i].str != arr1[i + 1].str)) {
					res.push_back(item);
					item.clear();
				}
			}
			if (item.size() > 0) {
				res.push_back(item);
			}
		} while (false);
		return res;
	}

///*** No.50
    double myPow(double x, int n) {
		if (n == 0)return 1;
		int fuhao = 1;
		if (x < 0){
			fuhao = -1;
			x *= -1; // 将x变为正数
		}
		long long ln = n;
		if (ln < 0){
			x = 1.0 / x;
			ln *= -1;
		}
		if (fuhao < 0 && ln % 2 == 0)
			fuhao = 1;

		// 现在x是一个正数
		// ln也是一个正数
		// 首先求到x的9999次幂
		// 看ln除于9999的余数就是他最后的次幂，如果ln/9999不等于0，并且它的9999次幂等于0，那么就直接返回0就可以了
		std::vector<double> p(10001, 99999);
		std::function<double(double, int)> dfsPow = [&](double x, int n)->double{
			if (p[n] != 99999)return p[n];
			if (n == 0)return 1;
			if (n == 1)return x;
			int l = n / 2;
			p[n] = dfsPow(x, l)*dfsPow(x, n - l);
			return p[n];
		};
		double yiwan = 0;
		double res = 1;
		if (ln > 10000){
			yiwan = dfsPow(x, 10000); // 先把他的1万次幂求出来
			for (int i = 0; i < ln / 10000; i++){
				res *= yiwan;
			}
			res *= dfsPow(x, ln % 10000);
		}
		else{
			res *=  dfsPow(x, ln);
		}

		return fuhao*res;
	}

///*** No.53
    int maxSubArray(vector<int>& nums) {
        // NUMS  
		// DPs   
		// dps[0] = nums[0]
		int res = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i - 1] > 0)  // 前一个大于0，就表示把他加过来只会是正影响不会产生负影响
				nums[i] += nums[i - 1];
			if (nums[i] > res)
				res = nums[i];
		}
		return res;
    }

///*** No.54
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
		// 在来个数组保存访没访问过
		std::vector<std::vector<bool>> isUse;
		std::vector<int> res;
		for (int i = 0; i < matrix.size(); i++) {
			std::vector<bool> item;
			for (int j = 0; j < matrix[i].size(); j++) {
				item.push_back(false);
			}
			isUse.push_back(item);
		}
		std::function<void(int, int)> heng = [&](int index, int zn) {
			if (zn == 1) {
				// 正向
				for (int i = 0; i < matrix[0].size(); i++) {
					if (!isUse[index][i]) {
						res.push_back(matrix[index][i]);
						isUse[index][i] = true;
					}
				}
			}
			else {
				for (int i = matrix[0].size() - 1; i >= 0; i--) {
					if (!isUse[index][i]) {
						res.push_back(matrix[index][i]);
						isUse[index][i] = true;
					}
				}
			}
		};
		std::function<void(int, int)> shu = [&](int index, int zn) {
			if (zn == 1) {
				// 正向
				for (int i = 0; i < matrix.size(); i++) {
					if (!isUse[i][index]) {
						res.push_back(matrix[i][index]);
						isUse[i][index] = true;
					}
				}
			}
			else {
				for (int i = matrix.size() - 1; i >= 0; i--) {
					if (!isUse[i][index]) {
						res.push_back(matrix[i][index]);
						isUse[i][index] = true;
					}
				}
			}
		};

		int hz = 0;  // 横正扫
		int sz = matrix[0].size() - 1;  // 竖正扫
		int hn = matrix.size() - 1; // 横逆扫
		int sn = 0;  // 竖逆扫
		// 横正 → 竖正 → 横逆 → 竖逆
		while ((hz <= hn) || (sz >= sn)) {
			if (hz < matrix.size()) {
				heng(hz, 1);
				hz++;
			}
			if (sz >= 0) {
				shu(sz, 1);
				sz--;
			}
			if (hn >= 0) {
				heng(hn, 2);
				hn--;
			}
			if (sn < matrix[0].size()) {
				shu(sn, 2);
				sn++;
			}
		}
		return res;
	}

///*** No.55
    bool canJump(vector<int>& nums) {
		// 从最后一个往前走，找到最远可以走到这里的位置
		// 然后来到这个位置继续往前面走，直到到达第一个元素的位置为止
		int i = nums.size() - 1;
		bool res = true;
		while (i > 0) {
			int count = 1;
			int index = i;
			for (int j = i - 1; j >= 0; --j) {
				if (nums[j] >= count) {
					index = j;
				}
				count++;
			}
			if (index == i) {
				res = false;
				break;
			}
			i = index;
		}
		return res;
	}

///*** No.56
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
		std::sort(intervals.begin(), intervals.end());
		// 双指针实现，第二个指针向前遍历，看后面区间的start在不在当前这个区间里面
		// 但是这样对于连续重叠的区间又是有问题的，所以需要更新当前这个合并区间end

		std::vector<std::vector<int>> res;
		for (int i = 0; i < intervals.size();) {
			int j = i+1;
			int t = intervals[i][1];
			while (j < intervals.size() && t >= intervals[j][0]) {
				t = std::max(t, intervals[j][1]);
				j++;
			}
			// 这样出来的就是一个合并的数组
			res.push_back({ intervals[i][0], t });
			i = j;
		}
		return res;
	}

///*** No.57
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		// std::sort(intervals.begin(), intervals.end());

		// 双指针实现，第二个指针向前遍历，看后面区间的start在不在当前这个区间里面
		// 但是这样对于连续重叠的区间又是有问题的，所以需要更新当前这个合并区间end
		int i = 0;
		int Size = intervals.size();
		for (; i < Size; i++) {
			if (intervals[i][0] > newInterval[0]) {
				intervals.insert(intervals.begin() + i, newInterval);
				break;
			}
		}
		if (i == Size) {
			intervals.push_back(newInterval);
		}
		Size++;

		std::vector<std::vector<int>> res;
		for (int i = 0; i < Size;) {
			int j = i+1;
			int t = intervals[i][1];
			while (j < Size && t >= intervals[j][0]) {
				t = std::max(t, intervals[j][1]);
				j++;
			}
			// 这样出来的就是一个合并的数组
			res.push_back({ intervals[i][0], t });
			i = j;
		}
		return res;
	}

///*** No.59
    vector<vector<int>> generateMatrix(int n) {
		std::vector<std::vector<int>> res;
		int startNum = 1;
		for (int i = 0; i < n; i++) {
			std::vector<int> item;
			for (int j = 0; j < n; j++) {
				item.push_back(0);
			}
			res.push_back(item);
		}
		// 横正 → 竖正 → 横逆 → 竖逆
		int hz = 0;
		int hn = res.size() - 1;
		int sz = res[0].size() - 1;
		int sn = 0;
		
		std::function<void(int, int)> heng = [&](int x, int isZheng) {
			if (isZheng == 1) {
				// 正向
				for (int i = 0; i < res[0].size(); i++) {
					if (res[x][i] == 0) {
						res[x][i] = startNum++;
					}
				}
			}
			else {
				for (int i = res[0].size() - 1; i >= 0; i--) {
					if (res[x][i] == 0) {
						res[x][i] = startNum++;
					}
				}
			}
		};

		std::function<void(int, int)> shu = [&](int y, int isZheng) {
			if (isZheng == 1) {
				// 正向
				for (int i = 0; i < res.size(); i++) {
					if (res[i][y] == 0) {
						res[i][y] = startNum++;
					}
				}
			}
			else {
				for (int i = res.size() - 1; i >= 0; i--) {
					if (res[i][y] == 0) {
						res[i][y] = startNum++;
					}
				}
			}
		};
		
		while (hz <= hn) {
			if (hz < res.size()) {
				heng(hz, 1);
				hz++;
			}
			if (sz >= 0) {
				shu(sz, 1);
				sz--;
			}
			if (hn >= 0) {
				heng( hn, 2);
				hn--;
			}
			if (sn < res[0].size()) {
				shu(sn, 2);
				sn++;
			}
		}
		return res;
	}

///*** No.61
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL)return NULL;
		// 先把所有的值提出来，然后将它们
		std::vector<int> arr;
		ListNode* p = head, *q = NULL;
		while (p) {
			arr.push_back(p->val);
			p = p->next;
		}
		p = q = head;
		k = k % arr.size();
		// 将q向前移动k个位置
		while (k--) {
			q = q->next;
		}
		for (int i = 0; i < arr.size(); i++) {
			if (q != NULL) {
				q->val = arr[i];
				q = q->next;
			}
			else {
				p->val = arr[i];
				p = p->next;
			}
		}
		return head;
	}

///*** No.62
    int uniquePaths(int m, int n) {
		// 想法一：回溯加剪枝
		// 想法二：动态规划
		// lu[i][j] = lu[i-1][j] + lu[i][j-1]
		// 我们知道的是 lu[0][1] = lu[1][0] = 1
		// 直接每一行横着求就完事了
		std::vector<std::vector<int>> res;
		for (int i = 0; i < m; i++) {
			std::vector<int> item;
			for (int j = 0; j < n; j++) {
				item.push_back(1);
			}
			res.push_back(item);
		}
		for (int i = 1; i < res.size(); ++i) {
			for (int j = 1; j < res[0].size(); ++j) {
				res[i][j] = res[i - 1][j] + res[i][j - 1];
			}
		}
		return res[m - 1][n - 1];
	}

///*** No.63
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // 只需要将有石头的地方路径变为0
        if(obstacleGrid[0][0]==1)return 0;
		int x = 1;
		for (int i = 0; i < obstacleGrid[0].size(); i++) {
			if (obstacleGrid[0][i] == 1) {
				x = 0;
			}
			obstacleGrid[0][i] = x;
		}
		x = 1;
		for (int i = 1; i < obstacleGrid.size(); i++) {
			if (obstacleGrid[i][0] == 1) {
				x = 0;
			}
			obstacleGrid[i][0] = x;
		}

		for (int i = 1; i < obstacleGrid.size(); i++) {
			for (int j = 1; j < obstacleGrid[0].size(); j++) {
				if (obstacleGrid[i][j] == 1) {
					obstacleGrid[i][j] = 0;
				}
				else {
					obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
				}
			}
		}
		return obstacleGrid[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
	}

///*** No.64
	int minPathSum(vector<vector<int>>& grid) {
        // 思想就是，让每一个位置过来的数字总和都是最小的
		for (int i = 1; i < grid[0].size(); i++) {
			grid[0][i] += grid[0][i - 1];
		}
		for (int i = 1; i < grid.size(); i++) {
			grid[i][0] += grid[i - 1][0];
		}
		for (int i = 1; i < grid.size(); i++) {
			for (int j = 1; j < grid[0].size(); j++) {
				int temp1 = grid[i][j] + grid[i - 1][j];
				int temp2 = grid[i][j] + grid[i][j - 1];
				if (temp1 < temp2) {
					grid[i][j] = temp1;
				}
				else {
					grid[i][j] = temp2;
				}
			}
		}

		return grid[grid.size() - 1][grid[0].size() - 1];
	}

///*** No.71
	string simplifyPath(string path) {
		path += '/';
		std::vector<std::string> stack;
		int i = 0;
		std::string item;
		for (int i = 0; i < path.size(); i++) {
			if (path[i] == '/') {
				// 这个时候就需要处理了
				std::string temp = item;
				item.clear();
				if (temp == "" || temp == ".")continue;
				if (temp == "..") {
					// 把前一个出栈
					if (stack.size() != 0) {
						stack.pop_back();
					}
					continue;
				}
				stack.push_back(temp);
				continue;
			}
			item += path[i];
		}

		path.clear();
		if (stack.size() == 0) {
			path = "/";
		}
		else {


			for (auto it : stack) {
				path = path + "/" + it;
				// std::cout << it << std::endl;
			}
		}

		return path;
	}

///*** No.72
	int minDistance(string word1, string word2) {
        // 详细讲解：https://www.hello-algo.com/chapter_dynamic_programming/edit_distance_problem/#2
		// 先创建二维dp数组
		std::vector<std::vector<int>> dp(word1.size() + 1, std::vector<int>(word2.size() + 1, 0));
		for (int i = 1; i < dp.size(); ++i) {
			dp[i][0] = i;
		}
		for (int i = 1; i < dp[0].size(); ++i) {
			dp[0][i] = i;
		}

		for (int i = 1; i < dp.size(); ++i) {
			for (int j = 1; j < dp[0].size(); ++j) {
				if (word1[i - 1] == word2[j - 1]) {
					// 两个相等的话，直接等于dp[i-1][j-1]
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
				}
			}
		}

		/*for (auto item : dp) {
			for (auto it : item) {
				std::cout << it << " ";
			}
			std::cout << std::endl;
		}*/

		return dp[dp.size() - 1][dp[0].size() - 1];
	}

///*** No.73
	void setZeroes(vector<vector<int>>& matrix) {
		// 两个set保存0所在的横坐标和纵坐标
		std::set<int> hengSet;
		std::set<int> shuSet;

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if (matrix[i][j] == 0) {
					hengSet.insert(i);
					shuSet.insert(j);
				}
			}
		}
		// 把横向的变成0
		for (auto it = hengSet.begin(); it != hengSet.end(); it++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				matrix[*it][j] = 0;
			}
		}

		for (auto it = shuSet.begin(); it != shuSet.end(); it++) {
			for (int j = 0; j < matrix.size(); j++) {
				matrix[j][*it] = 0;
			}
		}
	}

///*** No.74
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		// 在第一排竖着二分
		// 然后在找到的那一排进行横向二分
		int l = 0, r = matrix.size() - 1;
		int hmid;
		while (l <= r) {
			hmid = ((r - l) / 2) + l;
			if (matrix[hmid][0] > target) {
				// 要把r往前移动
				r = hmid - 1;
			}
			else if (matrix[hmid][0] < target) {
				// 要把l往后移动
				l = hmid + 1;
			}
			else {
				return true;
			}
		}
		// 确定target的大致位置，有可能当前hmid的位置要比target大，如果大的话就看上一行（因为这一行都没有可能了，第一个是最小的）
		if (matrix[hmid][0] > target) {
			hmid--;
		}
		// 这时有可能hmid的值是不合法的需要判断一下
		if (hmid < 0) {
			return false;
		}

		l = 0;
		r = matrix[hmid].size() - 1;
		while (l <= r) {
			int mid = ((r - l) / 2) + l;
			if (matrix[hmid][mid] > target) {
				// 要把r往前移动
				r = mid - 1;
			}
			else if (matrix[hmid][mid] < target) {
				// 要把l往后移动
				l = mid + 1;
			}
			else
				return true;
		}
		return false;
	}

///*** No.75
	void sortColors(vector<int>& nums) {
		// 让前面的都是0，后面的都是2，中间的不需要管就可以了
		int zeroIndex = 0;
		int i = 0;
		int  twoIndex = nums.size() - 1;
		while (i <= twoIndex) {
			if (nums[i] == 0) {
				// 把0交换过去
				std::swap(nums[i++], nums[zeroIndex++]);
				// 这个换过来的i为什么不用管，就可以直接往前面走，
				// 这是因为i一定是>=  zeroIndex的，来到这里地方我们前面的东西都是判断过的，要不是0要不就是1所以不用管可以直接将i向前移动
			}
			else if (nums[i] == 1) {
				// 1在中间不用动
				i++;
			}
			else {
				std::swap(nums[i], nums[twoIndex--]);
				// 这里的i不能移动，是因为我们从后面换过来的东西还没进行判断，也就是不知道它是什么所以需要在判断一次i位置上的元素
			}
		}
	}

///*** No.77
	vector<vector<int>> combine(int n, int k) {
		// 回溯求解，满足个数就放到解决数组中
		vector<vector<int>> res;
		std::function<void(std::vector<int>&, int)> dfs = [&](std::vector<int>& item, int num) {
			item.push_back(num);
			if (item.size() == k) {
				res.push_back(item);
				return;
			}

			for (int i = num + 1; i <= n; i++) {
				dfs(item, i);
				item.pop_back();
			}
		};
		
		for (int i = 1; i <= n; i++) {
			std::vector<int> item;
			dfs(item, i);
		}
		return res;
	}

///*** No.78
	vector<int> t;
	vector<vector<int>> ans;

	void dfs(int cur, vector<int>& nums) {
		if (cur == nums.size()) {
			ans.push_back(t);
			return;
		}
		t.push_back(nums[cur]);
		dfs(cur + 1, nums);
		t.pop_back();
		dfs(cur + 1, nums);
	}

	vector<vector<int>> subsets(vector<int>& nums) {
		dfs(0, nums);
		return ans;
	}

///*** No.79
	bool exist(vector<vector<char>>& board, string word) {
		struct Board
		{
			char val;
			bool isUse;
			Board(char v)
				: val(v)
				, isUse(false)
			{}
		};

		std::vector<std::vector<Board>> arr;
		for (int i = 0; i < board.size(); i++) {
			std::vector<Board> item;
			for (int j = 0; j < board[i].size(); ++j) {
				item.push_back(board[i][j]);
			}
			arr.push_back(item);
		}


		std::function<bool(int, int, int)> dfs = [&](int x, int y, int index)->bool {
			if (index == word.size() - 1 && arr[x][y].val == word[index])return true;
			if (index >= word.size())return true;
			if (arr[x][y].val != word[index])return false;

			bool ret = false;
			if (x - 1 >= 0 && arr[x - 1][y].isUse == false) {
				arr[x - 1][y].isUse = true;
				ret = dfs(x - 1, y, index + 1);
				arr[x - 1][y].isUse = false;
				if (ret)return ret;
			}
			if (x + 1 < arr.size() && arr[x + 1][y].isUse == false) {
				arr[x + 1][y].isUse = true;
				ret = dfs(x + 1, y, index + 1);
				arr[x + 1][y].isUse = false;
				if (ret)return ret;
			}
			if (y - 1 >= 0 && arr[x][y - 1].isUse == false) {
				arr[x][y - 1].isUse = true;
				ret = dfs(x, y - 1, index + 1);
				arr[x][y - 1].isUse = false;
				if (ret)return ret;
			}
			if (y + 1 < arr[0].size() && arr[x][y + 1].isUse == false) {
				arr[x][y + 1].isUse = true;
				ret = dfs(x, y + 1, index + 1);
				arr[x][y + 1].isUse = false;
				if (ret)return ret;
			}
			return ret;
		};

		bool ret = false;
		for (int i = 0; i < arr.size(); ++i) {
			for (int j = 0; j < arr[i].size(); ++j) {
				if (arr[i][j].val == word[0]) {
					arr[i][j].isUse = true;
					ret = dfs(i, j, 0);
					arr[i][j].isUse = false;
					if (ret)return ret;
				}
			}
		}
		return ret;
	}

///*** No.80
	int removeDuplicates(vector<int>& nums) {
		// 如果两个一样，就把第一个指针停在两个一样的后面
		if (nums.size() < 3)return nums.size();
		int cnt = 1;  // 计数（计一样的个数）
		int l = 2, r = 1;
		while (r < nums.size()) {
			if (nums[r] == nums[r - 1]) {
				// 相等的话就cnt++
				++cnt;
			}
			else {
				cnt = 1;
			}
			if (cnt <= 2 && r>=l) { // 为什么有r==l ,如果cnt小于等于2那就证明r可以往前移动了这个地方的值是合理的不需要覆盖了
				nums[l++] = nums[r];
			}
			r++;
		}
		return l;
	}

///*** No.81
	bool search(vector<int>& nums, int target) {
		std::function<bool(std::vector<int>& arr, int, int, int)> binarySearch = [&](std::vector<int>& arr, int  begin, int end, int target) {
			int l = begin;
			int r = end;
			while (l <= r) {
				int mid = (r - l) / 2 + l;
				if (arr[mid] > target) {
					r = mid - 1;
				}
				else if (arr[mid] < target) {
					l = mid + 1;
				}
				else
					return true;
			}
			return false;
		};

		// 分为2部分进行二分查找
		int i = 0;
		for (; i < nums.size() - 1; i++) {
			if (nums[i] > nums[i + 1]) {
				// 这个i就是分界点
				break;
			}
		}
		if (true != binarySearch(nums, 0, i, target)) {
			return binarySearch(nums, i + 1, nums.size() - 1, target);
		}
		return true;
	}

///*** No.82
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == NULL || head->next == NULL)return head;
		// 先找到第一个不是重复元素的位置，将他赋值给head
		ListNode* resHead = NULL;
		ListNode* p = head, * q = NULL;
		while (p != NULL) {
			if (p->next != NULL && p->val == p->next->val) {
				// 特殊处理
				while (p->next != NULL && p->val == p->next->val) {
					p = p->next;
				}
			}
			else {
				resHead = p;
				break;
			}
			p = p->next;
		}
		if (resHead == NULL || resHead->next == NULL)return resHead;
		// 已经找到了第一个不重复的开头
		p = resHead;
		q = resHead->next;
		while (q != NULL) {
			if (q->next != NULL && q->val == q->next->val) {
				// 需要进行处理
				// 在这里需要找到第一个不是重复元素的位置
				do {
					// 就要继续往下面搜了
					int temp = q->val;
					while (q != NULL && q->val == temp) {
						q = q->next;
					}
					// q的val不等于temp
					if (q == NULL || q->next == NULL)break;
				} while (q->val == q->next->val); // 看看是不是进入了下一个重复项
			    // 出来的一定是不重复的
				p->next = q;
			}
			p = q; // p要跳到最后一个不重复的位置
			if (p == NULL)
				break;
			q = q->next;
		}
		return resHead;
	}

///*** No.86
	ListNode* partition(ListNode* head, int x) {
		if (head == NULL || head->next == NULL)return head;
		// 如果当前指针所在位置的值大于等于x，就向后找看后面还有没有比x小的值
		// 有则交换，否则结束
		// 但是要保留相对位置
		// 方法二：
		// 创造两个数组，保存小于x和大于等于x的数据
        // 方法三：
        // 新建两个列表，一个存放小于x另一个存放大于等于x的值，然后将这两个链表进行尾首拼接即可
		std::vector<int> lArr;
		std::vector<int> rArr;
		ListNode* p = head;
		while (p != NULL) {
			if (p->val < x) {
				lArr.push_back(p->val);
			}
			else {
				rArr.push_back(p->val);
			}
			p = p->next;
		}
		p = head;
		for (int i = 0; i < lArr.size(); i++) {
			p->val = lArr[i];
			p = p->next;
		}
		for (int i = 0; i < rArr.size(); i++) {
			p->val = rArr[i];
			p = p->next;
		}
		return head;
	}

///*** No.89
	vector<int> grayCode(int n) {
		// 2^n  == 1 << n
		// 公式：第n个格雷码G(n) = n xor (n >> 1)
		// 方法二（动态规划）：
		// G(n+1) =  G(n) + G(n)的倒叙并且在前面|上1
		//  首先你是知道0和1符合要求的格雷码的，在其基础上进行倒叙输出，这就意味着后半部分也满足了相差一位的特点
		//  然后在前面添1，使得对接部分的数据也满足了要求，并且最后一个元素和第一个元素也只相差了一位
		std::vector<int> res = {0};
		int head = 1;  // 这时要在倒叙前面添加的1
		for (int i = 0; i < n; i++) {
			for (int j = res.size() - 1; j >= 0; --j) {
				res.push_back(head | res[j]);
			}
			head <<= 1;
		}
		return res;
	}

///*** No.90
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		// 0 1 2 3 4 5 6 7
		int size = nums.size();
		std::vector<std::vector<int>> res;
		std::set<std::vector<int>> arr;
		for (int i = 0; i < (1 << size); ++i) {
			std::vector<int> item;
			for (int j = 1; j <= size; ++j) {
				if (i & (1 << size - j)) {
					item.push_back(nums[j - 1]);
				}
				//std::cout << (1 << nums.size() - j) << " ";
			}
			std::sort(item.begin(), item.end());
			arr.insert(item);
			//std::cout << std::endl;
		}

		for (auto it : arr) {
			res.push_back(it);
		}
		return res;
	}

///*** No.91
	int numDecodings(string s) {
		// 分为单的
		//   和多的
		// 初始，单 = 1、多 = 0
		// next，单 = 单 + 多、多 = 能合并吗 ？ 等于上次的单 ：等于0
		// 最后结果为：单 + 多
		int dan = 0;
		int duo = 0;
		if (s[0] != '0') {
			dan = 1;
		}
		for (int i = 1; i < s.size(); ++i) {
			int tempDan = dan;
			int tempDuo = duo;
			dan = 0;
			duo = 0;
			if (s[i] != '0')
				dan = tempDan + tempDuo;
            if(s[i - 1] != '0' && s[i - 1] <= '2') {
                if(s[i - 1]=='2' && s[i] > '6')
                    continue;
                duo = tempDan;
            }
		}
		return dan + duo;
	}

///*** No.92
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		if (right == left)return head;
		// 两个指针都到起始的位置
		ListNode* p = head;
		// 第一个元素和最后一个元素的位置记录一下
		for (int i = 1; i < left; ++i) {
			p = p->next;
		}
		ListNode* temp = p;
		std::vector<int> arr;
		for (int i = 0; i <= right - left; ++i) {
			arr.push_back(temp->val);
			temp = temp->next;
		}
		for (int i = arr.size() - 1; i >= 0; --i) {
			p->val = arr[i];
			p = p->next;
		}
		return head;
	}

///*** No.93
	vector<string> restoreIpAddresses(string s) {
		// 递归，回溯
		// 地址为1位、2位、3位，满足条件加入结果集

		std::vector<std::string> ip;   // 要判断的ip字段
		std::vector<std::string> res;  // 结果集

		std::function<void(int startIndex, int len)> dfs =
			[&](int startIndex, int len) {
			if (ip.size() == 4) {
				if (s.size() == startIndex && len == 1) {
					// 加入到结果集中，并返回
					std::string subRes;
					for (int i = 0; i < 4; i++) {
						subRes += ip[i];
						if (i != 3)
							subRes += '.';
					}
					res.push_back(subRes);
				}
				//ip.pop_back();
				return;
			}
			if ((startIndex + len > s.size()) || (s[startIndex] == '0' && len > 1))
				return;
			if (len == 3) {
				// 有三个数
				if (s[startIndex] > '2') {
					return;
				}
				if (s[startIndex] == '2') {
					if (
						(s[startIndex + 1] > '5') ||
						(s[startIndex + 1] == '5' && s[startIndex + 2] > '5')
						)
						return;
				}
			}
			ip.push_back(std::string(s.begin() + startIndex, s.begin() + startIndex + len));

			//  从len之后开始继续加入递归
			for (int i = 1; i <= 3; i++) {
				dfs(startIndex + len, i);
			}
			ip.pop_back();
		};

		if (s.size() > 3) {
			std::vector<std::string> ip;
			for (int i = 1; i <= 3; i++) {
				dfs(0, i);
			}
		}
		return res;
	}

///*** No.95
	vector<TreeNode*> generateTrees(int n) {
		// 从start和end中选取一个数字i当做根节点，然后建立它的左子树和右子树
		// 建立左子树和右子树也是同样的方式，然后把所有可行的左子树和右子树选出一棵来凭借成我们最后的搜索二叉树
		std::function<std::vector<TreeNode*>(int, int)> dfs = [&](int start, int end)->std::vector<TreeNode*> {
			if (start > end)
				return { nullptr };
			// 所有可行的搜索二叉树
			std::vector<TreeNode*> allTrees;
			for (int i = start; i <= end; ++i) {
				std::vector<TreeNode*> leftTree = dfs(start, i - 1); // 递归获取所有可行的左子树
				std::vector<TreeNode*> rightTree = dfs(i + 1, end);  // 递归获取所有可行的左子树
				for (auto ln : leftTree) {
					for (auto rn : rightTree) {
						TreeNode* allTree = new TreeNode(i);
						allTree->left = ln;
						allTree->right = rn;
						allTrees.emplace_back(allTree);
					}
				}

			}
			return allTrees;
		};

		if (n == 0)return { nullptr };
		return dfs(1, n);
	}

///*** No.96
	int numTrees(int n) {
		// README中有图解
        std::vector<int> arr(n + 1);
        arr[0] = 1;
        arr[1] = 1;
        for(int i = 2; i <= n; ++i){
            for(int j = 1; j <= i; ++j){
                arr[i] += arr[j - 1] * arr[i - j];
            }
        }
        return arr[n];
    }

///*** No.97
	bool isInterleave(string s1, string s2, string s3) {
		int m = s1.size();
		int n = s2.size();
		if (m + n != s3.size())return false;
		std::vector<std::vector<bool>> arr(n+1);
		for (int i = 0; i <= n; i++) {
			arr[i] = std::vector<bool>(m + 1, 0);
		}
		// 先将第一排的横竖两行进行初始化
		arr[0][0] = true;
		for (int i = 1; i < arr[0].size() && s3[i - 1] == s1[i - 1]; ++i) {
			arr[0][i] = true;
		}
		for (int i = 1; i < arr.size() && s3[i - 1] == s2[i - 1]; ++i) {
			arr[i][0] = true;
		}

		for (int i = 1; i < arr.size(); ++i) {
			for (int j = 1; j < arr[i].size(); ++j) {
				arr[i][j] = (arr[i - 1][j] && s3[i + j - 1] == s2[i - 1]) || (arr[i][j - 1] && s3[i + j - 1] == s1[j - 1]);
			}
		}
		return arr[n][m];
	}

///*** No.98
	bool isValidBST(TreeNode* root) {
		// 对于一颗二叉搜索树来说，中序遍历是升序排列的
		// 怎么检测一个数组是否是有序的呢
		std::vector<int> nodeList;
		std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
			if (node == NULL)
				return;
			inorderTraversal(node->left);
			nodeList.push_back(node->val);
			inorderTraversal(node->right);
		};
		
		inorderTraversal(root);

		for (int i = 0; i < nodeList.size() - 1; ++i) {
			if (nodeList[i] >= nodeList[i + 1]) {
				return false;
			}
		}
		return true;
	}

///*** No.99
	void recoverTree(TreeNode* root) {
        // 二叉搜索树，中序遍历的元素数组是升序的
        // 所以可以全部读出来，然后排序在放回去
        std::vector<int> arr;
        std::vector<TreeNode*> NodeList;

        std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node){
            if(node == NULL)return;
            inorderTraversal(node->left);
            arr.push_back(node->val);
            NodeList.push_back(node);
            inorderTraversal(node->right);
        };

        inorderTraversal(root);

        std::sort(arr.begin(), arr.end());

        for(int i=0;i<NodeList.size();++i){
            NodeList[i]->val = arr[i];
        }
    }
};