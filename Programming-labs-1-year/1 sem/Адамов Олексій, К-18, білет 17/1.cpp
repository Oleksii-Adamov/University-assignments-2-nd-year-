void first_100_of_M(int a[]) {
	a[0] = 1;
	// "покажчики"(індекси) елементів, з яких ми будемо робити y = 2*x+1 та z = 3*x+1 
	int p_y = 0, p_z = 0;
	for (int i = 1; i < 100; i++) {
		int y = 2*a[p_y] + 1, z = 3*a[p_z] + 1;
		if (y == z) {
			a[i] = y;
			p_y++;
			p_z++;
		}
		else if (y < z) {
			a[i] = y;
			p_y++;
		}
		else {
			a[i] = z;
			p_z++;
		}
	}
}
