#include"Color.h"
void textcolor(int attr,int fg,int bg){
	std::cout<<"\x1b["<<attr<<';'<<fg+30<<';'<<bg+40<<'m';
}
