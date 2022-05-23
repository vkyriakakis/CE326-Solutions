// Dikaio gia ola ektos open/signal&block

monitor WC {
	condition q[2];
	int w[2];
	int in[2];

	void init(void) {
		w[0] = w[1] = 0;
		in[0] = in[1] = 0;
	}

	void enter_wc(int i) {
		if (w[!i] > 0 || in[i] == N || in[!i] > 0) {
			w[i]++;
			wait(q[i]);
		}
		else {
			in[i]++;
		}
	}

	void exit_wc(int i) {
		in[i]--;
		if (in[i] == 0 && w[!i] > 0) {
			do {
				in[!i]++;
				w[!i]--;
				signal(q[!i]);
			} while (w[!i] > 0 && in[!i] < N);
		}
		else if (w[!i] == 0 && w[i] > 0) {
			do {
				in[i]++;
				w[i]++;
				signal(q[i]);
			} while (w[i] > 0 && in[i] < N);
		}
	}
}