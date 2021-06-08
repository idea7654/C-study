#include <iostream>
#include <string>
#include <vector>

//using namespace std;

struct nTree
{
    //int data;
    std::string name;
    bool isDir;
    std::vector<nTree*> children; 
};

struct file_system{
    using node = nTree;
    using node_ptr = nTree*;

    private:
        node_ptr root;
        node_ptr cwd;
    public:
        file_system()
        {
            root = new node {"/", true, {}};
            cwd = root;
        }

        node_ptr find(const std::string& path)
        {
            if(path[0] == '/')
            {
                return find_impl(root, path.substr(1));
            }
            else{
                return find_impl(cwd, path);
            }
        }
    private:
        node_ptr find_impl(node_ptr directory, const std::string& path)
        {
            if(path.empty()){
                return directory;
            }
            auto sep = path.find('/');
            std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);
            std::string rest_path = sep == std::string::npos ? "" : path.substr(sep+1);
            auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child){
                return child->name == current_path;
            });

            if(directory->children.end() != found)
            {
                return find_impl(*found, rest_path);
            }
            return NULL;
        }
    public:
        bool add(const std::string& path, bool is_dir)
        {
            if(path[0] == '/'){
                return add_impl(root, path.substr(1), is_dir);
            }
            else{
                return add_impl(cwd, path, is_dir);
            }
        }
    private:
        bool add_impl(node_ptr directory, const std::string& path, bool is_dir)
        {
            if(directory->isDir == false)
            {
                std::cout << directory->name << "is not file" << std::endl;
                return false;
            }

            auto sep = path.find('/');
            if(sep == std::string::npos)
            {
                auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child){
                    return child->name == path;
                });
            }
        }
};