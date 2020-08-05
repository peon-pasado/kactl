template <class T>
struct minQueue {
	stack<T> l, r;
  T right_min;
  minQueue(): right_min(1e18) {}
  void add(T c) {
    r.push(c);
    right_min = min(right_min, c);
  }
	void pop() {
		if (l.empty()) {
      right_min = 1e18;
      while (!r.empty()) {
        if (l.empty()) l.push(r.top());
        else l.push(min(l.top(), r.top()));
        r.pop();
      }
      if (!l.empty()) l.pop();
    } else l.pop();
	}
	T get_min() {
		if (l.empty()) return right_min;
    return min(l.top(), right_min);
	}
};
