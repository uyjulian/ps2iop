
import sys
import os

import re

line_addr_re = re.compile(r"^// (.*?)\.o$")

header_prepend = [
	"/*",
	"# _____     ___ ____     ___ ____",
	"#  ____|   |    ____|   |        | |____|",
	"# |     ___|   |____ ___|    ____| |    \\    PS2DEV Open Source Project.",
	"#-----------------------------------------------------------------------",
	"# Copyright ps2dev - http://www.ps2dev.org",
	"# Licenced under Academic Free License version 2.0",
	"# Review ps2sdk README & LICENSE files for further details.",
	"*/",
	"",
]

header_prefix_prepend = {
	"libsnd2" : "#include \"libsnd2_internal.h\"",
	"libspu2" : "#include \"libspu2_internal.h\"",
	"rspu2drv" : "#include \"rs_i.h\"",
}

def split_marked_file(f, dt):
	current_dat = []
	current_id = None
	for line in f.readlines():
		line = line.rstrip().decode(encoding="ASCII", errors="replace")
		line_addr_result = line_addr_re.match(line)
		if line_addr_result:
			current_id = line_addr_result.group(1)
			if current_id in dt:
				current_dat = dt[current_id]
			else:
				dt[current_id] = []
				current_dat = dt[current_id]
		else:
			current_dat.append(line)

def write_split_files(dt, basedir=None):
	for fn in sorted(dt.keys()):
		contents = []
		contents.append("\n".join(header_prepend))
		for header_prefix in header_prefix_prepend:
			if fn.startswith(header_prefix + "/"):
				contents.append(header_prefix_prepend[header_prefix])
				break
		contents.append("\n".join(dt[fn]))
		if basedir != None:
			fn_full = basedir + "/" + fn + ".c"
			os.makedirs(os.path.dirname(fn_full), exist_ok=True)
			with open(fn_full, "w") as wf:
				wf.write("\n".join(contents))
	# fn_split = fn.split("/")
	# fn_split = [x for x in fn_split if (x != "") and (x != "..") and (x != ".")]
	# fn_clean = "/".join(fn_split)
	# if basedir != None:
	# 	os.makedirs(os.path.dirname(basedir + "/" + fn_clean), exist_ok=True)
	# 	with open(basedir + "/" + fn_clean, "w") as wf2:
	# 		wf2.write("\n".join(allfile[fn]))
	# 		wf2.write("\n")

if __name__ == "__main__":
	if len(sys.argv) > 1:
		dt = {}
		with open(sys.argv[1], "rb") as f:
			split_marked_file(f, dt)
		if len(sys.argv) > 2:
			write_split_files(dt, sys.argv[2])
