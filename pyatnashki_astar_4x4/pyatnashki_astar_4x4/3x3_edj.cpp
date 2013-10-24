#include<iostream>
#include <queue>
#include <set>
#include <math.h>
#include <list>
#include <string>
#include<map>
#define FSIZE 9
#define SSIZE 3
#define RIGHT 123456780
using namespace std;
class State
{
public:
	size_t field_[FSIZE];
    size_t dist_;
    size_t step_;
    size_t null_index_;
	size_t field_int_;
    State(size_t* f, size_t f_i, size_t d, size_t s, size_t i) : field_int_(f_i), dist_(d), step_(s), null_index_(i) {
		for(int i = 0; i < FSIZE; ++i) {
			field_[i] = f[i];
		}
	}
	size_t countDistance(){
		size_t res=0;
		for(int i = 0; i < FSIZE; ++i) {
			if(field_[i] != 0)
				res += abs(int(i / SSIZE) - int((field_[i] - 1) / SSIZE)) + abs(int(i % SSIZE) - int((field_[i] - 1) % SSIZE));
		}
		return res;
	}
};

class MyHashTable
{
public:
    vector<list<size_t> > table_;
    size_t size_;
    size_t capacity_;
    size_t hash(size_t x) 
    {
		  return x%92475 + x/92475;
    }

    MyHashTable() { table_.resize(130000); size_ = 130000; capacity_ = 0; }

	bool check(size_t x) {
		size_t index = hash(x);
        if (table_[index].empty()) 
        { 
            return true; 
        } else {
            for (list<size_t>::iterator it = table_[index].begin(); it != table_[index].end(); ++it)
                if (*it == x)
                    return false;
        }
		return true;
    }

    bool insert(size_t x)
    {
        size_t index = hash(x);
        if (table_[index].empty()) 
        { 
			table_[index].push_front(x);
            ++capacity_;
            return true; 
        } else {
            for (list<size_t>::iterator it = table_[index].begin(); it != table_[index].end(); ++it)
                if (*it == x)
                    return false;
            table_[index].push_back(x);
            ++capacity_;
        }
        return true;
    }
};

size_t toInt(State& s) {
	size_t res = 0;
	for(int i = 0; i < FSIZE; ++i) {
		res = res*10 + s.field_[i];
	}
	return res;
}

//class QueueComparator
//{
//public:
//    bool operator()(const State& s1, const State& s2) const { return s1.dist_ > s2.dist_; }
//};
class SetComparator
{
public:
	bool operator()(const State& s1, const State& s2) const { if(s1.dist_ != s2.dist_) return (s1.dist_ < s2.dist_); else return s1.field_int_ < s2.field_int_;}
};
class MapComparator
{
public:
	bool operator()(const State& s1, const State& s2) const {return s1.field_int_ < s2.field_int_;}
};
//priority_queue<State, vector<State>, QueueComparator> pr_queue;
set<State, SetComparator> pr_queue;
map<size_t, size_t> state_step;
MyHashTable used;

