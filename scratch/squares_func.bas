function my_square(x as integer) as integer
  return x * x
end function

for x as integer = 1 to 10
  print my_square(x)
next x

