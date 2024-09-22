#include <iostream>

struct Node
{
    int data;
    Node* next;

    Node(int value, Node* next_node){
        data = value;
        next = next_node;
    }
};


class List
{
private:
    Node* root;
public:
    void add(int value){
        if (root == nullptr)
        {
            root = new Node(value, nullptr);
            root->next = root;
        }
        else
        {
            Node* cur_el;

            if (root->next == root)
            {
                cur_el = new Node(value, root);
                root->next = cur_el;
                if (root->data > value) root = cur_el;
                return;
            }

            cur_el = root;

            if (root->data > value)
            {
                while (cur_el->next != root){
                    cur_el = cur_el->next;
                }
                cur_el->next = new Node(value, root);
                root = cur_el->next;
                return;
            }
            
            else
            {
                while (cur_el->next->data < value && cur_el->next != root)
                {
                    cur_el = cur_el->next;
                }
            }
            
            cur_el->next = new Node(value, cur_el->next);
        }
    }

    void clear(){
        if (root == nullptr){
            return;
        }
        Node* cur_el = root->next;
        Node* cur_el_next = cur_el->next;
        while (cur_el != root)
        {
            delete cur_el;
            cur_el = cur_el_next;
            cur_el_next = cur_el_next->next;
        }
        delete root;
        root = nullptr;
    }
    
    void print(){
        if (root == nullptr){
            std::cout << "empty list\n\r";
            return;
        }
        Node* cur_el = root;
        while (cur_el->next != root)
        {
            std::cout << cur_el->data << " ";
            cur_el = cur_el->next;
        }
        std::cout << cur_el->data << std::endl;        
    }

    List(int value){
        add(value);
    }

    List(){
        root = nullptr;
    }

    ~List(){
        clear();
    }
};

int main(){
    List lst;
    lst.print();
    for (int i = 0; i < 10; i++){
        if (i % 2 == 0) lst.add(i);
        else lst.add(i + 10);
    }
    lst.print();
    lst.clear();
    lst.print();
}