

i = ARGV[0].to_i
puts i

o = ""

while i > 0
	if i.between?(900,999) 
		o += 'CM'
		i -= 900
	end
	if i >= 1000
		o += 'M'
		i -= 1000
	end
	if i.between?(400,499)
		o += 'CD'
		i -= 400
	end
	if i.between?(500,899)
		o += 'D'
		i -= 500
	end
	if i.between?(90,99)
		o += 'XC'
		i -= 90
	end
	if i.between?(100,399)
		o += 'C'
		i -= 100
	end
	if i.between?(40,49)
		o += 'XL'
		i -= 40
	end
	if i.between?(50,89)
		o += 'L'
		i -= 50
	end
	if i == 9
		o += 'IX'
		i -= 9
	end
	if i.between?(10,39)
		o += 'X'
		i -= 10
	end
	if i == 4
		o += 'IV'
		i -= 4
	end
	if i.between?(5,8)
		o += 'V'
		i -= 5
	end
	if i.between?(1,3)
		o += 'I'
		i -= 1
	end
end


puts o
