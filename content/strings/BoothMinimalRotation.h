/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

int booth(string s){
	s += s;
	int n = s.size();
	vector<int> pi(n, 0);
	int k = 0;
	for(int i = 1; i < n; i++){
		int p = pi[i - k - 1];
		while(p > 0 and s[i] != s[k + p]){
			if(s[i] < s[k + p]) k = i - p;
			p = pi[p - 1];
		}
		if(s[i] != s[k + p]){
			if(s[i] < s[k]) k = i;
			pi[i - k] = 0;
		}
		else{
			pi[i - k] = p + 1;
		}
	}
	return k;
}
