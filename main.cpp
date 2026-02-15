#include <iostream>
#include <unordered_map>


using namespace std;

/*
    LRU Cache Implementation
    Time Complexity:
        get()  -> O(1)
        put()  -> O(1)
*/

class LRUCache {
private:
    int capacity;

    struct Node {
        int key, value;
        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }
    };

    unordered_map<int, Node*> mp;
    Node* head;
    Node* tail;

    void remove(Node* node) {
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;

        if (node == head)
            head = node->next;
        if (node == tail)
            tail = node->prev;
    }

    void insertAtFront(Node* node) {
        node->next = head;
        node->prev = nullptr;

        if (head)
            head->prev = node;

        head = node;

        if (!tail)
            tail = head;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = nullptr;
        tail = nullptr;
    }

    int get(int key) {
        if (mp.find(key) == mp.end())
            return -1;

        Node* node = mp[key];
        remove(node);
        insertAtFront(node);

        return node->value;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            remove(node);
            insertAtFront(node);
            return;
        }

        if (mp.size() == capacity) {
            mp.erase(tail->key);
            remove(tail);
        }

        Node* newNode = new Node(key, value);
        insertAtFront(newNode);
        mp[key] = newNode;
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << "Get 1: " << cache.get(1) << endl;

    cache.put(3, 30);

    cout << "Get 2: " << cache.get(2) << endl;

    cache.put(4, 40);

    cout << "Get 1: " << cache.get(1) << endl;
    cout << "Get 3: " << cache.get(3) << endl;
    cout << "Get 4: " << cache.get(4) << endl;

    return 0;
}
