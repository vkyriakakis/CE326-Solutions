monitor wagecage {
	condition want_pay;
	condition counter_free;
	condition teller_ready;

	int want_val;
	int counter_val;
	int teller_val;

	void init(void) {
		want_val = 0;
		counter_val = 1;
		teller_val = 0;
	}

	void barber_down(int *xval, condition x) {
		(*xval)--;
		if (*xval < 0) wait(x);
	}

	void barber_up(int *xval, condition x) {
		(*xval)++;
		if (xval <= 0) signal(x);
	}

	void client_pay(void) {
		barber_up(&want_val, want_pay);
		barber_down(&teller_val, teller_ready);
	}

	void teller_wait(void) {
		barber_down(&counter_val, counter_free);
		barber_down(&want_val, want_pay);
	}

	void teller_done(void) {
		barber_up(&teller_val, teller_ready);
		barber_up(&counter_val, counter_free);
	}
}

