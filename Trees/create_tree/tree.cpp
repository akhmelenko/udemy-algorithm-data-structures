
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
#include <algorithm>

template <typename T>
class Tree
{
private:
    struct Node
    {
        T val;
        Node *left = nullptr;
        Node *right = nullptr;
    };
    Node *root = nullptr;

    void DisplayRecPre(Node *node)
    {
        if (!node)
            return;
        std::cout << node->val << " ";
        DisplayRecPre(node->left);
        DisplayRecPre(node->right);
    }

    void DisplayRecIn(Node *node)
    {
        if (!node)
            return;
        DisplayRecIn(node->left);
        std::cout << node->val << " ";
        DisplayRecIn(node->right);
    }

    void DisplayRecPost(Node *node)
    {
        if (!node)
            return;
        DisplayRecPost(node->left);
        DisplayRecPost(node->right);
        std::cout << node->val << " ";
    }

    void DisplayRecByLevels(std::queue<Node *> &q)
    {
        if (!q.size())
            return;
        int levelSize = q.size();
        while (levelSize--)
        {
            // process node
            std::cout << q.front()->val << " ";
            // put children to queue
            if (q.front()->left)
                q.push(q.front()->left);
            if (q.front()->right)
                q.push(q.front()->right);
            // clear current node
            q.pop();
        }
        std::cout << "\n";
        DisplayRecByLevels(q);
    }

    bool IsCurrentRight4DisplayPostStack(std::stack<Node *> &s)
    {
        if (s.size() < 2)
            return false;
        Node *temp = s.top();
        bool res;
        s.pop();
        if (temp == s.top())
            res = true;
        else
            res = false;
        s.push(temp);
        return res;
    }

    Node *CreateBtFromPreAndInRec(std::vector<T> &pv, std::vector<T> iv)
    {
        if (!iv.size() || !pv.size())
            return nullptr;
        // get local root
        Node *node = new Node{};
        node->val = pv[0];
        auto it = std::find(iv.begin(), iv.end(), pv[0]);
        pv.erase(pv.begin());
        std::vector<T> ivLeft(iv.begin(), it);
        std::vector<T> ivRight(it + 1, iv.end());
        node->left = CreateBtFromPreAndInRec(pv, ivLeft);
        node->right = CreateBtFromPreAndInRec(pv, ivRight);
        return node;
    }

    int CountNodesRec(Node *node)
    {
        if (!node)
            return 0;
        return CountNodesRec(node->left) + CountNodesRec(node->right) + 1;
    }

    int CountHeightRec(Node *node)
    {
        if (!node)
            return 0;
        int left = CountHeightRec(node->left);
        int right = CountHeightRec(node->right);
        if (left > right)
            return left + 1;
        return right + 1;
    }

    int CountDegree1Rec(Node *node)
    {
        if (!node)
            return 0;
        int left = CountDegree1Rec(node->left);
        int right = CountDegree1Rec(node->right);
        if (!node->left && node->right ||
            node->left && !node->right)
            return left + right + 1;
        return left + right;
    }

    int CountDegree2Rec(Node *node)
    {
        if (!node)
            return 0;
        int left = CountDegree2Rec(node->left);
        int right = CountDegree2Rec(node->right);
        if (node->left && node->right)
            return left + right + 1;
        return left + right;
    }

    int CountNodesSummRec(Node *node)
    {
        if (!node)
            return 0;
        return CountNodesSummRec(node->left) + CountNodesSummRec(node->right) + node->val;
    }

