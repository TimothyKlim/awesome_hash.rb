require 'mkmf'

SRC_PATH = File.expand_path('../../../src', __FILE__)

create_makefile('align_hash_with_murmur')
find_header('hash_func.h', 'hash_align.h', 'math_rand_prot.h', 'MurmurHash3.cpp', SRC_PATH)
