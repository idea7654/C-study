#include <iostream>
#include <string>

using namespace std;

struct node{
    int data;
    node* first;
    node* second;
};

struct bst{
    node* root;

    node* find(int value){
        return find_impl(root, value);
    }

    private:
        node* find_impl(node* current, int value){
            if(!current){
                cout << endl;
                return;
            }

            if(current->data == value){
                return current;
            }

            if(value < current->data){
                cout << current->data << " to left: ";
                return find_impl(current->first, value);
            }

            cout << current->data << " to right: ";
            return find_impl(current->second, value);
        }

    public:
        void insert(int value)
        {
            if(!root){
                root = new node{value, NULL, NULL};
            }else{
                insert_impl(root, value);
            }
        }

    private:
        void insert_impl(node* current, int value){
            if(value < current->data){
                if(!current->first){
                    current->first = new node{value, NULL, NULL};
                }else{
                    insert_impl(current->first, value);
                }
            }else{
                if(!current->second){
                    current->second = new node{value, NULL, NULL};
                }else{
                    insert_impl(current->second, value);
                }
            }
        }
    public:
        void inOrder()
        {
            inOrder_impl(root);
        }
    private:
        void inOrder_impl(node* start)
        {
            if(!start)
            {
                return;
            }
            inOrder_impl(start->first);
            cout << start->data << " ";
            inOrder_impl(start->second);
        }
    public: 
        node* successor(node* start)
        {
            auto current = start->second;
            while (current && current->first){
                current = current->first;
            }
            return current;
        }
        void deleteValue(int value)
        {
            root = delete_impl(root, value);
        }
    private:
        node* delete_impl(node* start, int value)
        {
            if(!start)
            {
                return NULL;
            }

            if(value < start->data)
            {
                start->first = delete_impl(start->first, value);
            }else if(value > start->data)
            {
                start->second = delete_impl(start->second, value);
            }else{
                if(!start->first){
                    auto tmp = start->second;
                    delete start;
                    return tmp;
                }
                if(!start->second){
                    auto tmp = start->first;
                    delete start;
                    return tmp;
                }

                auto succNode = successor(start);
                start->data = succNode->data;

                start->second = delete_impl(start->second, succNode->data);
            }
            return start;
        }
};