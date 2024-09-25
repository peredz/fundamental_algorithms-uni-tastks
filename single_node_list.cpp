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

    void delete_next_element(Node * prev_el){
        if (root == nullptr) throw std::logic_error("delete element from empty list");

        if (prev_el->next == root){
            if (root->next == root)
            {
                delete root;
                root = nullptr;
                return;
            }

            prev_el->next = root->next;
            delete root;
            root = prev_el->next;
        }

        else 
        {
            Node* to_delete = prev_el->next;
            prev_el->next = prev_el->next->next;
            delete to_delete;
        }
    }

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

    void delete_elements_by_value(int value){
        if (root == nullptr)
        {
            std:: cout << "ERROR: delete element from empty list\n\r";
            return;
        };
        int counter {0};
        Node* cur_el = root;
        while (cur_el->next != root){
            if (cur_el->next->data == value){
                counter++;
                delete_next_element(cur_el);
            }
            else cur_el = cur_el->next;
        }
        if (root->data == value){
            counter++;
            delete_next_element(cur_el);
        }
        if (counter == 0) std::cout << "No such element with value " << value << std::endl;
        else std::cout << "Removed all " << value << std::endl;
    }

    void delete_prev_element_by_value(int value){
        if (root == nullptr)
        {
            std:: cout << "ERROR: delete element from empty list\n\r";
            return;
        };
        int counter {0};
        Node* cur_el = root;
        while (cur_el->next != root){
            if (cur_el->next->next->data == value){
                counter++;
                delete_next_element(cur_el);
            }
            else cur_el = cur_el->next;
        }
        if (root->next->data == value){
            counter++;
            delete_next_element(cur_el);
        }
        if (counter == 0) std::cout << "No such element with value " << value << std::endl;
        else std::cout << "Removed elements before each occurrence " << value << std::endl;
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
        if (i % 2 == 0) {lst.add(i); lst.add(i);}
        else {lst.add(i + 10); lst.add(i + 10);} 
    }
    lst.print();
    lst.delete_elements_by_value(0);
    lst.print();
    lst.delete_elements_by_value(19);
    lst.delete_elements_by_value(4);
    lst.delete_elements_by_value(2);
    lst.add(11);
    lst.print();
    lst.delete_elements_by_value(11);
    lst.delete_elements_by_value(12);
    lst.print();
    lst.add(11);
    lst.print();
    lst.delete_prev_element_by_value(11);
    lst.print();
    lst.delete_prev_element_by_value(11);
    lst.print();
    lst.delete_prev_element_by_value(6);
    lst.print();
    lst.delete_prev_element_by_value(17);
    lst.print();
    lst.delete_prev_element_by_value(11);
    lst.print();
}