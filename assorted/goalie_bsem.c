int goalie_cnt = 0;

// For this to work, the semaphores must be FIFO.
// If gwait1, gwait2 are used, it can work with
// any kind of semaphore.
bsem gmtx = init(1);
bsem gwait = init(0), mwait = init(0);

goalie {
	down(gmtx);

	goalie_cnt++;
	if (goalie_cnt == 2) {
		up(mwait);
		down(gwait);
		goalie_cnt = 0;

		form_group();

		up(gmtx);
	}
	else {
		up(gmtx);
		down(gwait);
		// Form_group() must be done b4 the up
		// else the 2nd goalie might release the mtx before
		form_group();
		up(gwait);
	}
}

midfield {
	down(mwait);
	// Form_group() must be done b4 the up
    // else the 2nd goalie might release the mtx before,
    // so rogue goalies will invade b4 the group is fully formed
	form_group();
	up(gwait);
}

