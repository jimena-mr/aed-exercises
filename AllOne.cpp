#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class MyHashMap {
public:
    vector<int> vec;
    int size;
    int count; // contendra el numero de elementos almacenados

    MyHashMap(): count(0) {
        size = 1e6 + 1;
        vec.resize(size);
        fill(vec.begin(), vec.end(), -1); // inicializa el mapa con -1
    }

    /*
        MyHashMap(int capacity) size(capacity) {
        vec.resize(size);
        fill(vec.begin(), vec.end(), -1);
    }

    */

    void put(int key, int value) {
        vec[key] = value;
        count++;
    }

    int get(int key) {
        return vec[key];
    }

    void remove(int key) {
        vec[key] = -1;
        count--;
    }

    double fillfactor() const {
        return static_cast<double>(count) / size;
    }
};

class AllOne {
private:
    MyHashMap freqMap;
    vector<vector<string>> freqList;
    vector<int> keyToIndex;

    int getKeyIndex(const string &key) {
        // funcion hash
        unsigned long hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % freqMap.size;
    }

public:
    AllOne() : freqList(1), keyToIndex(freqMap.size, -1) {}

    void inc(const string &key) {
        int index = getKeyIndex(key);
        int currFreq = freqMap.get(index);
        if (currFreq == -1) currFreq = 0;

        if (currFreq > 0) {
            auto &keys = freqList[currFreq];
            keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
            if (keys.empty()) {
                freqList[currFreq].clear();
                keyToIndex[index] = -1;
            }
        }

        currFreq++;
        freqMap.put(index, currFreq);
        if (currFreq >= freqList.size()) {
            freqList.resize(currFreq + 1);
        }
        freqList[currFreq].push_back(key);
        keyToIndex[index] = currFreq;
    }

    void dec(const string &key) {
        int index = getKeyIndex(key);
        int currFreq = freqMap.get(index);
        if (currFreq == -1) return;

        auto &keys = freqList[currFreq];
        keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
        if (keys.empty()) {
            freqList[currFreq].clear();
            keyToIndex[index] = -1;
        }

        if (currFreq > 1) {
            currFreq--;
            freqMap.put(index, currFreq);
            freqList[currFreq].push_back(key);
            keyToIndex[index] = currFreq;
        } else {
            freqMap.remove(index);
        }
    }

    string getMaxKey() {
        for (int i = freqList.size() - 1; i > 0; --i) {
            if (!freqList[i].empty()) {
                return freqList[i][0];
            }
        }
        return "";
    }

    string getMinKey() {
        for (int i = 1; i < freqList.size(); ++i) {
            if (!freqList[i].empty()) {
                return freqList[i][0];
            }
        }
        return "";
    }
};

int main() {
    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("world");
    allOne.inc("hello");

    cout << "Max Key: " << allOne.getMaxKey() << endl;  // hello
    cout << "Min Key: " << allOne.getMinKey() << endl;  // world

    allOne.dec("hello");

    cout << "Max Key: " << allOne.getMaxKey() << endl;  // hello/world
    cout << "Min Key: " << allOne.getMinKey() << endl;  // hello/world

    allOne.dec("hello");

    cout << "Max Key: " << allOne.getMaxKey() << endl;  // hello/world
    cout << "Min Key: " << allOne.getMinKey() << endl;  // hello/world

    return 0;
}
