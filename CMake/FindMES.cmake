set(FIND_MES_PATHS /mnt/c/Users/Kamil/CLionProjects/microservice/MESlib)

find_path(MES_INCLUDE_DIR MES.h
            PATH_SUFFIXES include
            PATHS ${FIND_MES_PATHS})

find_library(MES_LIBRARY
            NAMES MES
            PATH_SUFFIXES lib
            PATHS ${FIND_MES_PATHS})