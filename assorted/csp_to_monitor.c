// Pmon

int wait_count = 0;
int cur_pid;

while (1) {
	chan[]?("ENTER", cur_pid);
	while (1) {
		select {
			chan[cur_pid]?"EXIT": break;
			chan[cur_pid]?"WAIT": {
				wait_count++;
				break;
			}
			chan[cur_pid]?"SIGNAL": {
				if (wait_count > 0) {
					wait_count--;
					chan[]?("WAKEUP", cur_pid);
				}
				else {
					chan[cur_pid]?"ENTER";
				}
			}
		}
	}
}

// P(i)

enter_monitor() {
	chan[i]!"ENTER";
}

exit_monitor() {
	chan[i]!"EXIT";
}

signal() {
	chan[i]!"SIGNAL";
	chan[i]!"ENTER";
}

wait() {
	chan[i]!"WAIT";
	chan[i]!"WAKEUP";
}