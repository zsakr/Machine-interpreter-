! This my Fortran program
program hello
   logical :: prime
   integer :: a
   integer :: j
   integer :: n

   n = 100

   do i =2, n
      prime = .true.
      do j = 2, i /2
        if(modulo(i/j) ==0 ) then
          prime = .false.
        end if
      end do
    if(prime) then
      Print *,i
    end if
    end do

    a = ifprime(19)
end program hello

function ifprime(num)

implicit none

  real :: ifprime
  integer :: num
  integer :: i

  if(num == 1) then
    Print *, "FALSE"
    ifprime = 0
    stop
  end if

  if(nun == 2) then
    Print *, "TRUE"
    ifprime = 1
    stop
    end if

    do i = 2, num-1
    if(modulo(num,i) == 0) then
      Print *, "FALSE"
    else
      Print *, "TRUE"
    stop
    end if

end function ifprime
