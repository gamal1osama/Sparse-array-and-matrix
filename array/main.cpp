#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int data=0;
    int idx;
    Node* prev{};
    Node* next{};
    Node (int data,int idx):data(data),idx(idx){}
};

class Linked_List_array {
private:
    int length=0;
    int array_length=0;
    Node* head{};
    Node* tail{};

    void link(Node* first,Node*second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    Node* embed_after(Node* node_before, int data, int index) {
        Node* middle = new Node(data, index);
        ++length;

        Node* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }
    Node* get_index(int idx,bool is_created_if_not_founded) {
        Node * pre=head;
        while (pre->next && pre->next->idx < idx)
            pre=pre->next;
        bool is_founded=pre->next && pre->next->idx == idx;

        if(is_founded)
            return pre->next;

        if(!is_created_if_not_founded)
            return nullptr;

        return embed_after(pre,0,idx);
    }

public:
    Linked_List_array(int array_length):array_length(array_length) {
        tail = head = new Node(0, -1);
        ++length;
    }

    void print_array() {
        Node* cur = head->next;

        for (int c = 0; c < array_length; ++c) {
            if (cur && cur->idx == c) {
                cout << cur->data << " ";
                cur = cur->next;
            } else
                cout << "0 ";
        }
        cout << "\n";
    }
    void print_non_zeros() {
        for(Node*cur=head->next;cur;cur=cur->next) {
            cout<<cur->data<<" ";
        }
        cout<<"\n";
    }

    void set_value(int data, int index) {
        get_index(index, true)->data = data;
    }
    int get_value(int index) {
        Node* node = get_index(index, false);
        if (!node)
            return 0;
        return node->data;
    }
    void add(Linked_List_array &other) {
        assert(array_length==other.array_length);
        for(Node *cur_other = other.head->next;cur_other;cur_other=cur_other->next) {
            Node * our_cur=get_index(cur_other->idx,true);
            our_cur->data+=cur_other->data;
        }
    }


};





int main() {
    Linked_List_array array(10);	// length 10
    array.set_value(50, 5);
    array.set_value(20, 2);
    array.set_value(70, 7);
    array.set_value(40, 4);
    array.print_array();
    // 0 0 20 0 40 50 0 70 0 0
    array.print_non_zeros();
    // 20 40 50 70
    cout << array.get_value(7) << "\n";	// 70

    Linked_List_array array2(10);
    array2.set_value(1, 4);
    array2.set_value(3, 7);
    array2.set_value(4, 6);

    array.add(array2);
    array.print_array();
    // 0 0 20 0 41 50 4 73 0 0

}
