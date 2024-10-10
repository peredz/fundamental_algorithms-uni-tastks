#include <iostream>

class List
{
private:

    struct Node
    {
        int data;
        Node* next;
    
        Node(int value, Node* next_node){
            data = value;
            next = next_node;
        }
    };

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

    int find_divisors(int num)
    {
        int counter {0};
        num = abs(num);

        for (int i{2}; i < num; i++){
            if (num % i == 0) counter++;
        }


        return counter;
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

    void find_elements(int value){
        if (root == nullptr)
        {
            std:: cout << "no such element in the list\n\r";
            return;
        };
        
        int counter {0};
        Node* cur_el = root;
        while (cur_el->next != root){
            if (cur_el->data == value) counter++;
            cur_el = cur_el->next;
        }
        if (cur_el->data == value) counter++;
        
        if (counter == 0) std::cout << "no such element in the list\n\r";
        else if (counter == 1) std::cout << "there is one " << value << " in the list\n\r";
        else std::cout << "there are " << counter << " " << value << "'s in the list\n\r";
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
    
    void print(std::string sep = "\n\r"){
        if (root == nullptr){
            std::cout << "empty list" << sep;
            return;
        }
        Node* cur_el = root;
        while (cur_el->next != root)
        {
            std::cout << cur_el->data << " ";
            cur_el = cur_el->next;
        }
        std::cout << cur_el->data << sep;        
    }

    void print_with_divisors(std::string sep = "\n\r"){
        if (root == nullptr){
            std::cout << "empty list" << sep;
            return;
        }
        Node* cur_el = root;
        while (cur_el->next != root)
        {
            std::cout << cur_el->data << "(" << find_divisors(cur_el->data) << ") ";
            cur_el = cur_el->next;
        }

        std::cout << cur_el->data << "(" << find_divisors(cur_el->data) << ") " << sep;        
    }

    List merge(List lst){
        List new_list;

        if (lst.root == nullptr){
            if (root = nullptr){
                return new_list;
            }
            return this->create_copy();
        }

        if (root = nullptr){
            return new_list;
        }

        Node* cur_el = lst.root;
        new_list.add(cur_el->data);
        while (cur_el->next != lst.root ){
            cur_el = cur_el->next;
            new_list.add(cur_el->data);
        }

        cur_el = root;
        new_list.add(cur_el->data);
        while (cur_el->next != root ){
            cur_el = cur_el->next;
            new_list.add(cur_el->data);
        }
        // new_list.print();
        return new_list;
    }

    List divisors_control()
    {
        List new_list;
        Node* cur_el = root;

        if (root == nullptr){
            return new_list;
        }

        if (find_divisors(cur_el->data) > 3)
        {
            new_list.add(cur_el->data);
        }

        cur_el = cur_el->next;
        while (cur_el != root ){
            if (find_divisors(cur_el->data) > 3) new_list.add(cur_el->data);
            cur_el = cur_el->next;
        }

        return new_list;
    }

    List create_copy(){
        List new_lst;
        Node * cur_el = root;
        if (root == nullptr)
        {
            return new_lst;
        }

        while (cur_el->next != root)
        {
            new_lst.add(cur_el->data);
            cur_el = cur_el->next;
        } 
        new_lst.add(cur_el->data);
        return new_lst;
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

void some_tests(){
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
    lst.find_elements(5);
    lst.find_elements(11);
    lst.find_elements(13);
    lst.find_elements(17);
    List second_lst;
    for (int i = 0; i < 10; i++) second_lst.add(i * -1);
    lst.print();
    second_lst.print();
    List merged_list;
    merged_list = lst.merge(second_lst);
    merged_list.print();
}


int main(){
    List lst;
    for (int i{-30}; i < 30; i++){
        lst.add(i);
    }
    lst.print_with_divisors();

    List lst_with_4p_divs = lst.divisors_control();
    std::cout << std::endl;
    lst_with_4p_divs.print_with_divisors();
    lst = lst.merge(lst_with_4p_divs);
    lst.print();
}
