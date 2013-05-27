require 'helper'

class TestHighlyEfficientTypes < Test::Unit::TestCase
  should "works like HashMap" do
    hash = AlignHashWithMurmur.new
    assert_equal hash.size, 0
    hash['key'] = 'value'
    assert_equal hash['key'], 'value'
    assert_equal hash.size, 1
  end
end
