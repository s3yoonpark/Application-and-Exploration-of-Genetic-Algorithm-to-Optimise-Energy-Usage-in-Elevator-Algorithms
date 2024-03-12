#include <bits/stdc++.h>
using namespace std; 

const int elevatorWeight = 3000;
const int humanWeight = 60;
const int distanceBetweenFloors = 3; 
const int accelerationGravity = 10; 

struct Query{
    int from, to; 
};

vector<Query> rq;

struct cmp1 {
    bool operator() (const pair<int,int>& A, const pair<int,int>& B) {
        int a = A.second == 1 ? rq[A.first-1].from : rq[A.first-1].to;
        int b = B.second == 1 ? rq[B.first-1].from : rq[B.first-1].to; 
        return a > b; 
    }
};

struct cmp2 {
    bool operator() (const pair<int,int>& A, const pair<int,int>& B) {
        int a = A.second == 1 ? rq[A.first-1].from : rq[A.first-1].to; 
        int b = B.second == 1 ? rq[B.first-1].from : rq[B.first-1].to; 
        return a < b; 
    }
};

int main() {
    freopen("input.txt", "r", stdin); 
    int n, curLevel; 
    cin >> n >> curLevel; 
    rq = vector<Query>(n); 
    for (int i = 0; i < n; ++i) {
        cin >> rq[i].from >> rq[i].to; 
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp2> left; 
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp1> right; 
    for (int i = 0; i < n; ++i) {
        if (rq[i].from >= curLevel) {
            right.push(make_pair(i+1, 1)); 
        } else {
            left.push(make_pair(i+1, 1)); 
        }
    }
    int last = curLevel; 
    int ans = 0; 
    int num = 0; 
    while (!right.empty()) {
        pair<int,int> cur = right.top(); right.pop();
        // cout << "RIGHT : " << (cur.second == 1 ? rq[cur.first-1].from : rq[cur.first-1].to) << '\n'; 
        // cout << cur.first << ' ' << cur.second << "  "; 
        if (cur.second == 1) {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].from) * distanceBetweenFloors; 
            last = rq[cur.first-1].from; 
            ++num; 
            if (rq[cur.first-1].to >= last) {
                right.push(make_pair(cur.first, 0)); 
            } else {
                left.push(make_pair(cur.first, 0)); 
            }
        } else {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].to) * distanceBetweenFloors; 
            last = rq[cur.first-1].to; 
            --num; 
        }
    }
    while (!left.empty()) {
        pair<int,int> cur = left.top(); left.pop();
        // cout << "LEFT : " << (cur.second == 1 ? rq[cur.first-1].from : rq[cur.first-1].to) << '\n'; 
        // cout << cur.first << ' ' << cur.second << "  "; 
        if (cur.second == 1) {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].from) * distanceBetweenFloors; 
            last = rq[cur.first-1].from; 
            ++num; 
            if (rq[cur.first-1].to <= last) {
                left.push(make_pair(cur.first, 0)); 
            } else {
                right.push(make_pair(cur.first, 0)); 
            }
        } else {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].to) * distanceBetweenFloors; 
            last = rq[cur.first-1].to; 
            --num; 
        }
    }
    while (!right.empty()) {
        pair<int,int> cur = right.top(); right.pop();
        // cout << "RIGHT : " << (cur.second == 1 ? rq[cur.first-1].from : rq[cur.first-1].to) << '\n'; 
        // cout << cur.first << ' ' << cur.second << "  "; 
        if (cur.second == 1) {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].from) * distanceBetweenFloors; 
            last = rq[cur.first-1].from; 
            ++num; 
        } else {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - rq[cur.first-1].to) * distanceBetweenFloors; 
            last = rq[cur.first-1].to; 
            --num; 
        }
    }
    // cout << '\n'; 
    cout << ans << '\n'; 

    return 0; 
}
