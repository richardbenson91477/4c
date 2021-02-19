program main
  implicit none
  integer, parameter :: n = 200
  integer, parameter :: fd = 10
  real t(n), x(n), y(n)
  integer i 

  t = [(real(i) * .03141592653589793238, i = 1, n, 1)]

  x = cos(t)
  y = sin(t)

  write (*,*) 'opening circle.dat'
  open(unit=fd, file='circle.dat', action="write")
  do i = 1, n
    write (fd,*) x(i), y(i)
  enddo
  close(fd)

end program

