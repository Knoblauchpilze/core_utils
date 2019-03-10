debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf build

r: release

d: debug

install: r
	sudo cp build/Release/lib/libcore_utils.so /usr/local/lib
	sudo mkdir -p /usr/local/include/core_utils
	sudo cp src/*.hh /usr/local/include/core_utils
	sudo cp src/*.hxx /usr/local/include/core_utils

