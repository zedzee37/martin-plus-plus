.PHONY: setup run test

run src/*.c:
	cd build && ninja && ./martin-plus-plus
	cd ../

test test/*.c:
	cd build && meson test --verbose
	cd ../
