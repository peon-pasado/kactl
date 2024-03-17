/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

ll rec(ll N, int K) {
  if (N <= 1 || K < 0) return 0;
  if (N <= P[K]) return N-1;
  if (N < MAXN && 1ll * P[K]*P[K] > N) return N-1 - prec[N] + prec[P[K]];
  const int LIM = 250;
  static int memo[LIM*LIM][LIM];
  bool ok = N < LIM*LIM;
  if (ok && memo[N][K]) return memo[N][K];
  ll ret = N/P[K] - rec(N/P[K], K-1) + rec(N, K-1);
  if (ok) memo[N][K] = ret;
  return ret;
}

ll count_primes(ll N) { // less than or equal to
  if (N < MAXN) return prec[N];
  int K = prec[(int)sqrt(N) + 1];
  return N-1 - rec(N, K) + prec[P[K]];
}
