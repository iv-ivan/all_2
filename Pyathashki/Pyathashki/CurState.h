#ifndef _STATE
#define STATE
#include<vector>
class CurState {
private:
	std::vector<int> path_;
	int state_[4][4];
	int x_;//position of "empty"
	int y_;//
	int max_distance_;
	bool checkParity();
	int countDistance();
	int search();
	int goForward();
	void shift(int number);
public:
	CurState();
	CurState(const CurState& st);
	~CurState();
	void solve();
	std::vector<int> solution();
};
#endif