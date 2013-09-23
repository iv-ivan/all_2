#include"CurState.h"
#include<iostream>
#include<cmath>

CurState::CurState() {
	std::cout << "Start position (0 for 'empty'): " << std::endl;
	for(int y = 0; y < 4; ++y)
		for(int x = 0; x < 4; ++x) {
			std::cin >> state_[y][x];
			if(state_[y][x] == 0) {
				x_ = x;
				y_ = y;
			}
		}
	max_distance_ = countDistance();
}
bool CurState::checkParity() {
	int sum = 0;
	for(int n = 0; n < 14; ++n)
		if(state_[n / 4] [n % 4] != 0)
			for(int counter = n + 1; counter < 15; ++counter) {
				if((state_[counter / 4] [counter % 4] < state_[n / 4] [n % 4]) && (state_[counter / 4] [counter % 4] != 0))
					++sum;
			}
		else
			sum += n / 4 + 1;
	return bool(sum % 2);
}

int CurState::countDistance() {
	int distance = 0;
	for(int y = 0; y < 4; ++y)
		for(int x = 0; x < 4; ++x) {
			if(state_[y][x] != 0)
				distance += abs((state_[y][x] - 1) / 4 - y) + abs((state_[y][x] - 1) % 4 - x);
			if(state_[y][x] == 0)
				distance += abs(3 - y) + abs(3 - x);
		}
	return distance;
}

CurState::CurState(const CurState& st):path_(st.path_), x_(st.x_), y_(st.y_) {
	for(int y = 0; y < 4; ++y)
		for(int x = 0; x < 4; ++x)
			state_[y][x] = st.state_[y][x];
}

CurState::~CurState() {}

void CurState::solve() {
	if(checkParity() == 1)
		return;
	while(1) {
		path_.clear();
		//int step = 0;
		int temp = search();
		if(temp == -1)
			return;
		max_distance_ = temp;
	}
}
 
int CurState::search() {
	int estimation = path_.size() + countDistance();
	if(estimation > max_distance_) {
		shift(path_[path_.size() - 1]);
		path_.pop_back();
		return estimation;
	}
    if(estimation == path_.size())
		return - 1;
	int min = std::numeric_limits<int>::max();
	int temp;
    temp = goForward();
    if(temp < min)
		min = temp;
	if(temp != -1 && path_.size() > 0) {
		shift(path_[path_.size() - 1]);
		path_.pop_back();
	}
	return min;
}

int CurState::goForward() {
	int t = std::numeric_limits<int>::max(), b = std::numeric_limits<int>::max(), l = std::numeric_limits<int>::max(), r = std::numeric_limits<int>::max();//top bottom left right
	if(y_ > 0 && (path_.size() == 0 || state_[y_ - 1][x_] != path_[path_.size() - 1])) {
		state_[y_][x_] = state_[y_ - 1][x_];
		path_.push_back(state_[y_][x_]);
		state_[y_ - 1][x_] = 0;
		--y_;
		t = search();
	}
	int min = t;
	if(t == -1)
		return -1;
	if(y_ < 3 && (path_.size() == 0 || state_[y_ + 1][x_] != path_[path_.size() - 1])) {
		state_[y_][x_] = state_[y_ + 1][x_];
		path_.push_back(state_[y_][x_]);
		state_[y_ + 1][x_] = 0;
		++y_;
		b = search();
	}
	if(b < min)
		min = b;
	if(b == -1)
		return -1;
	if(x_ > 0  && (path_.size() == 0 || state_[y_][x_ - 1] != path_[path_.size() - 1])) {
		state_[y_][x_] = state_[y_][x_ - 1];
		path_.push_back(state_[y_][x_]);
		state_[y_][x_ - 1] = 0;
		--x_;
		l = search();
	}
	if(l < min)
		min = l;
	if(l == -1)
		return -1;
	if(x_ < 3  && (path_.size() == 0 || state_[y_][x_ + 1] != path_[path_.size() - 1])) {
		state_[y_][x_] = state_[y_][x_ + 1];
		path_.push_back(state_[y_][x_]);
		state_[y_][x_ + 1] = 0;
		++x_;
		r = search();
	}
	if(r < min)
		min = r;
	if(r == -1)
		return -1;
	return min;
}

void CurState::shift(int number) {
	if(x_ > 0 && state_[y_][x_ - 1] == number) {
		state_[y_][x_ - 1] = 0;
		state_[y_][x_] = number;
		--x_;
		return;
	}
	if(x_ < 3 && state_[y_][x_ + 1] == number) {
		state_[y_][x_ + 1] = 0;
		state_[y_][x_] = number;
		++x_;
		return;
	}
	if(y_ > 0 && state_[y_ - 1][x_] == number) {
		state_[y_ - 1][x_] = 0;
		state_[y_][x_] = number;
		--y_;
		return;
	}
	if(y_ < 3 && state_[y_ + 1][x_] == number) {
		state_[y_ + 1][x_] = 0;
		state_[y_][x_] = number;
		++y_;
		return;
	}
}

std::vector<int> CurState::solution() {
	return path_;
}