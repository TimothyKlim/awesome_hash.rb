require './align_hash_with_murmur'
require 'benchmark'
require 'hitimes'
require 'sane'
require 'ap'

def measure
  Hitimes::Interval.measure { yield }
end

def meas string
  time_took = measure { yield }
  puts "% -23s %.03f" % [string, time_took]
end

n = 15_000_000

[AlignHashWithMurmur, Hash].each do |klass|
  3.times do
    GC.start
    meas("benchmark #{klass}") do
      hash = klass.new
      n.times do |i|
        hash[i.to_s] = i
      end
    end
  end
end
