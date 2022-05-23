// Bridge
int rw = 0, bw = 0;
int rin = 0, bin = 0;
int ra = K, ba = K; // Epitrepta prosperasmata K

while (1) {
	select {
		chanR[]?("WAIT", void): rw++;
		chanB[]?("WAIT", void): bw++;
		(ra > 0 && bin == 0 && rin < N) && chanR[]?("ENTER", void): {
			rin++;
			rw--;
			if (bw > 0)
				ra--; 
		}
		(ba > 0 && rin == 0 && bin < N) && chanB[]?("ENTER", void): {
			bin++;
			bw--;
			if (rw > 0)
				ba--;
		}
		chanR[]?("EXIT", void): {
			rin--;

			// Panta reset tis epitreptes prosperaseis
			// akomh kai an kaneis den perimenei (mporei na 
			// erthoun meta apo wra)
			if (rin == 0) {
				ba = K;
			}
		}
		chanB[]?("EXIT", void): {
			bin--;
			if (bin == 0) {
				ra = K;
			}
		}
	}
}

// Red(i), Blue(j) is symmetric
while(1) {
	chanR[i]!"WAIT";
	chanR[i]!"ENTER";
	chanR[i]!"EXIT";
}
