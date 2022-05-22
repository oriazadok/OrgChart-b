#include <iostream>
#include <string>
#include <vector>
#include <list>

#define LEVEL_ORDER 0
#define REVERSE_LEVEL_ORDER 1
#define PRE_ORDER 2

using namespace std;


namespace ariel {
    
    class OrgChart {
        private:

            /**
             * Node is inner class represent a node in the organization 
             * 
             */
            class Node {
                public:
                    string _val;
                    vector<Node*> _sub;
                    Node *_next;
                    Node(string str) 
                        :_val(std::move(str)), _next(nullptr) {}
                    ~Node() {
                        for(Node* n : _sub) {
                            delete  n;
                        }
                    }
            };

            struct Node *_root;

        public:

            // constructor
            OrgChart();

            // destructor
            ~OrgChart();

            /**
             * @brief This function search a name in the tree
             * and return the Node contains the name in the tree
             * 
             * @param str 
             * @return Node* 
             */
            Node* find(string &sup);
            
            /**
             * @brief This function add a root to the tree
             * if there is a root already the givven name will replace the old one
             * 
             * @param r 
             * @return OrgChart& 
             */
            OrgChart& add_root(const string &r);

            /**
             * @brief This function add a node to the sub of the givven name
             * 
             * @param sup 
             * @param sub 
             * @return OrgChart& 
             */
            OrgChart& add_sub(string sup, string sub);

            /**
             * @brief This function set tne next pointers of each node for the iterators
             * for the level_order and the reverse_level_order we will use BFS
             * for preorder we will use DFS
             * 
             * the parameter type tells the function which kind of iterator we use
             * 
             * @param type 
             * @return Node* 
             */
            Node* setNext(int type);
            
            /**
             * @brief This function print the tree of the organazation
             * 
             * @param node 
             * @param level 
             * @return int 
             */
            // int OrgChart::printOrg(Node* root, ostream& output, string first_prefix, bool last_child){
            static int printOrg(const OrgChart::Node *node, string level);
            friend ostream& operator<< (ostream& output, const OrgChart& orgChart);

             /**
             * iterator is inner class represent a iterator of the organization 
             * 
             */
            class iterator {
                private:
                    struct Node *_current;
                
                public:
                    iterator(struct Node *ptr = nullptr)
                        : _current(ptr) {
                    }

                    string& operator*() const {
                        return this->_current->_val;
                    }

                    string* operator->() const {
                        return &this->_current->_val;
                    }

                    Node* operator&() const {
                        return this->_current;
                    }

                    // ++i;
                    iterator& operator++() {
                        this->_current = this->_current->_next;
                        return *this;
                    }

                    // i++;
                    // Usually iterators are passed by value and not by const& as they are small.
                    iterator operator++(int) {
                        iterator tmp= *this;
                        this->_current = _current->_next;
                        return tmp;
                    }

                    bool operator==(const iterator& rhs) const {
                        return _current == rhs._current;
                    }

                    bool operator!=(const iterator& rhs) const {
                        return _current != rhs._current;
                    }

            };  // END OF THE INNER CLASS ITERATOR


            //////////////////////////////////////
            // LEVEL ORDER
            //////////////////////////////////////
            iterator begin() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                setNext(LEVEL_ORDER);
                return iterator{this->_root};
            }
            iterator end() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                return iterator{nullptr};
            }

            iterator begin_level_order() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                setNext(LEVEL_ORDER);
                return iterator{this->_root};
            }
            iterator end_level_order() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                return iterator{nullptr};
            }

            //////////////////////////////////////
            // REVERSE LEVEL ORDER
            //////////////////////////////////////
            iterator begin_reverse_order() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                return iterator{setNext(REVERSE_LEVEL_ORDER)};
            }
            iterator reverse_order() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                return iterator{nullptr};
            }

            //////////////////////////////////////
            // PREORDER
            //////////////////////////////////////
            iterator begin_preorder() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                setNext(PRE_ORDER);
                return iterator{this->_root};
            }
            iterator end_preorder() {
                if(this->_root == nullptr) {
                    throw runtime_error("There is no root");
                }
                return iterator{nullptr};
            }

    };

}