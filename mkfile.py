import os

cur_dir = "Classes"
filename_pre_str = "../../"
dirname_pre_str = "$(LOCAL_PATH)/../../"


filenamelist = ""
dirnamelist = ""

def listdir(dirame):
	global filenamelist
	global dirnamelist

	dirfilenamelist = os.listdir(dirame)

	for dirfilename in dirfilenamelist:
		filename = dirame + "/" + dirfilename

		if os.path.isdir(filename):
			dirnamelist += dirname_pre_str + filename + " \\" + "\n"
			listdir(filename)
		elif filename[-4:] == ".cpp" or filename[-2:] == ".c":
			filenamelist += filename_pre_str + filename + " \\" + "\n"



listdir(cur_dir)
mkfile = open("mkfile.txt", "w")
mkfile.write(filenamelist + "\n\n\n" + dirnamelist)
mkfile.close()