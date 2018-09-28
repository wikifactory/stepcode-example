SCINSTALL := "../sc-install/"
SCHEMABUILD := "../stepcode/build/"

.DEFAULT_GOAL := pretty

all: clean p21mini p21read ap203min pretty

p21mini: p21mini.cpp
	g++ -std=c++11 \
		-I${SCINSTALL}/include/stepcode \
		-I${SCINSTALL}/include/stepcode/clstepcore \
		-I${SCINSTALL}/include/stepcode/clutils \
		-I${SCINSTALL}/include/stepcode/cldai \
		-I${SCINSTALL}/include/stepcode/cleditor \
		-I${SCINSTALL}/include/stepcode/base \
		p21mini.cpp -o p21mini \
		-L${SCINSTALL}/lib -lbase -lstepdai -lstepcore -lstepeditor -lsteputils \
		-L${SCHEMABUILD}/lib -lsdai_ap242 -lsdai_ap203e2 -lsdai_ap203

p21read: p21read.cpp
	g++ -std=c++11 \
		-I${SCINSTALL}/include/stepcode \
		-I${SCINSTALL}/include/stepcode/clstepcore \
		-I${SCINSTALL}/include/stepcode/clutils \
		-I${SCINSTALL}/include/stepcode/cldai \
		-I${SCINSTALL}/include/stepcode/cleditor \
		-I${SCINSTALL}/include/stepcode/base \
		p21read.cpp -o p21read \
		-L${SCINSTALL}/lib -lbase -lstepdai -lstepcore -lstepeditor -lsteputils \
		-L${SCHEMABUILD}/lib -lsdai_ap242 -lsdai_ap203e2 -lsdai_ap203

ap203min: ap203min.cpp
	g++ -std=c++11 \
		-I${SCINSTALL}/include/stepcode \
		-I${SCINSTALL}/include/stepcode/clstepcore \
		-I${SCINSTALL}/include/stepcode/clutils \
		-I${SCINSTALL}/include/stepcode/cldai \
		-I${SCINSTALL}/include/stepcode/cleditor \
		-I${SCINSTALL}/include/stepcode/base \
		-I${SCINSTALL}/include/schemas/sdai_ap203 \
		ap203min.cpp -o ap203min \
		-L${SCINSTALL}/lib -lbase -lstepdai -lstepcore -lstepeditor -lsteputils \
		-L${SCHEMABUILD}/lib -lsdai_ap203

pretty: pretty.cpp
	g++ -std=c++11 \
		-I${SCINSTALL}/include/stepcode \
		-I${SCINSTALL}/include/stepcode/clstepcore \
		-I${SCINSTALL}/include/stepcode/clutils \
		-I${SCINSTALL}/include/stepcode/cldai \
		-I${SCINSTALL}/include/stepcode/cleditor \
		-I${SCINSTALL}/include/stepcode/base \
		-I${SCINSTALL}/include/schemas/sdai_ap242 \
		pretty.cpp -o pretty \
		-L${SCINSTALL}/lib -lbase -lstepdai -lstepcore -lstepeditor -lsteputils \
		-L${SCHEMABUILD}/lib -lsdai_ap242

clean:
	-rm p21mini
	-rm p21read
	-rm ap203min
	-rm pretty
