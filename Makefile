all:
	node-waf configure build
pre:
	node-waf configure prebuild
tests:
	node ./test.js
install:
	cp ./build/default/node-gtk.node ~/.node_libraries/node-gtk.node
clean:
	rm -rf ./build
