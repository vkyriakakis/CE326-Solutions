// WC
int man_in = 0, wom_in = 0;
int wom_w = 0;

while(1) {
	select {
		// For women
		chanW[]?("WAIT", void): {
			wom_w++;
		}

		(man_in == 0 && wom_in < N) && chanW[]?("ENTER", void): {
			wom_w--;
			wom_in++;
		}

		chanW[]?("EXIT", void): {
			wom_in--;
		}

		// For men
		(man_in < N && (wom_in + wom_w == 0)) && chanM[]?("ENTER", void): {
			man_in++;
		}

		chanM[]?("EXIT", void): {
			man_in--;
		}
	}
}

// Man(i)
while (1) {
	chanM[i]!"ENTER";
	chanM[i]!"EXIT";
}

// Woman(j)
while(1) {
	chanW[j]!"WAIT";
	chanW[j]!"ENTER";
	chanW[j]!"EXIT";
}

