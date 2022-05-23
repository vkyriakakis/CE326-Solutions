// Train
int ps = 0;

while(1) { 
	while (ps < N) {
		chan[]?("ENTER", void);
		ps++;
	}

	train_ride();

	while (ps > 0) {
		chan[]?("EXIT", void);
		ps--;
	}
}

// Passenger
while(1) {
	chan[i]!"ENTER";
	// enjoy
	chan[i]!"EXIT";
}

