/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

template<class T> 
struct cvxHull {
    using P = Point<T>;
    using F = function<bool(P,P)>;
    deque<P> at;
    F r;
    cvxHull(F cmp = [](P p, P q) {return (p ^ q)>=0;}): r(cmp) {}
    //se necesita que x1 > x2 > ... (si hay empates yi en orden creciente)
    void push(P nw) {
        while (sz(at)>1&&r(at.back()-at[sz(at)-2], nw-at[sz(at)-2])) at.popb();
        at.pushb(nw);
    }
    T f(P p, P q) {
        return p*q;
    }
    //para remover se necesita que las consultas sean no decrecientes x1 <= x2 ...
    void remove(T x) {
        return remove(P(x, 1));
    }
    void remove(P nw) {
        while (sz(at)>1&&f(nw,at[0])>f(nw,at[1])) at.popf();
    }
    T query_front(T x) {
        return query_front(P(x, 1));
    }
    T query_front(P nw) {
        return f(nw, at[0]);
    }
    T query(T x) {
        return query(P(x, 1));
    }
    T query(P nw) {
        int lo=-1, hi=sz(at)-1;
        while (lo+1<hi) {
            int mi=lo+(hi-lo)/2;
            (f(nw, at[mi]) > f(nw, at[mi+1]) ? lo : hi) = mi;
        }
        return f(nw, at[hi]);
    }
};
