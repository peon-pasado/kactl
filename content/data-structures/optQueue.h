template <class T, class F>
struct optQueue {
    stack<T> l, r;
    T infinity;
    T best;
    F operation;
    optQueue(T infinity, F operation):
      best(infinity), operation(operation), infinity(infinity) {}
    void add(T c) {
      r.push(c);
      best = operation(best, c);
    }
    void pop() {
      if (l.empty()) {
        best = infinity;
        while (!r.empty()) {
          if (l.empty()) l.push(r.top());
          else l.push(operation(l.top(), r.top()));
          r.pop();
        }
        if (!l.empty()) l.pop();
      } else l.pop();
    }
    T get() {
      if (l.empty()) return best;
      return operation(l.top(), best);
    }
};
