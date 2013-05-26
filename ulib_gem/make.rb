#!/usr/bin/env ruby

system "ruby ./extconf.rb && make clean && make && ruby ./test.rb"
