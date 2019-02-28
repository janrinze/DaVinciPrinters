#include "parser.h"

#include <string>
#include <fstream>
#include <streambuf>

using namespace gpr;
using namespace std;

#define ENDLINE "\r\n"

// This example program shows how to create your own blocks and print them out,
// and how to use the parser. To create a custom block and print it out just type:
//     ./parse-gcode
// at the command line
// To parse a G-code file type:
//     ./parse-gcode <path-to-gcode-file>
int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "We are going to create a new block programatically ";
    cout << "and print it out:" << ENDLINE;

    chunk G1 = make_word_int('G', 1);
    chunk X1pt7 = make_word_double('X', 1.7);
    chunk YN1 = make_word_double('Y', -1.0);
    chunk comment = make_comment('(', ')', "This is a silly comment");

    block artificial_block(false,(std::vector<chunk>) {G1, X1pt7, YN1, comment});
    // The call to set_text is only relevant for debugging. It sets the block
    // member variable block_text to a string representation of the block so
    // that you can see a compact representation of the block during debugging
    artificial_block.set_debug_text();

    cout << artificial_block << ENDLINE;
  } else {
    assert(argc == 2);
  
    string file = argv[1];

    std::ifstream t(file);
    std::string file_contents((std::istreambuf_iterator<char>(t)),
			      std::istreambuf_iterator<char>());

    gcode_program p = parse_gcode(file_contents);

    cout << "; filename = " << file << ENDLINE;
    cout << "; print_time = 486" << ENDLINE;
    cout << "; machine = FXX" << ENDLINE;
    cout << "; material = default" << ENDLINE;
    cout << "; layer_height = 0.20" << ENDLINE;
    cout << "; fill_density = 0.25" << ENDLINE;
    cout << "; raft_layers = 0" << ENDLINE;
    cout << "; support_material = 0" << ENDLINE;
    cout << "; support_material_extruder = 1" << ENDLINE;
    cout << "; fill_density = 0.10" << ENDLINE;
    cout << "; support_density = 0.20" << ENDLINE;
    cout << "; shells = 2" << ENDLINE;
    cout << "; speed = 45" << ENDLINE;
    cout << "; total_layers = 22" << ENDLINE;
    cout << "; version = 14070911" << ENDLINE;
    cout << "; total_filament = 0.40" << ENDLINE;
    cout << "; extruder_filament = 0.18:0.21" << ENDLINE;
    cout << "; dimension = 72.35:42.57:6.65" << ENDLINE;
    cout << "; extruder = 3" << ENDLINE;

    // fix speed and G0
    double max_speed=3600.0;
    for (auto j: p) {
	bool l_end=true;
	for (auto k: j) {
	    switch(k.tp()) {
	    case CHUNK_TYPE_WORD_ADDRESS:
		if (k.get_word()=='F') 
		{
			
			if (k.get_address().tp()==ADDRESS_TYPE_DOUBLE)
			{
			    if (k.get_address().double_value() < max_speed)
			    {
				cout << k << " ";
			    } else {
				cout << "F" << max_speed << " ";
			    }
			} else {
			    if (k.get_address().int_value() < (int) max_speed )
			    {
				cout << k << ENDLINE;
			    } else {
				cout << "F" << max_speed << " ";
			    }
			}
		    
		} else {
		   if (k.get_word()=='G' && k.get_address().int_value()==0) // filter G0
			   cout << "G1 ";
		   else
		       cout << k << " ";
		}
		break;
	    case CHUNK_TYPE_COMMENT: l_end=false; break;
	    default: 
		cout << k << " ";
	    }
	}
	// add dos line ending.
	if (l_end) cout << ENDLINE;
    }
    // cout << "Max speed is " << max_speed << ENDLINE;
    
  }
}

