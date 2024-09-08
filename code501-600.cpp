class Solution
{
public:
///*** No.509
	int fib(int n)
	{
		if (n <= 0)
			return 0;
		if (n == 1 || n == 2)
			return 1;
		int n1 = 1, n2 = 1, temp;
		for (int i = 3; i <= n; i++)
		{
			temp = n1 + n2; // **如果题目要求取余，就在这取余，不要在最后取余会溢出**
			n1 = n2;
			n2 = temp;
		}
		return temp;
	}
};