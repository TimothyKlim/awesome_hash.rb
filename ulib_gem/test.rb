require './align_hash_with_murmur'
require 'ap'

hash = AlignHashWithMurmur.new
ap hash['wowowowo'] = "вау вау"
ap hash['wowowowo1'] = "wow"

ap "hash['wowowowo']: #{hash['wowowowo']}"
ap "hash['none']: #{hash['none']}"
ap "hash.size: #{hash.size}"
