init() {
	out(<"LOCK">);
	out(<"CNT", 0, "GROUP", false>);
}

cafe_enter() {
	in(<"LOCK">);
	in(<"CNT", &cnt, "GROUP", &is_group>);

	cnt++;
	if (cnt == N)
		out(<"CNT", N, "GROUP", true>);
	else {
		out(<"LOCK">);
		out(<"CNT", cnt, "GROUP", is_group>);
	}
}

cafe_exit() {
	in(<"CNT", &cnt, "GROUP", &is_group>);

	cnt--;
	if (cnt == 0 && is_group) {
		out(<"LOCK">);
		out(<"CNT", 0, "GROUP", false>);
	}
	else
		out(<"CNT", cnt, "GROUP", is_group>);
}