    int CountLeafsRec(Node *node)
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return 1;
        return CountLeafsRec(node->left) + CountLeafsRec(node->right);
    }

    Node *SearchInBtsRec(Node *node, const T &val)
    {
        if (!node)
            return nullptr;
        if (node->val == val)
            return node;
        else if (node->val > val)
            return SearchInBtsRec(node->left, val);
        else
            return SearchInBtsRec(node->right, val);
    }

    Node *InsertInBtsRec(Node *node, const T &val)
    {
        if (!node)
        {
            node = new Node;
            node->val = val;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        if (node->val > val)
            node->left = InsertInBtsRec(node->left, val);
        else
            node->right = InsertInBtsRec(node->right, val);
        return node;
    }

    Node *MaxNodeBst(Node *node)
    {
        if (!node)
            return nullptr;
        Node *local = node;
        while (local->right)
        {
            local = local->right;
        }
        return local;
    }

    Node *MinNodeBst(Node *node)
    {
        if (!node)
            return nullptr;
        Node *local = node;
        while (local->left)
        {
            local = local->left;
        }
        return local;
    }

    Node *DeleteFromBstRec(Node *node, const T &val)
    {
        if (!node)
            return nullptr;
        if (node->val > val)
            node->left = DeleteFromBstRec(node->left, val);
        else if (node->val < val)
            node->right = DeleteFromBstRec(node->right, val);
        else
        {
            // node->val = val
            if (!node->left && !node->right)
            {
                // no children
                delete node;
                return nullptr;
            }
            else if (!node->left && node->right || node->left && !node->right)
            {
                // one child
                Node *temp;
                if (node->left)
                    temp = node->left;
                else
                    temp = node->right;
                delete node;
                return temp;
            }
            else
            {
                // 2 children
                // compare the height
                if (CountHeightRec(node->left) > CountHeightRec(node->right))
                {
                    // get from left
                    Node *temp = MaxNodeBst(node->left);
                    node->val = temp->val;
                    node->left = DeleteFromBstRec(node->left, temp->val);
                }
                else
                {
                    // get form right
                    Node *temp = MinNodeBst(node->left);
                    node->val = temp->val;
                    node->right = DeleteFromBstRec(node->right, temp->val);
                }
            }
        }
        return node;
    }

    int NodeBalanceFactor(Node *node)
    {
        if (!node)
            return 0;
        return CountHeightRec(node->left) - CountHeightRec(node->right);
    }

    bool IsNodeBalanced(Node *node)
    {
        if (!node)
            return true;
        return abs(NodeBalanceFactor(node)) <= 1;
    }

    bool IsBtsBalancedRec(Node *node)
    {
        if (!node)
            return true;
        return IsNodeBalanced(node) && IsBtsBalancedRec(node->left) && IsBtsBalancedRec(node->right);
    }

    // nullptr - all balanced; other - node pointer
    Node *GetUnbalancedNodeRec(Node *node)
    {
        // IMPORTANT : search ublalanced node from children to parent
        if (!node)
            return nullptr;
        // ! first check children
        Node *left = GetUnbalancedNodeRec(node->left);
        Node *right = GetUnbalancedNodeRec(node->right);
        if (left)
            return left;
        else if (right)
            return right;
        else if (!IsNodeBalanced(node)) // check parent at the end
            return node;
        return nullptr;
    }

    // nullptr - all balanced; other - node pointer
    Node *GetUnbalancedNode()
    {
        // IMPORTANT : search ublalanced node from children to parent
        return GetUnbalancedNodeRec(root);
    }

public:
    Tree() { root = nullptr; };
    ~Tree(){};

    void Create(const std::vector<std::pair<bool, T>> &v)
    {
        if (!v.size() || !v[0].first)
            return;
        std::queue<Node *> q;
        // create root
        root = new Node;
        root->val = v[0].second;
        root->left = nullptr;
        root->right = nullptr;
        q.push(root);
        int i = 0;
        while (q.size())
        {
            // create left
            i++;
            if (i < v.size() && v[i].first)
            {
                Node *left = new Node;
                // set link from parent
                q.front()->left = left;
                left->val = v[i].second;
                // NULL children (we not shue are the exists)
                left->left = nullptr;
                left->right = nullptr;
                // add left to queue
                q.push(left);
            }
            // create right
            i++;
            if (i < v.size() && v[i].first)
            {
                Node *right = new Node;
                // set link from parent
                q.front()->right = right;
                right->val = v[i].second;
                // NULL children (we not shue are the exists)
                right->left = nullptr;
                right->right = nullptr;
                // add right to queue
                q.push(right);
            }
            // delete parent from queue
            q.pop();
        }
    }

    void CreateBtFromPreAndIn(std::vector<T> pv, std::vector<T> iv)
    {
        root = CreateBtFromPreAndInRec(pv, iv);
    }

    void DisplayPre()
    {
        std::cout << "[ ";
        DisplayRecPre(root);
        std::cout << "]\n";
    }

    void DisplayIn()
    {
        std::cout << "[ ";
        DisplayRecIn(root);
        std::cout << "]\n";
    }

    void DisplayPost()
    {
        std::cout << "[ ";
        DisplayRecPost(root);
        std::cout << "]\n";
    }

    void DisplayByLevels()
    {
        std::cout << "[ ";
        if (!root)
        {
            std::cout << "]";
            return;
        }
        std::queue<Node *> q;
        q.push(root);
        DisplayRecByLevels(q);
        std::cout << "]\n";
    }

    void DisplayPreStack()
    {
        std::cout << "[ ";
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            if (node)
            {
                // process node
                std::cout << node->val << " ";
                s.push(node);
                // go left
                node = node->left;
            }
            else
            {
                // go right
                node = s.top()->right;
                s.pop();
            }
        }
        std::cout << "]\n";
    }

    void DisplayInnStack()
    {
        std::cout << "[ ";
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            if (node)
            {
                s.push(node);
                // go left
                node = node->left;
            }
            else
            {
                // process node
                std::cout << s.top()->val << " ";
                // go right
                node = s.top()->right;
                s.pop();
            }
        }
        std::cout << "]\n";
    }

    // push stack every child enter
    void DisplayPostStack()
    {
        std::cout << "[ ";
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            if (node)
            {
                s.push(node);
                // go left
                node = node->left;
            }
            else
            {
                // process parent while right
                while (IsCurrentRight4DisplayPostStack(s))
                {
                    std::cout << s.top()->val << " ";
                    s.pop();
                    s.pop();
                }
                if (!s.size())
                    continue;
                // now left
                s.push(s.top()); // now left
                node = s.top()->right;
            }
        }
        std::cout << "]\n";
    }

    void DisplayIterByLevels()
    {
        std::cout << "[ ";
        if (!root)
        {
            std::cout << "]\n";
            return;
        }
        std::queue<Node *> q;
        q.push(root);
        while (q.size())
        {
            // process front node
            std::cout << q.front()->val << " ";
            // push children to queue
            if (q.front()->left)
                q.push(q.front()->left);
            if (q.front()->right)
                q.push(q.front()->right);
            // pop parent from queue
            q.pop();
        }
        std::cout << "]\n";
    }

    void DisplayPreStack2()
    {
        std::cout << "[ ";
        if (!root)
        {
            std::cout << "]\n";
            return;
        }
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            // process node
            std::cout << node->val << " ";
            // check children exists
            if (!node->left && !node->right)
            {
                // if no children and stack empty - finish
                if (!s.size())
                {
                    std::cout << "]\n";
                    return;
                }
                // if no children and stack not empyt - go right
                if (s.top()->right)
                    node = s.top()->right;
                s.pop();
                continue;
            }
            s.push(node);
            // go left
            if (node->left)
            {
                node = node->left;
                continue;
            }
            // go right
            node = node->right;
        }
        std::cout << "]\n";
    }

    void DisplayInnStack2()
    {
        std::cout << "[ ";
        if (!root)
        {
            std::cout << "]\n";
            return;
        }
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            // check children exists
            if (!node->left && !node->right)
            {
                // process node
                std::cout << node->val << " ";
                // if no children and stack empty - finish
                if (!s.size())
                {
                    std::cout << "]\n";
                    return;
                }
                // if no children and stack not empty - go right
                if (s.top()->right)
                    node = s.top()->right;
                // process node
                std::cout << s.top()->val << " ";
                s.pop();
                continue;
            }
            s.push(node);
            // go left
            if (node->left)
            {
                node = node->left;
                continue;
            }
            // go right
            node = node->right;
        }
        std::cout << "]\n";
    }

    void DisplayPostStack2()
    {
        std::cout << "[ ";
        if (!root)
        {
            std::cout << "]\n";
            return;
        }
        std::stack<Node *> s;
        Node *node = root;
        while (s.size() || node)
        {
            // check children exists
            if (!node->left && !node->right)
            {
                // process node
                std::cout << node->val << " ";
                // if no children and stack empty - finish
                if (!s.size())
                {
                    std::cout << "]\n";
                    return;
                }

                // if current left - go rigth
                if (node == s.top()->left)
                {
                    node = s.top()->right;
                    continue;
                }

                // if current not left - process parrent, remove parent and go upper level right
                // process parent
                std::cout << s.top()->val << " ";
                // remove parent
                s.pop();
                if (s.size())
                {
                    node = s.top()->right;
                    continue;
                }
                else
                {
                    std::cout << "]\n";
                    return;
                }
            }
            s.push(node);
            // go left
            if (node->left)
            {
                node = node->left;
                continue;
            }
            // go right
            node = node->right;
        }
        std::cout << "]\n";
    }

    int CountNodes()
    {
        return CountNodesRec(root);
    }

    int CountHeight()
    {
        if (!root)
            return -1;
        return CountHeightRec(root) - 1;
    }

    int CountDegree2()
    {
        if (!root)
            return -1;
        return CountDegree2Rec(root);
    }

    int CountNodesSumm()
    {
        return CountNodesSummRec(root);
    }

    int CountLeafs()
    {
        return CountLeafsRec(root);
    }

    int CountDegree1()
    {
        return CountDegree1Rec(root);
    }

    Node *SearchInBts(const T &val)
    {
        return SearchInBtsRec(root, val);
    }

    Node *SearchInBtsIter(const T &val)
    {
        if (!root)
            return nullptr;
        Node *node = root;
        while (node)
        {
            if (node->val == val)
                return node;
            else if (node->val > val)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    bool InsertInBtsIter(const T &val)
    {
        if (!root)
        {
            root = new Node;
            root->val = val;
            root->left = nullptr;
            root->right = nullptr;
            return true;
        }
        Node *node = root;
        Node *prev = nullptr;
        while (node)
        {
            prev = node;
            if (node->val == val)
                return false;
            else if (node->val > val)
                node = node->left;
            else
                node = node->right;
        }
        // node == nullptr
        node = new Node;
        node->val = val;
        node->left = nullptr;
        node->right = nullptr;
        if (prev->val > node->val)
            prev->left = node;
        else
            prev->right = node;
        return true;
    }

    Node *InsertInBts(const T &val)
    {
        // Node *node = InsertInBtsRec(root, val);
        // if (!root)
        //     root = node;
        // return node;
        root = InsertInBtsRec(root, val);
        return root;
    }

    void AddElementsToBst(const std::vector<T> &v)
    {
        for (auto val : v)
            InsertInBts(val);
    }

    bool DeleteFromBst(const T &val)
    {
        if (!root)
            return false;
        return DeleteFromBstRec(root, val);
    }

    bool CreateBstFromPreorder(const std::vector<T> &pv)
    {
        if (!pv.size())
            return false;
        std::stack<Node *> s;
        Node *node = root;
        node = new Node;
        node->val = pv[0];
        node->left = nullptr;
        node->right = nullptr;
        root = node;
        for (int i = 1; i < pv.size(); i++)
        {
            if (node && pv[i] == node->val)
                return false;
            if (pv[i] < node->val)
            { // go left
                node->left = new Node;
                s.push(node);
                node = node->left;
            }
            else
            { // go right
                while (s.size() && pv[i] > s.top()->val)
                {
                    // go right from stack
                    node = s.top();
                    s.pop();
                }
                node->right = new Node;
                node = node->right;
            }
            node->val = pv[i];
            node->left = nullptr;
            node->right = nullptr;
        }
        return true;
    }

    bool CreateBstFromPostorder(const std::vector<T> &pv)
    {
        if (!pv.size())
            return false;
        std::stack<Node *> s;
        Node *node = root;
        node = new Node;
        node->val = pv[pv.size() - 1];
        node->left = nullptr;
        node->right = nullptr;
        root = node;
        for (int i = pv.size() - 2; i >= 0; i--)
        {
            if (node && pv[i] == node->val)
                return false;
            if (pv[i] > node->val)
            { // go right
                node->right = new Node;
                s.push(node);
                node = node->right;
            }
            else
            { // go left
                while (s.size() && pv[i] < s.top()->val)
                {
                    // go left from stack
                    node = s.top();
                    s.pop();
                }
                node->left = new Node;
                node = node->left;
            }
            node->val = pv[i];
            node->left = nullptr;
            node->right = nullptr;
        }
        return true;
    }

    /*
      UP
      |
      A (base addr)
     / \
    B   Ar
   / \
  Bl  Br

           ||
           \/
           
           UP
           |
           B (base addr) - must stay the same!
          / \
         Bl  A
            / \
           Br Ar
           */

    bool LLRotate(Node *baseNode)
    {
        std::cout << "LLRotate: \n";
        if (!baseNode || !baseNode->left)
        {
            std::cout << "false\n";
            return false;
        }
        // 0) Copy baseNode to A pointer
        Node *A = baseNode;
        // 0) Copy B pointer
        Node *B = baseNode->left;
        // 1) set A->left point to Bl
        A->left = B->left;
        // 2) set B->left point to Br
        B->left = B->right;
        // 3) set B->right point to Ar
        B->right = A->right;
        // 4) set A->right point to B
        A->right = B;
        // 5) swap A->val and B->val
        T temp = A->val;
        A->val = B->val;
        B->val = temp;
        return true;
    }

    // mirror from LLRotate (left to right; right to left)
    bool RRRotate(Node *baseNode)
    {
        std::cout << "RRRotate: \n";
        if (!baseNode || !baseNode->right)
        {
            std::cout << "false\n";
            return false;
        }
        Node *A = baseNode;
        Node *B = baseNode->right;
        A->right = B->right;
        B->right = B->left;
        B->left = A->left;
        A->left = B;
        T temp = A->val;
        A->val = B->val;
        B->val = temp;
        return true;
    }

    /*
      UP
      |
      A (base addr)
     / \
    B   Ar
   / \
  Bl  C
     / \
    Cl  Cr

       ||
       \/

       UP 
       |
       C (base addr) - must stay the same!
      /  \
     B    A
    / \  / \
   Bl Cl Cr Ar
   */

    bool LRRotate(Node *baseNode)
    {
        std::cout << "LRRotate: \n";
        if (!baseNode || !baseNode->left || !baseNode->left->right)
        {
            std::cout << "false\n";
            return false;
        }
        // 0) Copy A ptr
        Node *A = baseNode;
        // 0) Copy B ptr
        Node *B = baseNode->left;
        // 0) copy C ptr
        Node *C = baseNode->left->right;
        // 1) set B->right point to Cl
        B->right = C->left;
        // 2) set C->left point to Cr
        C->left = C->right;
        // 3) set C->right point to Ar
        C->right = A->right;
        // 4) set A->right point to C
        A->right = C;
        // 5) swap A->val and C->val
        T temp = A->val;
        A->val = C->val;
        C->val = temp;
        return true;
    }

    // mirror from LRRotate (left to right; right to left)
    bool RLRotate(Node *baseNode)
    {
        std::cout << "RLRotate: \n";
        if (!baseNode || !baseNode->right || !baseNode->right->left)
        {
            std::cout << "false\n";
            return false;
        }
        Node *A = baseNode;
        Node *B = baseNode->right;
        Node *C = baseNode->right->left;
        B->left = C->right;
        C->right = C->left;
        C->left = A->left;
        A->left = C;
        T temp = A->val;
        A->val = C->val;
        C->val = temp;
        return true;
    }

    bool IsBtsBalanced()
    {
        return IsBtsBalancedRec(root);
    }

    void InsertInAvl(const T &val)
    {
        InsertInBts(val);
        // IMPORTANT : search ublalanced node from children to parent
        Node *unbalNode = GetUnbalancedNode();
        if (unbalNode)
        {
            if (NodeBalanceFactor(unbalNode) > 1 && NodeBalanceFactor(unbalNode->left) > 0)
                LLRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) > 1 && NodeBalanceFactor(unbalNode->left) < 0)
                LRRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) < -1 && NodeBalanceFactor(unbalNode->right) < 0)
                RRRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) < -1 && NodeBalanceFactor(unbalNode->right) > 0)
                RLRotate(unbalNode);
        }
        // debag check
        if (GetUnbalancedNode())
            std::cout << "DEBUG UNBAL\n";
        return;
    }

    void TransformBstToAvl()
    {
        // IMPORTANT : search ublalanced node from children to parent
        // balancing until ubalNode != nullptr
        while (Node *unbalNode = GetUnbalancedNode())
        {
            if (NodeBalanceFactor(unbalNode) > 1 && NodeBalanceFactor(unbalNode->left) > 0)
                LLRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) > 1 && NodeBalanceFactor(unbalNode->left) < 0)
                LRRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) > 1) // ublanced with perfect left child
                // can choose any (LL or LR)
                LLRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) < -1 && NodeBalanceFactor(unbalNode->right) < 0)
                RRRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) < -1 && NodeBalanceFactor(unbalNode->right) > 0)
                RLRotate(unbalNode);
            else if (NodeBalanceFactor(unbalNode) < 1) // ublanced with perfect right child
                // can choose any (RR or RL)
                RRRotate(unbalNode);
            std::cout << "DEBUG BALANCING\n";
        }
    }

    void DeleteFromAvl(const T &val)
    {
        DeleteFromBst(val);
        // chech for unbalance
        if (GetUnbalancedNode())
        {
            TransformBstToAvl();
        }
    }
};

