file(GLOB_RECURSE libsrc *.h *.cpp *.hpp *.c *.cc)

target_sources(eden PUBLIC ${libsrc})
