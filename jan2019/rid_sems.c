bsem mtx = init(1);
bsem rq = init(0);
bsem dq = init(0);
bsem aq = init(0);

int aw = 0, dw = 0, rw = 0;
int r_in = 0, w_in = 0, d_in = 0;

void read_enter(void) {
	down(mtx);
	if (dw > 0 OR d_in > 0) {
		rw++;
		up(mtx);
		down(rq);
		if (rw > 0) {
			rw--; r_in++; up(rq);
		}
		else
			up(mtx);
	}
	else {
		r_in++;
		up(mtx);
	}
}

void read_exit(void) {
	down(mtx);
	r_in--;
	if (r_in == 0 AND dw > 0 AND a_in == 0) {
		dw--; d_in++; up(dq);
	}
	else
		up(mtx);
}

void add_enter(void) {
	down(mtx);
	if (a_in > 0 OR d_in > 0) {
		aw++;
		up(mtx);
		down(aq);
	}
	else {
		a_in++;
		up(mtx);
	}
}

void add_exit(void) {
	down(mtx);
	a_in--;
	if (r_in == 0 AND dw > 0) {
		dw--; d_in++; up(dq);
	}
	else if (aw > 0) {
		aw--; a_in++; up(aq);
	}
	else
		up(mtx);
}

void del_enter(void) {
	down(mtx);
	if (aw > 0 OR rw > 0 OR r_in > 0 a_in > 0) {
		dw--;
		up(mtx);
		down(dq);
		if (dw > 0) {
			dw--; d_in++; up(dq);
		}
		else
			up(mtx);
	}
	else {
		d_in++;
		up(mtx);
	}
}

void del_exit(void) {
	down(mtx);
	d_in--;
	if (d_in == 0) {
		if (aw > 0 AND rw > 0) {
			aw--; a_in++; up(aq);
			rw--; r_in++; up(rq);
		}
		else if (aw > 0) {
			aw--; a_in++; up(aq);
		}
		else if (rw > 0) {
			rw--; r_in++; up(rq);
		}
		else 
			up(mtx);
	}
	else
		up(mtx);
}