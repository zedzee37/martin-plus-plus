run:
	cd build && ninja && ./martin-plus-plus
	cd ../

test:
	cd build && meson test
	cd ../
