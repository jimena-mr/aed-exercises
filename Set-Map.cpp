#include <iostream>
using namespace std;

class MyHashSet {
public:
   vector<int>v;
    MyHashSet() {
        v.resize(1000000+10,0);
    }
    
    void add(int key) {
        v[key]=1;
    }
    
    void remove(int key) {
        v[key]=0;
    }
    
    bool contains(int key) {
        if(v[key])return true;
        else return false;
    }
};


class MyHashMap {
public:
vector<int>vec;
int size;
    MyHashMap() {
        size = 1e6+1;
        vec.resize(size);
        fill(vec.begin() , vec.end() , -1);
    }
    
    void put(int key, int value) {
        vec[key] = value; 
    }
    
    int get(int key) {
        return vec[key]; 
    }
    
    void remove(int key) {
        vec[key] = -1; 
    }
};

MyHashSet hashSet;
    hashSet.add(1);
    hashSet.add(2);
    cout << "HashSet contains 1: " << (hashSet.contains(1) ? "True" : "False") << endl;
    cout << "HashSet contains 3: " << (hashSet.contains(3) ? "True" : "False") << endl;
    hashSet.add(2);
    cout << "HashSet contains 2: " << (hashSet.contains(2) ? "True" : "False") << endl;
    hashSet.remove(2);
    cout << "HashSet contains 2 after removal: " << (hashSet.contains(2) ? "True" : "False") << endl;

    MyHashMap hashMap;
    hashMap.put(1, 1);
    hashMap.put(2, 2);
    cout << "Value for key 1: " << hashMap.get(1) << endl;
    cout << "Value for key 3: " << hashMap.get(3) << endl;
    hashMap.put(2, 1);
    cout << "Updated value for key 2: " << hashMap.get(2) << endl;
    hashMap.remove(2);
    cout << "Value for key 2 after removal: " << hashMap.get(2) << endl;
