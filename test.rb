#!/usr/bin/ruby
require 'fileutils'
require 'net/http'

class Uriresponser
 def initialize( uri )
  raise ArgumetError if uri == 0
  @uri = uri
  puts uri
 end
 def uri
  p @uri
 end 
  
end

Uriresponser.new "test\n" 

