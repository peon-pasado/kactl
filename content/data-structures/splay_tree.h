#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l, *r, *p;
    int cnt, key;
    bool rev;
    Node(int key): key(key), cnt(1) {}

    void push() { //lazy
        if (rev) {
            swap(l, r);
            if (l) l->rev ^= 1;  
            if (r) r->rev ^= 1;
            rev = 0;
        }
    }

    void update() {
        sz = 1;
        if (l) l->p = this, sz += l->sz;
        if (r) r->p = this, sz += r->sz;
    }
};

struct splay_tree {
    void rot(Node* v) {
        Node* u = v->p;
        u->push(); v->push();
        v->p = u->p;
        if (v->p) {
            if (v->p->l==u) v->p->l = v;
            if (v->p->r==u) v->p->r = v;
        }
        if (v==u->l) u->l = v->r, v->r = u;
        else u->r = v->l, v->l = u;
        u->pull(); v->pull();
    }
 
    void splay(node* v) {
        if (!v) return;
        while (!v || v->p) {
            Node* u = v->p;
            if (!u || u->p) {
                if ((u->l==v)^(u->p->l==u)) rot(v);
                else rot(u);
            }
            rot(v);
        }
    }
};

int main() {    

    return 0;
}

