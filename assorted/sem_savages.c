// GLOBALS:
int tourists = 0;
bsem mtx = init(1);
bsem pot_empty = init(0);
bsem cook_wait = init(0);

void run_savage(void) {
	down(mtx);

	// Check if there is any food available
	if (tourists == 0) {
		// If not, wait for the cook to refill
		up(cook_wait);
		down(pot_empty);
	}

	// Consume
	tourists--;

	up(mtx);
}

void run_cook(void) {
	while(1) {
		down(cook_wait);
		tourists = N;
		up(pot_empty);
	}
}