size_t addNeighbours(State& s)
{    
	size_t news_int;
    size_t newDist;
    if (s.null_index_+SSIZE < FSIZE)
    {
        newDist = s.dist_ + 1;
        if ((s.field_[s.null_index_+SSIZE] - 1) / SSIZE <= s.null_index_ / SSIZE)
            --newDist;
        else
			++newDist;
		//cout << newDist<<endl;
		 /*if (s.field_[s.null_index_+SSIZE] == s.null_index_+SSIZE+1)
            ++newDist;
        else 
            if (s.field_[s.null_index_+SSIZE] == s.null_index_+1)
                --newDist;*/
		swap(s.field_[s.null_index_+SSIZE], s.field_[s.null_index_]);
		State news(s.field_, 0, newDist, s.step_+1, s.null_index_+SSIZE);
		news_int = toInt(news);
		news.field_int_ = news_int;
		if (used.check(news_int)) {
			//if(s.step_ == 22) { cout << news.field_[1]<< " " <<news.field_[0]<< " " <<news.field_[1]<< " " <<news.field_[2]<< " " <<news.field_[3]<< " " <<news.field_[4]<< " " <<news.field_[5]<< " " <<news.field_[6]<< " " <<news.field_[7]<< " " <<news.field_[8]<<endl;}
			map<size_t,size_t>::iterator it = state_step.find(news_int);
			if(it == state_step.end()) {
				pr_queue.insert(news);
				state_step.insert(make_pair(news_int, s.step_+1));
			} else {
				//cout << "ahah" << endl;
				if(it->second > s.step_ + 1) {
					//cout << "ahah" << endl;
					news.dist_ -= it->second - s.step_ - 1;
					pr_queue.erase(news);
					news.dist_ = newDist;
					pr_queue.insert(news);
					state_step.erase(it);
					state_step.insert(make_pair(news_int, s.step_+1));
				}
			}
		}
        if (news_int == RIGHT) {
			//cout << "ert" << s.field_int_ << endl;
            return news.step_;
		}
        swap(s.field_[s.null_index_+SSIZE], s.field_[s.null_index_]);
    }

    if (s.null_index_ > SSIZE-1)
	{
        newDist = s.dist_ + 1;
        if ((s.field_[s.null_index_-SSIZE] - 1) / SSIZE >= s.null_index_ / SSIZE)
            --newDist;
        else 
			++newDist;
		//cout << newDist<<endl;
		/*if (s.field_[s.null_index_-SSIZE] == s.null_index_-SSIZE+1)
            ++newDist;
        else 
            if (s.field_[s.null_index_-SSIZE] == s.null_index_+1)
                --newDist;*/
        swap(s.field_[s.null_index_-SSIZE], s.field_[s.null_index_]);
		State news(s.field_, 0, newDist, s.step_+1,  s.null_index_-SSIZE);
		news_int = toInt(news);
		news.field_int_ = news_int;
		if (used.check(news_int)) {
			//if(s.step_ == 22) { cout << news.field_[1]<< " " <<news.field_[0]<< " " <<news.field_[1]<< " " <<news.field_[2]<< " " <<news.field_[3]<< " " <<news.field_[4]<< " " <<news.field_[5]<< " " <<news.field_[6]<< " " <<news.field_[7]<< " " <<news.field_[8]<<endl;}
			map<size_t,size_t>::iterator it = state_step.find(news_int);
			if(it == state_step.end()) {
				pr_queue.insert(news);
				state_step.insert(make_pair(news_int, s.step_+1));
			} else {
				//cout << "ahah" << endl;
				if(it->second > s.step_ + 1) {
					//cout << "ahah" << endl;
					news.dist_ -= it->second - s.step_ - 1;
					pr_queue.erase(news);
					news.dist_ = newDist;
					pr_queue.insert(news);
					state_step.erase(it);
					state_step.insert(make_pair(news_int, s.step_+1));
				}
			}
		}
        if (news_int == RIGHT) {
			//cout << "ert" << s.field_int_ << endl;
            return news.step_;
		}
        swap(s.field_[s.null_index_-SSIZE], s.field_[s.null_index_]);
    }

    if ((s.null_index_ + 1) % SSIZE != 0)
    {
        newDist = s.dist_ + 1;
        if ((s.field_[s.null_index_+1] - 1) % SSIZE <= s.null_index_ % SSIZE)
            --newDist;
        else 
           ++newDist;
		//cout << newDist<<endl;
		/*if (s.field_[s.null_index_+1] == s.null_index_+SSIZE-1)
            ++newDist;
        else 
            if (s.field_[s.null_index_+1] == s.null_index_+1)
                --newDist;*/
		swap(s.field_[s.null_index_+1], s.field_[s.null_index_]);
		State news(s.field_, 0, newDist, s.step_+1, s.null_index_+1);
		news_int = toInt(news);
		news.field_int_ = news_int;
		if (used.check(news_int)) {
			//if(s.step_ == 22) { cout << news.field_[1]<< " " <<news.field_[0]<< " " <<news.field_[1]<< " " <<news.field_[2]<< " " <<news.field_[3]<< " " <<news.field_[4]<< " " <<news.field_[5]<< " " <<news.field_[6]<< " " <<news.field_[7]<< " " <<news.field_[8]<<endl;}
			map<size_t,size_t>::iterator it = state_step.find(news_int);
			if(it == state_step.end()) {
				pr_queue.insert(news);
				state_step.insert(make_pair(news_int, s.step_+1));
			} else {
				//cout << "ahah" << endl;
				if(it->second > s.step_ + 1) {
					//cout << "ahah" << endl;
					news.dist_ -= it->second - s.step_ - 1;
					pr_queue.erase(news);
					news.dist_ = newDist;
					pr_queue.insert(news);
					state_step.erase(it);
					state_step.insert(make_pair(news_int, s.step_+1));
				}
			}
		}
        if (news_int == RIGHT) {
			//cout << "e" << s.field_int_ << " " << s.step_ << " " << s.dist_ << endl;
            return news.step_;
		}
        swap(s.field_[s.null_index_+1], s.field_[s.null_index_]);
	}

    if ((s.null_index_) % SSIZE != 0)
    {
        newDist = s.dist_ + 1;
        if ((s.field_[s.null_index_-1] - 1) % SSIZE >= s.null_index_ % SSIZE)
            --newDist;
        else 
			++newDist;
		//cout << newDist<<endl;
		/*if (s.field_[s.null_index_-1] == s.null_index_)
            ++newDist;
        else 
            if (s.field_[s.null_index_-1] == s.null_index_+1)
                --newDist;*/
		swap(s.field_[s.null_index_-1], s.field_[s.null_index_]);
		State news(s.field_, 0, newDist, s.step_+1, s.null_index_-1);
		news_int = toInt(news);
		news.field_int_ = news_int;
		if (used.check(news_int)) {
			//if(s.step_ == 22) { cout << news.field_[1]<< " " <<news.field_[0]<< " " <<news.field_[1]<< " " <<news.field_[2]<< " " <<news.field_[3]<< " " <<news.field_[4]<< " " <<news.field_[5]<< " " <<news.field_[6]<< " " <<news.field_[7]<< " " <<news.field_[8]<<endl;}
			map<size_t,size_t>::iterator it = state_step.find(news_int);
			if(it == state_step.end()) {
				pr_queue.insert(news);
				state_step.insert(make_pair(news_int, s.step_+1));
			} else {
				//cout << "ahah" << endl;
				if(it->second > s.step_ + 1) {
					//cout << "ahah" << endl;
					news.dist_ -= it->second - s.step_ - 1;
					pr_queue.erase(news);
					news.dist_ = newDist;
					pr_queue.insert(news);
					state_step.erase(it);
					state_step.insert(make_pair(news_int, s.step_+1));
				}
			}
		}
        if (news_int == RIGHT) {
			//cout << "er" << s.field_int_ << endl;
            return news.step_;
		}
        swap(s.field_[s.null_index_-1], s.field_[s.null_index_]);
    }

	used.insert(s.field_int_);
    return 0;
}

