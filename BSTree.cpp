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
};