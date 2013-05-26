require './align_hash_with_murmur'
require 'ap'

hash = AlignHashWithMurmur.new
ap hash['wowowowo'] = "вау вау"

ap "hash['wowowowo']: #{hash['wowowowo']}"
