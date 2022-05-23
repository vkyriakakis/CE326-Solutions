monitor coffee_converter {
	int ingr_val;
	int coffee_empty;
	int sugar_empty;
	int coffee_pcs;
	int sugar_pcs;

	condition not_sugar_full;
	condition not_coffee_full;
	condition ingredients_rdy;

	void init(void) {
		ingr_val = 0;
		coffee_empty = N;
		sugar_empty = M;
		coffee_pcs = sugar_pcs = 0;
	}

	void barber_up(int *x_val, condition x_cond) {
		(*x_val)++; if (*x_val <= 0) signal(x_cond);
	}

	void barber_down(int *x_val, condition x_cond) {
		(*x_val)--; if (*x_val < 0) wait(x_cond);
	}

	void add1sugar(void) {
		barber_down(&sugar_empty, not_sugar_full);

		sugar_pcs++;
		if (sugar_pcs => 1 && coffee_pcs => 2) {
			sugar_pcs--;
			coffee_pcs -= 2;

			barber_up(&ingr_val, ingredients_rdy);
		}
	}

	void add1coffee(void) {
		barber_down(&coffee_empty, not_coffee_full);

		coffee_pcs++;
		if (sugar_pcs => 1 && coffee_pcs => 2) {
			sugar_pcs--;
			coffee_pcs -= 2;

			barber_up(&ingr_val, ingredients_rdy);
		}
	}

	void rmv2coffee1sugar(void) {
		barber_down(&ingr_val, ingredients_rdy);
		barber_up(&coffee_empty, not_coffee_full);
		barber_up(&coffee_empty, not_coffee_full);
		barber_up(&sugar_empty, not_sugar_full);
	}
}
