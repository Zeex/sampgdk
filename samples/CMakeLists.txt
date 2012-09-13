cmake_minimum_required(VERSION 2.8)

add_subdirectory(helloworld)
set_property(TARGET helloworld PROPERTY FOLDER "sampgdk/samples")
	
add_subdirectory(lvdm)
set_property(TARGET lvdm PROPERTY FOLDER "sampgdk/samples")

add_subdirectory(unlimitedfs)
set_property(TARGET unlimitedfs PROPERTY FOLDER "sampgdk/samples")