size_t Astar()
{
    size_t flag;
    do  
    {
        State s = *(pr_queue.begin());
        pr_queue.erase(pr_queue.begin());
        flag = addNeighbours(s);
        
    } while (flag == 0 && !pr_queue.empty());
    return flag;
}

int main()
{
    size_t st[FSIZE];
    size_t temp;
    size_t ind;
    for (size_t i = 0; i < FSIZE; ++i)
    {
        cin >> temp;
        if (temp == 0) 
            ind = i;
		st[i] = temp;
    }
	State s(st, 0, 0, 0, ind);
	s.dist_ = s.countDistance();
	//cout << s.dist_<<endl;
	size_t q = toInt(s);
    if (q != RIGHT)
    {
		s.field_int_ = q;
        pr_queue.insert(s);
		state_step.insert(make_pair(q, 0));
        size_t result;
		if((result = Astar()) != 0)
			cout << "Yes" << endl << result << endl;
		else
			cout << "No" << endl;
    } else 
        cout << "Yes" << endl << 0 << endl;
	//cout << endl;
	//cout << state_dist.find(123456708)->second << endl;/*
/*	cout << state_dist.find(685013472)->second << endl;//+
	cout << state_dist.find(685103472)->second << endl;
	cout << state_dist.find(685130472)->second << endl;//+
	cout << state_dist.find(680135472)->second << endl;
	cout << state_dist.find(608135472)->second << endl;//+
	cout << state_dist.find(68135472)->second << endl;
	cout << state_dist.find(168035472)->second << endl;
	cout << state_dist.find(168435072)->second << endl;
	cout << state_dist.find(168435702)->second << endl;
	cout << state_dist.find(168435720)->second << endl;
	cout << state_dist.find(168430725)->second << endl;//+
	cout << state_dist.find(160438725)->second << endl;
	cout << state_dist.find(106438725)->second << endl;
	cout << state_dist.find(136408725)->second << endl;
	cout << state_dist.find(136428705)->second << endl;
	cout << state_dist.find(136428750)->second << endl;
	cout << state_dist.find(136420758)->second << endl;
	cout << state_dist.find(130426758)->second << endl;
	cout << state_dist.find(103426758)->second << endl;
	cout << state_dist.find(123406758)->second << endl;
	cout << state_dist.find(123456708)->second << endl;
	cout << state_dist.find(RIGHT)->second << endl;*/
    return 0;
}