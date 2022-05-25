#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;


namespace ariel {

    const int level_order = 0;
    const int reverse_level_order = 1;
    const int preorder = 2;
    
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

                    Node(const Node& other) {
                        this->_val = other._val;
                        this->_sub = other._sub;
                        this->_next = other._next;
                    }

                    Node( Node&& other) = default;

                    ~Node() {
                        for(Node* n : _sub) {
                            delete  n;
                        }
                    }

                    Node& operator=(const Node& other) = default;
                    Node& operator=(Node&& ) = default;
            };

            struct Node *_root;

        public:

            // constructor
            OrgChart();

            // copy constructor
            OrgChart(const OrgChart& other);
            OrgChart(OrgChart&& other) = default;

            // destructor
            ~OrgChart();

            OrgChart& operator=(const OrgChart& other);
            OrgChart& operator=(OrgChart&& other) = default;

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
                setNext(level_order);
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
                setNext(level_order);
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
                return iterator{setNext(reverse_level_order)};
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
                setNext(preorder);
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