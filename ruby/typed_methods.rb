require 'pp'

require 'filigree/types'

class Class
	def *(times)
		Array.new(times, self)
	end
end

def deft(name, ret_type, *param_types, &block)
	param_types.flatten!
	
	if param_types.length != block.parameters.length
		raise "Incomplete type given for function '#{name}'"
	end
	
	define_method(name) do |*args|
		block.parameters.map(&:last).zip(param_types, args).each do |n, t, v|
			break if v.nil?
			
			check_type(v, t, n, true)
		end
		
		ret = block.call(*args)
		
		if ret.is_a?(ret_type)
			ret
		else
			raise "Incorrect return type for function #{name}"
		end
	end
end

deft(:add, Integer, Integer) do |a, &block|
	a + b
end

pp add(41)
