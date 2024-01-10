debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

install: release
	cd build/Release && sudo cmake --install .

clean:
	rm -rf build

cleanInstall:
	sudo rm -rf /usr/local/include/core_utils
	sudo rm -rf /usr/local/lib/libcore_utils.so

r: release

d: debug
