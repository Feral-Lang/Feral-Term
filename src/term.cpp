/*
	Copyright (c) 2020, Electrux
	All rights reserved.
	Using the GNU GPL 3.0 license for the project,
	main LICENSE file resides in project's root directory.
	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <sys/ioctl.h>

#include "feral/VM/VM.hpp"

var_base_t * term_width_native( vm_state_t & vm, const fn_data_t & fd )
{
	int width = 80;
#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl( 0, TIOCGSIZE, & ts );
	width = ts.ts_cols;
#elif defined TIOCGWINSZ
	struct winsize ws;
	ioctl( 0, TIOCGWINSZ, & ws );
	width = ws.ws_col;
#endif /* TIOCGSIZE */
	return make< var_int_t >( width );
}

var_base_t * term_height_native( vm_state_t & vm, const fn_data_t & fd )
{
	int height = 24;
#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl( 0, TIOCGSIZE, & ts );
	height = ts.ts_lines;
#elif defined TIOCGWINSZ
	struct winsize ws;
	ioctl( 0, TIOCGWINSZ, & ws );
	height = ws.ws_row;
#endif /* TIOCGSIZE */
	return make< var_int_t >( height );
}

INIT_MODULE( term )
{
	var_src_t * src = vm.current_source();
	src->add_native_fn( "term_width_native", term_width_native );
	src->add_native_fn( "term_height_native", term_height_native );
	return true;
}
