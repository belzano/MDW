# The name of our project is "MME". CMakeLists files in this project can 
# refer to the root source directory of the project as ${MME_SOURCE_DIR} and 
# to the root binary directory of the project as ${MME_BINARY_DIR}. 

cmake_minimum_required(VERSION 2.8)
project (apiinternal)

# ----------------------------------------------------------------------------
# Process subdirectories
# ----------------------------------------------------------------------------

add_subdirectory (bom)
add_subdirectory (shapes)
add_subdirectory (process)

