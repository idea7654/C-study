#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct node
{
    string position;
    node* first;
    node* second;
};

struct org_tree
{
    node* root;
    static org_tree create_org_structure(const string& pos)
    {
        org_tree tree;
        tree.root = new node{pos, NULL, NULL};
        return tree;
    }

    static node* find(node* root, const string& value)
    {
        if(root == NULL){
            return NULL;
        }
        if(root->position == value){
            return root;
        }

        auto firstFound = org_tree::find(root->first, value);

        if(firstFound != NULL){
            return firstFound;
        }

        return org_tree::find(root->second, value);
    }

    bool addSubordinate(const string& manager, const string& subordinate)
    {
        auto managerNode = org_tree::find(root, manager);

        if(!managerNode){
            cout << manager << "not found: " << endl;
            return false;
        }

        if(managerNode->first && managerNode->second){
            cout << manager << "under " << subordinate << "could not add" << endl;
            return false;
        }

        if(!managerNode->first){
            managerNode->first = new node{subordinate, NULL, NULL};
        }else{
            managerNode->second = new node{subordinate, NULL, NULL};
        }

        cout << manager << " under " << subordinate << "add" << endl;
        return true;
    }

    static void levelOrder(node* start)
    {
        if(!start){
            return;
        }

        queue<node*> q;
        q.push(start);

        while(!q.empty())
        {
            int size = q.size();
            for(int i = 0; i < size; i++){
                auto current = q.front();
                q.pop();

                cout << current->position << ", ";
                if(current->first){
                    q.push(current->first);
                }
                if(current->second){
                    q.push(current->second);
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinate("CEO", "SubPresident");
    tree.addSubordinate("SubPresident", "ITPre");
    tree.addSubordinate("SubPresident", "margetingPre");
    org_tree::levelOrder(tree.root);
    while(true){

    }
}