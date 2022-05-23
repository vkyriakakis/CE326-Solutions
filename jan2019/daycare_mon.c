// open/sigcont (mporei na douleuei kai gia open/sigblock, exw kai zwh)
monitor daycare {
	condition tq, kq;
	int kids_in, kids_can;
	int kw, tw;

	void init(void) {
		kw = tw = 0;
		kids_in = kids_can = 0;
	}
	void kid_enter(void) {
		// If daycare full, the kid can sleep outside
		if (kids_in == kids_can) {
			kw++;
			wait(kq);
		}
		else
			kids_in++;
	}
	void teacher_enter(void) {
		int i;

		kids_can += N;

		// First check entering kids, then exiting teachers (prio(kids) > prio(teachers))
		if (kw > 0) { // 1:N ratio, each new teacher adds N to the capacity
			for (i = 0 ; i < N AND kw > 0 ; i++) {
				kw--; kids_in++; signal(kq);
			}
		}
		else if (tw > 0) { // 1 teacher enters, 1 leaves, no capacity changer
			tw--; kids_can -= N; signal(tq);
		}
	}
	void kid_exit(void) {
		kids_in--;
		// Priority to kids
		if (kw > 0) { // 1 kid exits, 1 kid enters, no change
			kids_in++; kw--; signal(kq);
		}
		// Let one teacher go, if your exit adjusted the ratio so
		// that they can
		else if (tw > 0 AND (kids_can - kids_in >= N)) {
			kids_can -= N; tw--; signal(tq);
		}
	}
	void teacher_exit(void) {
		// If the free kids "positions" are less than N
		// you can't leave, some kids depend on you
		if (kids_can - kids_in < N) {
			tw++;
			wait(tq);
		}
		else
			kids_can -= N;
	}
}

