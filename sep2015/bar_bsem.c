bsem mtx = init(1);
bsem q = init(0);
int cnt = 0;

void barrier_wait(void) {
	down(mtx);
	cnt++;
	if (cnt == N)
		up(q);
	else
		up(mtx);

	down(q);
	cnt--;
	if (cnt == 0)
		up(mtx);
	else
		up(q);
}

