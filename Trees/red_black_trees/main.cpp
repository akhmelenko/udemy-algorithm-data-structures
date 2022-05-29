
#include <iostream>
#include <queue>

// Let x be the newly inserted node.
// 1. Perform standard BST insertion and make the color of newly inserted nodes as RED.
// 2. If x is root, change color of x as BLACK (Black height of complete tree increases by 1).
// 3. Do following if color of x’s parent is not BLACK or x is not root.
//      1. If x’s uncle is RED (Grand parent must have been black from property 4)
//          1. Change color of parent and uncle as BLACK.
//          2. color of grand parent as RED.
//          3. Change x = x’s grandparent, repeat steps 2 and 3 for new x.
//         2. If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)

// 1. Determine the configuration:
//     1. Left Left Case (p is left child of g and x is left child of p).
//     2. Left Right Case (p is left child of g and x is right child of p).
//     3. Right Right Case (Mirror of case a).
//     4. Right Left Case (Mirror of case c).

// 2. Change x = x’s parent, repeat steps 2 and 3 for new x.

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *parent;
    bool color;
};

class RBTree {
   private:
    Node *root;

   protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);

   public:
    // Constructor
    RBTree() { root = NULL; }
    void insert(const int &n);
    void inorder();
    void levelOrder();

    // A recursive function to do inorder traversal
    void inorderHelper(Node *root) {
        if (root == NULL)
            return;

        inorderHelper(root->left);
        cout << root->data << "  ";
        inorderHelper(root->right);
    }

    /* A utility function to insert
        a new node with given key
       in BST */
    Node *BSTInsert(Node *root, Node *pt) {
        /* If the tree is empty, return a new node */
        if (root == NULL)
            return pt;

        /* Otherwise, recur down the tree */
        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        /* return the (unchanged) node pointer */
        return root;
    }

    // Utility function to do level order traversal
    void levelOrderHelper(Node *root) {
        if (root == NULL)
            return;

        std::queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            Node *temp = q.front();
            cout << temp->data << "  ";
            q.pop();

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

    void RBTree::rotateLeft(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != NULL)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_right;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;

        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void RBTree::rotateRight(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != NULL)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    // This function fixes violations
    // caused by BST insertion
    void RBTree::fixViolation(Node *&root, Node *&pt) {
        Node *parent_pt = NULL;
        Node *grand_parent_pt = NULL;

        while ((pt != root) && (pt->color != BLACK) &&
               (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            /*  Case : A
                Parent of pt is left child
                of Grand-parent of pt */
            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;

                /* Case : 1
                   The uncle of pt is also red
                   Only Recoloring required */
                if (uncle_pt != NULL && uncle_pt->color ==
                                            RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }

                else {
                    /* Case : 2
                       pt is right child of its parent
                       Left-rotation required */
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                       pt is left child of its parent
                       Right-rotation required */
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color,
                         grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            /* Case : B
               Parent of pt is right child
               of Grand-parent of pt */
            else {
                Node *uncle_pt = grand_parent_pt->left;

                /*  Case : 1
                    The uncle of pt is also red
                    Only Recoloring required */
                if ((uncle_pt != NULL) && (uncle_pt->color ==
                                           RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Case : 2
                       pt is left child of its parent
                       Right-rotation required */
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                       pt is right child of its parent
                       Left-rotation required */
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color,
                         grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    // Function to insert a new node with given data
    void RBTree::insert(const int &data) {
        Node *pt = new Node(data);

        // Do a normal BST insert
        root = BSTInsert(root, pt);

        // fix Red Black Tree violations
        fixViolation(root, pt);
    }

    // Function to do inorder and level order traversals
    void RBTree::inorder() { inorderHelper(root); }
    void RBTree::levelOrder() { levelOrderHelper(root); }

    void DisplayLevels() {
        std::cout << "[";
        if (!root) {
            std::cout << " ]\n";
            return;
        }
        std::queue<Node *> q;
        q.push(root);
        while (q.size()) {
            int size = q.size();
            while (size--) {
                std::cout << q.front()->val << "-" << (q.front()->red ? "R" : "B") << " ";
                if (q.front()->left)
                    q.push(q.front()->left);
                if (q.front()->right)
                    q.push(q.front()->right);
                q.pop();
            }
            std::cout << "\n";
        }
    }
};

int main() {
    RBTree tree;

    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();

    cout << "\n\nLevel Order Traversal of Created Tree\n";
    tree.levelOrder();

    return 0;
}