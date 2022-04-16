void build(vector<int>& h){
	sort(h.begin(), h.end(), [](int x, int y){ return dfn[x] < dfn[y]; });
	sta[tp = 1] = 1; g[1].clear();
	for(int i = 0; i < h.size(); i++){
		int tmp = lca(h[i], sta[tp]);
		if(tmp != sta[tp]){
			while(dfn[tmp] < dfn[sta[tp - 1]])
			  g[sta[tp]].push_back(sta[tp - 1]), tp--;
			if(dfn[sta[tp - 1]] != dfn[tmp]){
				g[tmp].clear();
				g[tmp].push_back(sta[tp]);
				sta[tp] = tmp; 
			}else{
				g[tmp].push_back(sta[tp--]);
			}
		}
		g[h[i]].clear(); sta[++tp] = h[i];
	}
	for(int i = 1; i < tp; i++)
	  g[sta[i]].push_back(sta[i + 1]);
	return ;
}

