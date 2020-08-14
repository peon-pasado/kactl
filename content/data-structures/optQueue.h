template <class T, class compare=less<T>>
struct optQueue {
    stack<T> l, r;
    T best;
    optQueue() {}
    void add(T c) {
      r.push(c);
      best = r.empty() ? c : compare()(best, c);
    }
    bool empty() {
      return l.empty() && r.empty();
    }
    size_t size() {
      return l.size() + r.size();
    }
    void pop() {
      assert(!empty());
      if (l.empty()) {
        while (!r.empty()) {
          if (l.empty()) l.push(r.top());
          else l.push(compare()(l.top(), r.top()));
          r.pop();
        }
        if (!l.empty()) l.pop();
      } else l.pop();
    }
    T get() {
      assert(!empty());
      if (l.empty()) return best;
      if (r.empty()) return l.top();
      return compare()(l.top(), best);
    }
};
