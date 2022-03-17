#include "Graph.h"
#include "Simple_window.h"


int main()
{

	using namespace Graph_lib;
	Point tl(100, 200);
	Simple_window win(tl, 800, 700, "Canvas");
    
	Vector_ref<Box> vr1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			vr1.push_back(new Box(Point(i * 130, j * 150), (i+1)*30, (j+1)*40, 12));
			vr1[vr1.size() - 1].set_fill_color(i * 40 + j);
			win.attach(vr1[vr1.size() - 1]);
		}
	}
	win.wait_for_button();
	
	for (int i = 0; i < 16; i++) {
		win.detach(vr1[vr1.size() -i-1]);
	}
	
	
	Vector_ref<Regular_polygon> vr2;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			vr2.push_back(new Regular_polygon(Point(50+j * 200, 50+i * 150), (4*i+j+3), 50));
			vr2[vr2.size() - 1].set_color(i * 40 + j);
			win.attach(vr2[vr2.size() - 1]);
		}
	}
	win.wait_for_button();
	
	for (int i = 0; i < 16; i++) {
		win.detach(vr2[vr2.size() - i - 1]);
	}
	

	Vector_ref<Star> vr3;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			vr3.push_back(new Star(Point(50+j * 200, 50+i * 150), 4*i+j+3, 20, 50));
			vr3[vr3.size() - 1].set_color(i * 40 + j);
			win.attach(vr3[vr3.size() - 1]);
		}
	}
	win.wait_for_button();
	
	for (int i = 0; i < 16; i++) {
		win.detach(vr3[vr3.size()  - i - 1]);
	}
	
	Vector_ref<Rose> vr4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			vr4.push_back(new Rose(Point(50 + j * 200, 50 + i * 150), 4 * i + j + 4, j+1, 30));
			vr4[vr4.size() - 1].set_color(i * 40 + j);
			win.attach(vr4[vr4.size() - 1]);
		}
	}
	win.wait_for_button();

	for (int i = 0; i < 16; i++) {
		win.detach(vr4[vr4.size() - i - 1]);
	}

	Vector_ref<Bug> vr5;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			vr5.push_back(new Bug(Point(30 + j * 200, 30 + i * 150), (4 * i + j+1)*6, (4 * i + j)*3, (4 * i + j+1)*5));
			vr5[vr5.size() - 1].set_fill_color(i * 40 + j);
			win.attach(vr5[vr5.size() - 1]);
		}
	}
	win.wait_for_button();

	for (int i = 0; i < 16; i++) {
		win.detach(vr4[vr4.size() - i - 1]);
	}
}