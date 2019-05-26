cmake_minimum_required( VERSION 2.8 )
aux_source_directory(. DIR_DISPLAY_SRCS)
add_library(display ${DIR_DISPLAY_SRCS})