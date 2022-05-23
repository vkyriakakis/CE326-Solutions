monitor kafeneio {
	condition group_left;
	int cnt;
	bool is_group;

	void init(void) {
		cnt = 0;
		is_group = false;
	}

	void enter_cafe(void) {
		if (is_group)
			wait(group_left);

		cnt++;
		if (cnt == N)
			is_group = true;
	}

	void exit_cafe(void) {
		cnt--;
		if (cnt == 0 && is_group) {
			is_group = false;
			for (int i = 0 ; i < N ; i++)
				signal(group_left);
		}
	}
}

