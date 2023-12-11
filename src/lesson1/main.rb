# frozen_string_literal: true

file = File.open "/home/thomas/projects/github.com/advent-of-code-2023/src/lesson1/data-lesson1.txt"

lines = file.readlines

def lesson1(lines)
  first_digit = ''
  last_digit = ''
  digits = Array.new
  lines.each do |line|
    line.each_char do |char|
      if char.match?(/^\d+$/)
        if first_digit.empty?
          first_digit = char
        end
        last_digit = char
      end
    end

    digits.push((first_digit + last_digit).to_i)
    first_digit = ''
    last_digit = ''
  end

  puts 'lesson 1: ' + digits.sum.to_s
end

def lesson2(lines)
  digits = Array.new
  re_first = /(one|two|three|four|five|six|seven|eight|nine|[1-9])/m
  re_last = /(eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|[1-9])/m
  lines.each do |line|
    first_groups = line.scan(re_first)
    first_digit = first_groups[0][0]
    line.reverse!
    last_groups = line.scan(re_last)
    last_digit = last_groups[0][0]
    num = (to_number(first_digit) + to_number(last_digit)).to_i
    digits.push(num)
  end

  puts 'lesson 2: ' + digits.sum.to_s
end

def to_number(number)
  case number
  when 'one', 'eno'
    return '1'
  when 'two', 'owt'
    return '2'
  when 'three', 'eerht'
    return '3'
  when 'four', 'ruof'
    return '4'
  when 'five', 'evif'
    return '5'
  when 'six', 'xis'
    return '6'
  when 'seven', 'neves'
    return '7'
  when 'eight', 'thgie'
    return '8'
  when 'nine', 'enin'
    return '9'
  else
    return number
  end
end

lesson1(lines)
lesson2(lines)