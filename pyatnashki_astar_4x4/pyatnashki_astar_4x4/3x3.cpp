////#include<iostream>
////#include <queue>
////#include <set>
////#include <math.h>
////#include <list>
////#include <string>
////
////#define FSIZE 9
////#define SSIZE 3
////size_t RIGTH_VARIANT[FSIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '0'};
////
////using namespace std;
////class State
////{
////public:
////	size_t field_[FSIZE];
////    size_t dist_;
////    size_t step_;
////    size_t null_index_;
////	string seq_;
////    State(size_t* f, size_t d, size_t s, size_t i, string str) : dist_(d), step_(s), null_index_(i), seq_(str) {
////		for(int i = 0; i < FSIZE; ++i) {
////			field_[i] = f[i];
////		}
////	}
////};
////
////class MyHashTable
////{
////public:
////    vector<list<size_t> > table_;
////    size_t size_;
////    size_t capacity_;
////    size_t hash(size_t x) 
////    {
////		  return x/92475;
////    }
////
////    MyHashTable() { table_.resize(130337); size_ = 130337; capacity_ = 0; }
////
////    bool insert(size_t x)
////    {
////        size_t index = hash(x);
////        if (table_[index].empty()) 
////        { 
////			table_[index].push_front(x);
////            ++capacity_;
////            return true; 
////        } else {
////            for (list<size_t>::iterator it = table_[index].begin(); it != table_[index].end(); ++it)
////                if (*it == x)
////                    return false;
////            table_[index].push_back(x);
////            ++capacity_;
////        }
////        return true;
////    }
////};
////
////size_t toInt(State& s) {
////	size_t res = 0;
////	for(int i = 0; i < FSIZE; ++i) {
////		res = res*10 + s.field_[i];
////	}
////	return res;
////}
////
////class QueueComparator
////{
////public:
////    bool operator()(const State& s1, const State& s2) const { return s1.dist_ > s2.dist_; }
////};
////
////priority_queue<State, vector<State>, QueueComparator> pr_queue; 
////MyHashTable used;
////
////string addNeighbours(State s)
////{    
////    size_t newDist;
////    if (s.null_index_+SSIZE < FSIZE)
////    {
////        newDist = s.dist_ + 1;
////        if ((s.field_[s.null_index_+SSIZE] - 1) / SSIZE > s.null_index_ / SSIZE)
////            ++newDist;
////        else
////			--newDist;
////		swap(s.field_[s.null_index_+SSIZE], s.field_[s.null_index_]);
////		State news(s.field_, newDist, s.step_+1, s.null_index_+SSIZE, s.seq_+"d");
////		size_t news_int = toInt(news);
////		if (used.insert(news_int))
////            pr_queue.push(news);
////        if (news_int == 123456780)
////            return news.seq_;
////        swap(s.field_[s.null_index_+SSIZE], s.field_[s.null_index_]);
////    }
////
////    if (s.null_index_ > SSIZE-1)
////	{
////        newDist = s.dist_ + 1;
////        if ((s.field_[s.null_index_-SSIZE] - 1) / SSIZE >= s.null_index_ / SSIZE)
////            --newDist;
////        else 
////			++newDist;
////        swap(s.field_[s.null_index_-SSIZE], s.field_[s.null_index_]);
////		State news(s.field_, newDist, s.step_+1,  s.null_index_-SSIZE, s.seq_+"u");
////		size_t news_int = toInt(news);
////		if (used.insert(news_int))
////            pr_queue.push(news);
////        if (news_int == 123456780)
////            return news.seq_;
////        swap(s.field_[s.null_index_-SSIZE], s.field_[s.null_index_]);
////    }
////
////    if ((s.null_index_) % SSIZE != SSIZE - 1)
////    {
////        newDist = s.dist_ + 1;
////        if ((s.field_[s.null_index_+1] - 1) % SSIZE <= s.null_index_ % SSIZE)
////            --newDist;
////        else 
////           ++newDist;
////		swap(s.field_[s.null_index_+1], s.field_[s.null_index_]);
////		State news(s.field_, newDist, s.step_+1, s.null_index_+1, s.seq_+"r");
////		size_t news_int = toInt(news);
////		if (used.insert(news_int))
////            pr_queue.push(news);
////        if (news_int == 123456780)
////            return news.seq_;
////        swap(s.field_[s.null_index_+1], s.field_[s.null_index_]);
////	}
////
////    if ((s.null_index_) % SSIZE != 0)
////    {
////        newDist = s.dist_ + 1;
////        if ((s.field_[s.null_index_-1] - 1) % SSIZE >= s.null_index_ % SSIZE)
////            --newDist;
////        else 
////			++newDist;
////		swap(s.field_[s.null_index_-1], s.field_[s.null_index_]);
////		State news(s.field_,  newDist, s.step_+1, s.null_index_-1, s.seq_+"l");
////		size_t news_int = toInt(news);
////		if (used.insert(news_int))
////            pr_queue.push(news);
////        if (news_int == 123456780)
////            return news.seq_;
////        swap(s.field_[s.null_index_-1], s.field_[s.null_index_]);
////    }
////
////    return "";
////}
////
////string Astar()
////{
////    string flag;
////    do  
////    {
////        State s = pr_queue.top();
////        pr_queue.pop();
////        flag = addNeighbours(s);
////        
////    } while (flag == "" && !pr_queue.empty());
////    return flag;
////}
////
////int main()
////{
////    size_t st[FSIZE];
////    size_t temp;
////    size_t ind;
////    for (size_t i = 0; i < FSIZE; ++i)
////    {
////        cin >> temp;
////        if (temp == 0) 
////            ind = i;
////		st[i] = temp;
////    }
////	State s(st, 0, 0, ind, "");
////    if (toInt(s) != 123456780)
////    {
////        pr_queue.push(s);
////        string result;
////        if ((result = Astar()) != "")
////            cout << "YES" << endl << result;
////        else 
////            printf("NO\n");
////    } else 
////        printf("YES\n 0\");
////    return 0;
////}
//#include <iostream>
//#include <limits.h>
//#include <stdlib.h>
//#include <queue>
//#include <set>
//#include <math.h>
//#include <list>
//
//#define FSIZE 9
//
//using namespace std;
//
//class State
//{
//public:
//    int field;
//    int dist;
//    vector<int> arr;
//    int step;
//    int index;
//    State(int f) { field = f; }
//    State(int f, int d, int s) : field(f), dist(d), step(s) {}
//    State(int f, int d, int s, vector<int>& a, int i) : field(f), dist(d), step(s), arr(a), index(i) {}
//};
//
//class myHashTable
//{
//public:
//    vector<list<int> > table;
//    int size;
//    int capacity;
//    int hash(int s) 
//    {
//        return (s%92475 + s/92475); 
//    }
//    //double load_factor() {    return ((double)capacity)/size < 1.6; }
//   /* void resize()
//    {
//        vector<list<State> > newtable;
//        newtable.resize(size*2);
//        for (int i = 0; i < size; ++i)
//            for (list<State>::iterator it = table[i].begin(); it != table[i].end(); ++it)
//            {
//                int index = hash(*it);
//                newtable[index].push_back(*it);
//            }
//        table = newtable;
//        size *= 2;
//    }*/
//
//    myHashTable() { table.resize(130000); size = 130000; capacity = 0; }
//    bool insert(int s)
//    {
//        /*if (load_factor() > 1.6)
//            resize();*/
//        int index = hash(s);
//        if (table[index].empty()) 
//        { 
//			table[index].push_front(s);
//            ++capacity;
//            return true; 
//        } else {
//            for (list<int>::iterator it = table[index].begin(); it != table[index].end(); ++it)
//                if (*it == s)
//                    return false;
//            table[index].push_back(s);
//            ++capacity;
//        }
//        return true;
//    }
//};
//
//
////class SetComparator
////{
////public:
////    bool operator()(const State& s1, const State& s2) const { return s1.field < s2.field; }
////};
//
//class QueueComparator
//{
//public:
//    bool operator()(const State& s1, const State& s2) const { return s1.dist > s2.dist; }
//};
//
//priority_queue<State, vector<State>, QueueComparator> go; 
////set<State, SetComparator> used;
//myHashTable used;
////
////int getDist(vector<int>& state)
////{
////    int res = 0;
////    for (int i = 0; i < FSIZE; ++i)
////    {
////        int value = state[i];
////        if (value) 
////            res += abs(i/3 - (value-1)/3) + abs(i%3 - (value-1)%3);
////        //if (value != (i+1))
////            //++res;
////    }
////    return res/2;
////}
//
//int toInt(vector<int>& cur)
//{
//    int result = 0;
//    for (int i = 0; i < FSIZE; ++i)
//        result = result*10 + cur[i];
//    return result;
//}
//
//int addNeibours(State s)
//{    
//    //vector<int> temp = s.arr;
//    int newInt;
//    int newDist;
//    if (s.index+3 < FSIZE)
//    {
//        newDist = s.dist + 1;
//        if (s.arr[s.index+3] == s.index+4)
//            ++newDist;
//        else 
//            if (s.arr[s.index+3] == s.index+1)
//                --newDist;
//		swap(s.arr[s.index+3], s.arr[s.index]);
//        newInt = toInt(s.arr);
//        State news(newInt, newDist, s.step+1, s.arr, s.index+3);
//        if (used.insert(newInt))
//            go.push(news);
//        if (news.field == 123456780)
//            return news.step;
//        swap(s.arr[s.index+3], s.arr[s.index]);
//    }
//
//    if (s.index > 2)
//	{
//        newDist = s.dist + 1;
//        if (s.arr[s.index-3] == s.index-2)
//            ++newDist;
//        else 
//            if (s.arr[s.index-3] == s.index+1)
//                --newDist;
//		
//        swap(s.arr[s.index-3], s.arr[s.index]);
//        newInt = toInt(s.arr);
//        State news(newInt, newDist, s.step+1, s.arr, s.index-3);
//        if (used.insert(newInt))
//            go.push(news);
//        if (news.field == 123456780)
//            return news.step;
//        swap(s.arr[s.index-3], s.arr[s.index]);
//    }
//
//    if ((s.index+1) % 3)
//    {
//        newDist = s.dist + 1;
//        if (s.arr[s.index+1] == s.index+2)
//            ++newDist;
//        else 
//            if (s.arr[s.index+1] == s.index+1)
//                --newDist;
//		swap(s.arr[s.index+1], s.arr[s.index]);
//        newInt = toInt(s.arr);
//        State news(newInt, newDist, s.step+1, s.arr, s.index+1);
//        if (used.insert(newInt))
//            go.push(news);
//        if (news.field == 123456780)
//            return news.step;
//        swap(s.arr[s.index+1], s.arr[s.index]);
//    }
//
//    if ((s.index-1) % 3 != 2 && s.index > 0)
//    {
//        newDist = s.dist + 1;
//        if (s.arr[s.index-1] == s.index)
//            ++newDist;
//        else 
//            if (s.arr[s.index-1] == s.index+1)
//                --newDist;
//		swap(s.arr[s.index-1], s.arr[s.index]);
//        newInt = toInt(s.arr);
//        State news(newInt, newDist, s.step+1, s.arr, s.index-1);
//        if (used.insert(newInt))
//            go.push(news);
//        if (news.field == 123456780)
//            return news.step;
//        swap(s.arr[s.index-1], s.arr[s.index]);
//    }
//
//    return 0;
//}
//
//int Astar()
//{
//    int flag;
//    do  
//    {
//        State s = go.top();
//        go.pop();
//        flag = addNeibours(s);
//        
//    } while (!flag && !go.empty());
//    
//    return flag;
//}
//
//int main()
//{
//    int startint = 0;
//    vector<int> start;
//    int temp;
//    int ind;
//    for (int i = 0; i < FSIZE; ++i)
//    {
//        scanf_s("%d", &temp);
//        start.push_back(temp);
//        if (!temp) 
//            ind = i;
//    }
//    startint = toInt(start);
//    if (startint != 123456780)
//    {
//        State s(startint, 0, 0);
//        s.arr = start;
//        s.index = ind;
//        go.push(s);
//        int result;
//        if (result = Astar()) 
//            printf("Yes\n%d\n", result);
//        else 
//            printf("No\n");
//    } else 
//        printf("Yes\n 0\n");
//    return 0;
//}