int main()
{
    Tree<int> t;
    // t.Create({{true, 1}, {true, 2}, {true, 3}, {false, 22}, {false, 22}, {true, 4}, {true, 5}});
    t.Create({{true, 1}, {true, 2}, {true, 3}, {true, 4}, {true, 5}});
    t.DisplayPre();
    t.DisplayIn();
    t.DisplayPost();
    t.DisplayByLevels();
    t.DisplayPreStack();
    t.DisplayInnStack();
    t.DisplayPostStack();
    t.DisplayIterByLevels();

    std::cout << "\n BT utils ==\n";
    std::vector<int> pre{4, 7, 9, 6, 3, 2, 5, 8, 1};
    std::vector<int> in{7, 6, 9, 3, 4, 5, 8, 2, 1};
    Tree<int> t2;
    t2.CreateBtFromPreAndIn(pre, in);
    t2.DisplayPre();
    t2.DisplayIterByLevels();
    std::cout << t2.CountNodes() << "\n";
    std::cout << t2.CountHeight() << "\n";
    std::cout << t2.CountDegree2() << "\n";
    std::cout << t2.CountNodesSumm() << "\n";
    std::cout << t2.CountLeafs() << "\n";
    std::cout << t2.CountDegree1() << "\n";

    std::cout << "\n BTS ==\n";
    Tree<int> bts;
    pre = {14, 9, 1, 3, 13, 28, 15, 29, 31};
    in = {1, 3, 9, 13, 14, 15, 28, 29, 31};
    bts.CreateBtFromPreAndIn(pre, in);
    bts.DisplayPre();
    std::cout << "rec is 29 found = "
              << (bts.SearchInBts(29) ? bts.SearchInBts(29)->val : 0) << "\n";
    std::cout << "rec is 19 found = "
              << (bts.SearchInBts(19) ? bts.SearchInBts(19)->val : 0) << "\n";
    std::cout << "iter is 29 found = "
              << (bts.SearchInBtsIter(29) ? bts.SearchInBtsIter(29)->val : 0) << "\n";
    std::cout << "iter is 19 found = "
              << (bts.SearchInBtsIter(19) ? bts.SearchInBtsIter(19)->val : 0) << "\n";
    bts.InsertInBtsIter(7);
    bts.DisplayPre();
    bts.InsertInBts(17);
    bts.DisplayPre();
    Tree<int> bts2;
    bts2.AddElementsToBst({14, 3, 7, 11, 13, 19, 26, 29});
    bts2.DisplayIn();
    bts2.DisplayByLevels();
    bts2.DeleteFromBst(19);
    bts2.DisplayIn();
    bts2.DisplayByLevels();
    bts2.DeleteFromBst(26);
    bts2.DisplayIn();
    bts2.DisplayByLevels();
    bts2.DeleteFromBst(7);
    bts2.DisplayIn();
    bts2.DisplayByLevels();
    bts2.DeleteFromBst(14);
    bts2.DisplayIn();
    bts2.DisplayByLevels();
    bts2.DeleteFromBst(13);
    bts2.DisplayIn();
    bts2.DisplayByLevels();

    std::cout << "\n BTS from pre==\n";
    Tree<int> bts3;
    bts3.CreateBstFromPreorder({30, 20, 10, 15, 25, 40, 50, 45});
    bts3.DisplayPre();
    bts3.DisplayIn();
    bts3.DisplayByLevels();

    std::cout << "\n BTS from post==\n";
    Tree<int> bts4;
    bts4.CreateBstFromPostorder({15, 10, 25, 20, 45, 50, 40, 30});
    bts4.DisplayPost();
    bts4.DisplayPre();
    bts4.DisplayIn();
    bts4.DisplayByLevels();
    // std::cout << "LL rotate\n";
    // bts4.LLRotate();
    // bts4.DisplayByLevels();
    // std::cout << "RR rotate\n";
    // bts4.RRRotate();
    // bts4.DisplayByLevels();
    // std::cout << "insert more to root->left->right:\n";
    // bts4.InsertInBts(27);
    // bts4.InsertInBts(22);
    // bts4.DisplayByLevels();
    // std::cout << "LR rotate\n";
    // bts4.LRRotate();
    // bts4.DisplayByLevels();
    std::cout << "insert more to root->right->left:\n";
    bts4.InsertInBts(29);
    bts4.InsertInBts(26);
    bts4.DisplayByLevels();
    // std::cout << "RL rotate\n";
    // bts4.RLRotate();
    // bts4.DisplayByLevels();
    std::cout << "is Balanced?=" << bts4.IsBtsBalanced() << "\n";
    bts4.DeleteFromBst(15);
    bts4.DeleteFromBst(45);
    bts4.DisplayByLevels();
    std::cout << "is Balanced?=" << bts4.IsBtsBalanced() << "\n";

    std::cout << "AVL ==\n";
    Tree<int> avl;
    avl.InsertInAvl(20);
    avl.DisplayByLevels();
    avl.InsertInAvl(60);
    avl.DisplayByLevels();
    avl.InsertInAvl(40);
    avl.DisplayByLevels();
    avl.InsertInAvl(80);
    avl.DisplayByLevels();
    avl.InsertInAvl(70);
    avl.DisplayByLevels();
    avl.InsertInAvl(10);
    avl.DisplayByLevels();
    avl.InsertInAvl(90);
    avl.DisplayByLevels();
    avl.InsertInAvl(85);
    avl.DisplayByLevels();

    std::cout << " BST to AVL ==\n";
    bts.DisplayByLevels();
    bts.TransformBstToAvl();
    bts.DisplayByLevels();
    bts3.DisplayByLevels();
    bts3.TransformBstToAvl();
    bts3.DisplayByLevels();

    std::cout << " newBST to AVL ==\n";
    Tree<int> bst;
    bst.AddElementsToBst({50, 30, 90, 100, 120, 95});
    bst.DisplayByLevels();
    bst.TransformBstToAvl();
    bst.DisplayByLevels();

    std::cout << " newBST2 to AVL ==\n";
    Tree<int> bst2;
    bst2.AddElementsToBst({50, 30, 90, 100, 120, 95, 20, 10, 25});
    bst2.DisplayByLevels();
    bst2.TransformBstToAvl();
    bst2.DisplayByLevels();

    std::cout << " delete from AVL ==\n";
    bst2.DisplayByLevels();
    bst2.DeleteFromAvl(120);
    bst2.DisplayByLevels();
    bst2.DeleteFromAvl(10);
    bst2.DisplayByLevels();

    return 0;
}