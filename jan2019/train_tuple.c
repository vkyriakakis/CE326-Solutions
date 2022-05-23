init() {
	out(<"LOCK">);
	out(<"CNT", 0>);
}

train() {
	while (1) {
		in(<"TRAIN">);
		make_tour();
		out(<"BARRIER">);
	}
}

passenger() {
	// Entry code
	in(<"LOCK">);

	in(<"CNT", &cnt>);
	cnt++;
	if (cnt == N)
		out(<"TRAIN">);
	else
		out(<"LOCK">);

	out(<"CNT", cnt>);

	// Exit code
	in(<"BARRIER">);

	in(<"CNT", &cnt>);
	cnt--;
	if (cnt == 0)
		out(<"LOCK">);
	else
		out(<"BARRIER">);

	out(<"CNT", cnt>);
}


