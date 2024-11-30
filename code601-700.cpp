class Solution
{
public:
///*** No.661
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
		std::vector<std::vector<int>> res = img;

		// (x, y) + (x+1, y) + (x-1, y) + (x, y+1) + (x, y-1) + (x-1, y-1) + (x+1, y-1) + (x-1, y+1) + (x+1, y+1)
		for (int x = 0; x < img.size(); ++x) {
			for (int y = 0; y < img[x].size(); ++y) {

				int sum = 0;
				int count = 0;
				for (int i = x - 1; i <= x + 1; ++i) {
					if (i >= img.size() || i < 0)
						continue;
					for (int j = y - 1; j <= y + 1; ++j) {
						if (j >= img[x].size() || j < 0)
							continue;
						sum += img[i][j];
						++count;
					}
				}

				res[x][y] = (int)floor(sum / (count * 1.0));
			}
		}
		return res;
	}
};