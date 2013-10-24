#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <queue>
#include <set>
#include <math.h>
#include <list>
#include <string>

#define FSIZE 16
#define SSIZE 4
char RIGTH_VARIANT[FSIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '0'};
#define SIMPLE_NUM 7

using namespace std;

class State
{
public:
    char* field;
    size_t dist;
    size_t step;
    size_t index;
	string seq;
    State(char* f, size_t d, size_t s, size_t i, string se) : field(f), dist(d), step(s), index(i), seq(se) {}
};

class myHashTable
{
public:
    vector<list<char*> > table;
    int size;
    int capacity;
    int hash(char* s) 
    {
		  int result = 0;
		  for (int i = 0; i < FSIZE; ++i)
			  result = (result+abs(s[i]))*SIMPLE_NUM%size;
		  return result;
    }

    myHashTable() { table.resize(17337); size = 17337; capacity = 0; }
    bool insert(char s[FSIZE])
    {
        int index = hash(s);
        if (table[index].empty()) 
        { 
			table[index].push_front(s);
            ++capacity;
            return true; 
        } else {
            for (list<char*>::iterator it = table[index].begin(); it != table[index].end(); ++it)
                if (*it == s)
                    return false;
            table[index].push_back(s);
            ++capacity;
        }
        return true;
    }
};

class QueueComparator
{
public:
    bool operator()(const State& s1, const State& s2) const { return s1.dist > s2.dist; }
};

priority_queue<State, vector<State>, QueueComparator> go; 
myHashTable used;

bool check(char c[FSIZE])
{
	for (size_t i = 0; i < FSIZE; ++i)
		if (RIGTH_VARIANT[i] != c[i])
			return false;
	return true;
}

string addNeibours(State s)
{    
    size_t newDist;
    if (s.index+SSIZE < FSIZE)
    {
        newDist = s.dist + 1;
        if (s.field[s.index+SSIZE] == s.index+SSIZE+1)
            ++newDist;
        else 
            if (s.field[s.index+SSIZE] == s.index+1)
                --newDist;
		swap(s.field[s.index+SSIZE], s.field[s.index]);
		State news(s.field, newDist, s.step+1, s.index+SSIZE, s.seq+"d");
		if (used.insert(s.field))
            go.push(news);
        if (check(news.field))
            return news.seq;
        swap(s.field[s.index+SSIZE], s.field[s.index]);
    }

    if (s.index > SSIZE-1)
	{
        newDist = s.dist + 1;
        if (s.field[s.index-SSIZE] == s.index-SSIZE+1)
            ++newDist;
        else 
            if (s.field[s.index-SSIZE] == s.index+1)
                --newDist;
		
        swap(s.field[s.index-SSIZE], s.field[s.index]);
		State news(s.field, newDist, s.step+1,  s.index-SSIZE, s.seq+"u");
		if (used.insert(s.field))
            go.push(news);
        if (check(news.field))
            return news.seq;
        swap(s.field[s.index-SSIZE], s.field[s.index]);
    }

    if ((s.index+1) % SSIZE)
    {
        newDist = s.dist + 1;
        if (s.field[s.index+1] == s.index+2)
            ++newDist;
        else 
            if (s.field[s.index+1] == s.index+1)
                --newDist;
		swap(s.field[s.index+1], s.field[s.index]);
		State news(s.field, newDist, s.step+1, s.index+1, s.seq+"r");
		if (used.insert(s.field))
            go.push(news);
        if (check(news.field))
            return news.seq;
        swap(s.field[s.index+1], s.field[s.index]);
	}

    if ((s.index-1) % SSIZE != SSIZE-1 && s.index > 0)
    {
        newDist = s.dist + 1;
        if (s.field[s.index-1] == s.index)
            ++newDist;
        else 
            if (s.field[s.index-1] == s.index+1)
                --newDist;
		swap(s.field[s.index-1], s.field[s.index]);
		State news(s.field,  newDist, s.step+1, s.index-1, s.seq+"l");
		if (used.insert(s.field))
            go.push(news);
        if (check(news.field))
            return news.seq;
        swap(s.field[s.index-1], s.field[s.index]);
    }

    return "";
}

string Astar()
{
    string flag;
    do  
    {
        State s = go.top();
        go.pop();
        flag = addNeibours(s);
        
    } while (flag == "" && !go.empty());
    
    return flag;
}

int main()
{
    char st[FSIZE];
    int temp;
    int ind;
	char ttemp[2];
    for (size_t i = 0; i < FSIZE; ++i)
    {
        scanf_s("%d", &temp);
        if (!temp) 
            ind = i;
		sprintf_s(ttemp, "%x", temp);
		st[i] = ttemp[0];
    }
    if (!check(st))
    {
        State s(st, 0, 0, ind, "");
        go.push(s);
        string result;
        if ((result = Astar()) != "")
            cout << "YES" << endl << result;
        else 
            printf("NO\n");
    } else 
        printf("YES\n");
    return 0;
}