SCINSTALL := "../sc-install"
SCHEMABUILD := "../stepcode/ap242"

all: p21mini

p21mini:
	g++ -I${SCINSTALL}/include/stepcode \
		-I${SCINSTALL}/include/stepcode/clstepcore \
		-I${SCINSTALL}/include/stepcode/clutils \
		-I${SCINSTALL}/include/stepcode/cldai \
		-I${SCINSTALL}/include/stepcode/cleditor \
		-I${SCINSTALL}/include/stepcode/base \
		p21mini.cpp -o p21mini \
		-L${SCINSTALL}/lib -lbase -lstepdai -lstepcore -lstepeditor -lsteputils \
		-L${SCHEMABUILD}/lib -lsdai_ap242

clean:
	rm p21mini
