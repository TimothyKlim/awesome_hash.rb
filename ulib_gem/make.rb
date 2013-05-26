#!/usr/bin/env ruby

system %Q{
  ruby ./extconf.rb
  make
  ruby ./test.rb
}.strip
