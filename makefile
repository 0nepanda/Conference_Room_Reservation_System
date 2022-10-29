target=workFlow
libs=01机房预约系统.cpp 03student.cpp 04teacher.cpp 05Manager.cpp 08orderFile.cpp
$(target):$(libs)
	g++ -std=c++11 $^ -o $@