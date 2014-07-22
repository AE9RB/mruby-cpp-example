MRuby::Gem::Specification.new('mruby-cpp-example') do |spec|
  spec.license = 'MIT'
  spec.author  = 'David Turnbull'
  spec.summary = 'mruby C++ example'
  
  # Enable C++11 for compilers where it's not default
  if spec.build.toolchains.include? 'gcc'
    spec.cxx.flags << "-std=c++11"
  end

end
