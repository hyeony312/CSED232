#include "artist.h"
#include "drawer.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "argc is not 4, but " << argc << endl;
		throw;
	}
	// CREATE PARSER
	parser p;
	// LOAD IMAGE AND CONFIG
	vector<int> tokens = p.load_image(argv[1]);
	vector<string> configs = p.load_config(argv[2]);

string style_target = configs[0];
string drawer_target = configs[1];
char* path_output = argv[3];
int width = tokens[0];
int height = tokens[1];
vector<int> vals = { tokens.begin() + 2, tokens.end() };

// CREATE ARTIST
artist* style;
if (style_target == "classic") {
	style = new classic(width, height, vals);
}
else if (style_target == "iclassic") {
	style = new iclassic(width, height, vals);
}
else if (style_target == "sobelx") {
	style = new sobelx(width, height, vals);
}
else if (style_target == "sobely") {
	style = new sobely(width, height, vals);
}
else if (style_target == "gradient") {
	style = new gradient(width, height, vals);
}
else {
	throw;
}

// CREATE DRAWER
drawer* d;
if (drawer_target == "drawer") {
	d = new drawer(style);
}
else if (drawer_target == "upsample") {
	d = new upsample(style);
}
else if (drawer_target == "downsample") {
	d = new downsample(style);
}
else if (drawer_target == "scale") {
	int scale_x = stoi(configs[2]);
	int scale_y = stoi(configs[3]);
	d = new scale(style, scale_x, scale_y);
}
else {
	throw;
}
// PERFORM DRAWING
string output = d->draw();
cout << output;
// WRITE OUTPUT
p.write_result(path_output, output);
return 0;
}
