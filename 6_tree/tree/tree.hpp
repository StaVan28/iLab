
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream> 
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "settings.h"

//-----------------------------------------------------------------------------

class NodeTree
{
    public:

        int key_    = 0; 
        int height_ = 0;

        NodeTree* left_   = nullptr;
        NodeTree* right_  = nullptr;
        NodeTree* parent_ = nullptr;
};
    
//!

class Tree
{
    private:

        //--------------------------------------------------

        char*     name_     = nullptr;
        NodeTree* root_     = nullptr;
        int       capacity_ = 0;

        //--------------------------------------------------

        NodeTree* insert(NodeTree* insrt_node, const int key)
        {
            if (insrt_node == nullptr) 
            {
                insrt_node       = new NodeTree;
                insrt_node->key_ = key;
            }
            else if (insrt_node->key_ < key)
            {
                insrt_node->right_          = insert(insrt_node->right_, key_);
                insrt_node->right_->parent_ = insrt_node;
            }
            else
            {
                insrt_node->left_           = insert(insrt_node->left_,  key_);
                insrt_node->left_->parent_  = insrt_node;    
            }

            return insrt_node;
        }

        //--------------------------------------------------

    public:

        //--------------------------------------------------

        Tree() :
            name_(new char[strlen(UNKNOWN_NAME) + 1])  
        {
            strcpy(name_, UNKNOWN_NAME);
        }

        //--------------------------------------------------

        Tree(char* const name) :
            name_(new char[strlen(name) + 1]) 
        {
            strcpy(name_, name);
        }

        //--------------------------------------------------

       ~Tree()
        {
            delete [] name_;
            delete    root_;
        }    

        //--------------------------------------------------

        void insert(const int key)
        {
            insrt_node = insert(insrt_node, key);
        }

        //--------------------------------------------------
    
        void dump()
        {
            
        }

        //--------------------------------------------------

};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED