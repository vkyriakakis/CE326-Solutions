bsem mtx = init(1);
bsem oq = init(0), nq = init(0);
int n_in = 0, o_in = 0, ow = 0, nw = 0;

olympiakos {
	down(mtx);
	if (n_in > N || (n_in > 0 && o_in == N) || o_in == 2N) {
		ow++;
		up(mtx);
		down(oq);
		o_in++; // board
		if (o_in < 2N && ow > 0) {
			ow--;
			up(oq);
		}
		else
			up(mtx);
	}
	else {
		o_in++; //board
		up(mtx);
	}
}

nikioths {
	down(mtx);
	if (o_in > N || (o_in > 0 && n_in == N) || n_in == 2N) {
		nw++;
		up(mtx);
		down(nq);
		n_in++; // board
		if (n_in < 2N && nw > 0) {
			nw--;
			up(nq);
		}
		else
			up(mtx);
	}
	else {
		n_in++; //board
		up(mtx);
	}
}