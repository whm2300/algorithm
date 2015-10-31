typedef struct tagNode {
    int value;
    struct tagNode *l;
    struct tagNode *r;
}Node;

//完全二叉树插入节点保持完全二叉树属性不变
Node *insert(Node *root, Node *new_node) {
    if (root == NULL || new_node == NULL) {
        return NULL;
    }

    if (root->l == NULL) {
        root->l = new_node;
        return root;
    } else if (root->r == NULL) {
        root->r = new_node;
        return root;
    }

    int lrc = 0;
    Node *p = root->l;
    while (p != NULL) {
        ++lrc;
        p = p->r;
    }
    int rrc = 0;
    p = root->r;
    while (p != NULL) {
        ++rrc;
        p = p->r;
    }

    if (lrc == rrc) {
        insert(root->l, new_node);
    } else {
        insert(root->r, new_node);
    }
}

//计算完全二叉树节点数目
int count(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int lh = 0;
    Node *p = root->l;
    while (p != NULL) {
        ++lh;
        p = p->l;
    }
    int rh = 0;
    p = root->r;
    while (p != NULL) {
        ++rh;
        p = p->r;
    }
    if (lh == rh) {
        return pow(2, lh+1) - 1;
    } else {
        return count(root->l) + count(root->r) + 1;
    }
}
