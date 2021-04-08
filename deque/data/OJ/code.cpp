//
// Created by Rainy Memory on 2021/4/8.
//

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../../deque.hpp"


bool need_to_check_throw = 1;
bool good_complexity = 1;//if the complexity is N^2, change to 0
int N = good_complexity ? 50000 : 1000;


class T {
private:
    int x;
public:
    T(int x) : x(x) {}
    
    int num() const { return x; }
    
    void change(int y) {
        x = y;
    }
};

bool operator==(const T &a, const T &b) {
    return a.num() == b.num();
}

bool operator!=(const T &a, const T &b) {
    return a.num() != b.num();
}

sjtu::deque<T> q;
std::deque<T> stl;
sjtu::deque<T>::iterator it_q;
std::deque<T>::iterator it_stl;
sjtu::deque<T>::const_iterator _it_q;
std::deque<T>::const_iterator _it_stl;


bool equal() {
    if (q.size() != stl.size()) return 0;
    if (q.empty() != stl.empty()) return 0;
    int cnt = 0;
    for (it_q = q.begin(), it_stl = stl.begin(); it_q != q.end() || it_stl != stl.end(); it_q++, it_stl++) {
        if (*it_q != *it_stl) {
            printf("cnt = %d\n", cnt);
            return 0;
        }
        cnt++;
    }
    return 1;
}

bool test1() {
    //printf("test1: push & pop                    ");
    for (int i = 1; i <= N; i++) {
        if (i % 10 <= 3) q.push_back(T(i)), stl.push_back(T(i));
        else if (i % 10 <= 7) q.push_front(T(i)), stl.push_front(T(i));
        else if (i % 10 <= 8) q.pop_back(), stl.pop_back();
        else if (i % 10 <= 9) q.pop_front(), stl.pop_front();
    }
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    while (!q.empty()) {
        q.pop_back();
        stl.pop_back();
    }
    //puts("Accept");
    return true;
}

bool test2() {
    //printf("test2: at & [] & front & back        ");
    int flag = 0;
    try {
        int t = q.front().num();
    } catch (...) { flag++; }
    
    try {
        int t = q.back().num();
    } catch (...) { flag++; }
    if (flag != 2 && need_to_check_throw) {
        //puts("Wrong Answer");
        return false;
    }
    for (int i = 1; i <= N; i++) {
        if (i % 10 <= 3) q.push_back(T(i)), stl.push_back(T(i));
        else if (i % 10 <= 7) q.push_front(T(i)), stl.push_front(T(i));
        else if (i % 10 <= 8) q.pop_back(), stl.pop_back();
        else if (i % 10 <= 9) q.pop_front(), stl.pop_front();
    }
    flag = 0;
    try {
        int t = (q.at(q.size() + 100)).num();
    } catch (...) { flag = 1; }
    if (flag != 1 && need_to_check_throw) {
        //puts("Wrong Answer");
        return false;
    }
    int num = q.size();
    for (int i = 0; i < 1000; i++) {
        int t = rand() % num;
        if (q[t] != stl[t] || q.at(t) != stl.at(t)) {
            //puts("Wrong Answer");
            return false;
        }
    }
    return !(q.front() != stl.front() || q.back() != stl.back());
    //puts("Accept");
}

