#include "OrgChart.hpp"

namespace ariel {
    
    OrgChart::OrgChart() {
        this->_root = nullptr;
    }

    OrgChart::OrgChart(const OrgChart& other) {
        this->_root = other._root;
    }
    
    OrgChart::~OrgChart() {
        delete this->_root;
    }

    OrgChart& OrgChart::operator=(const OrgChart& other) {
        if(this == &other) {
            return *this;
        }
        return *this;
    }

    OrgChart::Node* OrgChart::find(string &sup) {
        for (iterator it = this->begin_level_order(); it != this->end_level_order(); ++it) { 
                if((*it) == sup) {
                    return &it;
                }
        }
        throw runtime_error("No such node");
    } 
    
    OrgChart& OrgChart::add_root(const string &r) {
        if (this->_root == nullptr) {
            this->_root = new Node(r);
        } else {
            this->_root->_val = r;
        }
        return *this;
    }
    OrgChart& OrgChart::add_sub(string sup, string sub) {
        if(this->_root == nullptr) {
            throw runtime_error("There is no root");
        }
        Node *add = find(sup);
        add->_sub.push_back(new Node(std::move(sub)));
        return *this;
    }

    OrgChart::Node* OrgChart::setNext(int type) {
        list<Node*> list;
        list.push_front(this->_root);
        this->_root->_next = nullptr;
        Node *temp = nullptr;
        while(!list.empty()) {
            temp = list.back();
            list.pop_back();
            if(type == level_order) {
                for(size_t i = 0; i < temp->_sub.size(); i++) {
                    list.push_front(temp->_sub[i]);
                }
                temp->_next = list.back();
            } else if(type == reverse_level_order) {
                for(int i = (size_t)(temp->_sub.size() - 1); i >= 0 ; i--) {
                    list.push_front(temp->_sub.at((size_t)i));
                }
                if(!list.empty()) {
                    list.back()->_next = temp;
                }
            } else if(type == preorder) {
                for(int i = (size_t)(temp->_sub.size() - 1); i >= 0; i--) {
                    list.push_back(temp->_sub.at((size_t)i));
                }
                temp->_next =   list.back();
            }
        }
        return temp;
    }

    int OrgChart::printOrg(const OrgChart::Node *node, string level) { 
        cout << level << "> " << node->_val << endl;
        level += (node->_sub.empty()) ? "    " : "      ";

        for(size_t i = 0; i < node->_sub.size(); i++) {
            
            printOrg(node->_sub.at(i), level);
        }
        return 0;
    }
    ostream& operator<< (ostream &output, const OrgChart& orgChart) {
        OrgChart::printOrg(orgChart._root, "");
        return output;
    }

}