bool test3() {
    //printf("test3: iterator operation            ");
    int num = q.size();
    for (int i = 1; i <= 1000; i++) {
        int t1 = rand() % num;
        int t2 = rand() % num;
        if (*(q.begin() + t1) != *(stl.begin() + t1)) {
            //puts("Wrong Answer");
            return false;
        }
        if (t2 && *(q.end() - t2) != *(stl.end() - t2)) {
            //puts("Wrong Answer");
            return false;
        }
        if ((q.begin() + t1) - (q.begin() + t2) != (t1 - t2)) {
            //puts("Wrong Answer");
            return false;
        }
    }
    if ((q.begin() + num) != q.end()) {
        //puts("Wrong Answer");
        return false;
    }
    if ((q.end() - num) != q.begin()) {
        //puts("Wrong Answer");
        return false;
    }
    bool flag = 0;
    sjtu::deque<T> other;
    try {
        int t = q.begin() - other.begin();
    } catch (...) {
        flag = 1;
    }
    if (!flag && need_to_check_throw) {
        //puts("Wrong Answer");
        return false;
    }
    it_q = q.begin();
    it_stl = stl.begin();
    for (int i = 1; i <= 10; i++) {
        int t = rand() % (num / 10);
        it_q += t;
        it_stl += t;
        if (*it_q != *it_stl) {
            //puts("Wrong Answer");
            return false;
        }
        if (it_q->num() != it_stl->num()) {
            //puts("Wrong Answer");
            return false;
        }
    }
    it_q = --q.end();
    it_stl = --stl.end();
    if (*it_q != *it_stl) {
        //puts("Wrong Answer");
        return false;
    }
    for (int i = 1; i < 10; i++) {
        int t = rand() % (num / 10);
        it_q -= t;
        it_stl -= t;
        if (*it_q != *it_stl) {
            //puts("Wrong Answer");
            return false;
        }
        it_q->change(t);;
        it_stl->change(t);
        if (*it_q != *it_stl) {
            //puts("Wrong Answer");
            return false;
        }
    }
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    if (!(q.begin() + 10 == q.begin() + 5 + 6 - 1)) {
        //puts("Wrong Answer");
        return false;
    }
    sjtu::deque<T> pp;
    if (q.end() == pp.end()) {
        //puts("Wrong Answer");
        return false;
    }
    
    int t = rand() % (q.size() - 1);
    it_q = q.begin() + t;
    it_stl = stl.begin() + t;
    const sjtu::deque<T>::iterator it_q_const(++it_q);
    const std::deque<T>::iterator it_stl_const(++it_stl);
    if (*it_q_const != *it_stl_const) {
        //puts("Wrong Answer");
        return false;
    }
    if (it_q_const->num() != it_stl_const->num()) {
        //puts("Wrong Answer");
        return false;
    }
    it_q_const->change(t);
    it_stl_const->change(t);
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    //puts("Accept");
    return true;
}

bool test4() {
    //printf("test4: const_iterator operation      ");
    const sjtu::deque<T> _q(q);
    const std::deque<T> _stl(stl);
    int num = _q.size();
    for (int i = 1; i <= 1000; i++) {
        int t1 = rand() % num;
        int t2 = rand() % num;
        if (*(_q.cbegin() + t1) != *(_stl.cbegin() + t1)) {
            //puts("Wrong Answer");
            return false;
        }
        if (t2 && *(_q.cend() - t2) != *(_stl.cend() - t2)) {
            //puts("Wrong Answer");
            return false;
        }
        if ((_q.cbegin() + t1) - (_q.cbegin() + t2) != (t1 - t2)) {
            //puts("Wrong Answer");
            return false;
        }
    }
    if ((_q.cbegin() + num) != _q.cend()) {
        //puts("Wrong Answer");
        return false;
    }
    if ((_q.cend() - num) != _q.cbegin()) {
        //puts("Wrong Answer");
        return false;
    }
    _it_q = _q.cbegin();
    _it_stl = _stl.cbegin();
    for (int i = 1; i <= 10; i++) {
        int t = rand() % (num / 10);
        _it_q += t;
        _it_stl += t;
        if (*_it_q != *_it_stl) {
            //puts("Wrong Answer");
            return false;
        }
        if (_it_q->num() != _it_stl->num()) {
            //puts("Wrong Answer");
            return false;
        }
    }
    _it_q = --_q.cend();
    _it_stl = --_stl.cend();
    if (*_it_q != *_it_stl) {
        //puts("Wrong Answer");
        return false;
    }
    if (!(_q.cbegin() + 10 == _q.cbegin() + 5 + 6 - 1)) {
        //puts("Wrong Answer");
        return false;
    }
    //puts("Accept");
    return true;
}

bool test5() {
    //printf("test5: erase & insert                ");
    for (int i = 1; i <= sqrt(N) && q.size() >= 10; i++) {
        int t = rand() % (q.size() - 3);
        it_q = q.begin() + t;
        it_stl = stl.begin() + t;
        it_q = q.erase(it_q);
        it_stl = stl.erase(it_stl);
        it_q = q.erase(it_q);
        it_stl = stl.erase(it_stl);
        it_q->change(t);
        it_stl->change(t);
    }
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    it_q = q.erase(q.end() - 1);
    it_stl = stl.erase(stl.end() - 1);
    if (it_q != q.end()) {
        //puts("Wrong Answer");
        return false;
    }
    for (int i = 1; i <= sqrt(N); i++) {
        int t = rand() % q.size();
        it_q = q.begin() + t;
        it_stl = stl.begin() + t;
        it_q = q.insert(it_q, T(t));
        it_stl = stl.insert(it_stl, T(t));
        
        it_q = q.insert(it_q, T(t + 1));
        it_stl = stl.insert(it_stl, T(t + 1));
    }
    it_q = q.begin();
    it_stl = stl.begin();
    for (int i = 1; i <= sqrt(N); i++) {
        it_q = q.insert(it_q, T(i));
        it_stl = stl.insert(it_stl, T(i));
    }
    it_q = q.insert(q.end(), T(66666));
    it_stl = stl.insert(stl.end(), T(66666));
    if (it_q != q.end() - 1) {
        //puts("Wrong Answer");
        return false;
    }
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    //puts("Accept");
    return true;
}

bool test6() {
    //printf("test6: clear & copy & assignment     ");
    sjtu::deque<T> p(q), r;
    r = q;
    q.clear();
    if (!q.empty() || q.size() != 0 || q.begin() != q.end()) {
        //puts("Wrong Answer");
        return false;
    }
    q = q = q;
    if (!q.empty() || q.size() != 0 || q.begin() != q.end()) {
        //puts("Wrong Answer");
        return false;
    }
    for (int i = 1; i <= 1000; i++) {
        int t = rand() % p.size();
        p.push_back(T(t));
        p.insert(p.begin() + t, T(t));
        r.push_back(T(t));
        r.insert(r.begin() + t, T(t));
        stl.push_back(T(t));
        stl.insert(stl.begin() + t, T(t));
    }
    
    q = p;
    p.clear();
    q = q = q = q;
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    q.clear();
    q = r;
    r.clear();
    q = q = q = q;
    if (!equal()) {
        //puts("Wrong Answer");
        return false;
    }
    //puts("Accept");
    return true;
}

bool test7() {
    //printf("test7: complexity                    ");
    int num = 400000;
    static sjtu::deque<T> q;
    for (int i = 0; i < num; i++) {
        if (i % 1000 == 0)std::cout << i << std::endl;
        q.push_front(T(i));
    }
    for (int i = 0; i < num; i++) {
        if (i % 1000 == 0)std::cout << i << std::endl;
        q.pop_front();
    }
    for (int i = 0; i < num; i++) {
        if (i % 1000 == 0)std::cout << i << std::endl;
        q.push_back(T(i));
    }
    for (int i = 0; i < num; i++) {
        if (i % 1000 == 0)std::cout << i << std::endl;
        q.pop_back();
    }
    for (int i = 0; i < num; i++) {
        if (i % 10 <= 3) q.push_back(T(i));
        else if (i % 10 <= 7) q.push_front(T(i));
        else if (i % 10 <= 8) q.pop_back();
        else if (i % 10 <= 9) q.pop_front();
    }
    int test_num = 500000;
    it_q = q.begin() + q.size() - 10;
    for (int i = 0; i < test_num; i++) {
        int tmp = (*it_q).num();
        tmp = it_q->num();
        if (i % test_num == 0) it_q = q.begin() + rand() % q.size();
    }
    for (int i = 0; i < N; i++) {
        it_q = q.begin() + rand() % q.size();
        q.insert(it_q, T(rand()));
    }
    for (int i = 0; i < N; i++) {
        it_q = q.begin() + rand() % q.size();
        q.erase(it_q);
    }
    for (int i = 0; i < N; i++) {
        int tmp = q[rand() % q.size()].num();
        tmp = q.at(rand() % q.size()).num();
    }
    if (good_complexity) {
        q.clear();
        for (int i = 0; i < 2000000; i++)
            q.push_back(i);
        while (q.size() > 2010) {
            if (rand() % 2) q.pop_front();
            else q.pop_back();
        }
        int tmp;
        for (int i = 0; i < 500000; i++) {
            tmp = q[2000].num();
            tmp = q[1000].num();
        }
    }
    //puts("Accept");
    return true;
}

int main() {
    srand(time(NULL));
    //puts("test start:");
    if (test1() &&
        test2() &&
        test3() &&
        test4() &&
        test5() &&
        test6() &&
        test7())
        std::cout << 1 << std::endl;
    else
        std::cout << 0 << std::endl;
    return 0;
}