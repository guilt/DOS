C
C QSORT.FOR  FORTRAN version of the quicksort algorithm
C
C This program is described in Chapters 2 and 3 of the Microsoft Source
C Profiler User's Guide.
C
C

      program qsort

      integer MAXNUMWORDS, MAXWORDSIZE
      parameter (MAXNUMWORDS = 1500, MAXWORDSIZE = 15)

      integer numwords
      character*15 wordarray(MAXNUMWORDS)
      integer wordindex(MAXNUMWORDS)
      common /globals/ numwords, wordarray, wordindex

      integer i
      character*128 inpfilename, outfilename

      write (*, *) 'Fortran Quicksort demo program'

      if (nargs() .ne. 3) then
          call usage
      end if

C open the input file

      call getarg(1, inpfilename, i)
      open (1, file = inpfilename, status='old', iostat=i)

      if (i .ne. 0) then
          write (*, "(' Cannot open file ''', a, '''')")
     +          inpfilename(1:len_trim(inpfilename))
          stop
      end if

C open the output file

      call getarg(2, outfilename, i)
      open (2, file = outfilename, iostat=i)

      if (i .ne. 0) then
          write (*, "(' Cannot open file ''', a, '''')")
     +          outfilename(1:len_trim(outfilename))
          stop
      end if

C init the wordarray and wordindex

      do i = 1, MAXNUMWORDS
          wordarray(i) = '               '
          wordindex(i) = i
      end do

C read the source file, split into words

      write (*, *) 'Loading...'

      call GetWords

      write (*, "(' Loaded ',  i4, ' words')") numwords

C sort the array and output the sorted list

      write (*, *) 'Sorting...'

      if (numwords .gt. 1) then     !don't bother sorting 1 word lists
          call quicksort
      end if

      write (2, "(' ', a)")
     +      (wordarray(wordindex(i)), i = 1, numwords)

      return
      end                           !program qsort


C
C subroutine GetWords
C
C read up to MAXNUMWORDS words from the source file, and store each one in
C    wordarray
C

      subroutine GetWords

      integer MAXNUMWORDS, MAXWORDSIZE
      parameter (MAXNUMWORDS = 1500, MAXWORDSIZE = 15)

      integer numwords
      character*15 wordarray(MAXNUMWORDS)
      integer wordindex(MAXNUMWORDS)
      common /globals/ numwords, wordarray, wordindex

      character*1 c
      character*256 line
      integer lineindex
      integer chrnum

      numwords = 0

      do while (.true.)            !read lines
          read (1, "(a)", end=10) line
          line(256:256) = ' '      !force recognition of last word on line
          chrnum = 1

          do lineindex = 1, 256    !scan line for words
              c = line(lineindex:lineindex)

              select case (c)

                  case (' ')
                      if (chrnum .ne. 1) then
                          chrnum = 1
                          numwords = numwords + 1

                          if (numwords .ge. MAXNUMWORDS) then
                              goto 10
                          end if    !if (numwords .ge. MAXNUMWORDS) then
                      end if        !if (chrnum .ne. 1) then

                  case default
                      if (chrnum .le. MAXWORDSIZE) then
                          wordarray(numwords+1)(chrnum:chrnum) = c
                          chrnum = chrnum + 1
                      end if        !if (chrnum .le. MAXWORDSIZE) then
              end select            !select case (c)
          end do                    !do lineindex = 1, 256
      end do                        !do while (.true.)

10    return
      end                           !subroutine GetWords


C
C*************************************************************************
C subroutine quicksort
C
C quicksort the wordarray
C
C note the simulation of recursion, using stackptr and indexed variables
C

      subroutine quicksort

      integer MAXNUMWORDS, MAXWORDSIZE
      parameter (MAXNUMWORDS = 1500, MAXWORDSIZE = 15)

      integer numwords, swaptemp
      character*15 wordarray(MAXNUMWORDS), pivot
      integer wordindex(MAXNUMWORDS)
      common /globals/ numwords, wordarray, wordindex

      integer stackptr, lower(16), upper(16)

      stackptr = 1
      lower(1) = 1
      upper(1) = numwords

      do while (stackptr .gt. 0)
          if (lower(stackptr) .ge. upper(stackptr)) then
              stackptr = stackptr - 1
              cycle
          end if                    !if (lower(stackptr) .ge. ...

C figure out where we are in the recursion tree

          i = lower(stackptr)
          j = upper(stackptr)
          pivot = wordarray(wordindex(j))

C separate this partition into 2 parts

          do while (i .lt. j)
              do while ((i .lt. j) .and.
     +                  lle(wordarray(wordindex(i)), pivot))
                 i = i + 1
              end do                !do while ((i .lt. j) .and. ...

              do while ((j .gt. i) .and.
     +                  lge(wordarray(wordindex(j)), pivot))
                 j = j - 1
              end do                !do while ((j .gt. i) .and. ...

C if we haven't reached the pivot element yet, there must be two elements
C out of order, so swap them

            if (i .lt. j) then
               swaptemp = wordindex(i)
               wordindex(i) = wordindex(j)
               wordindex(j) = swaptemp
            end if                  !if (i .lt. j) then
         end do                     !do while (i .lt. j)

C move the pivot element back where it belongs

         j = upper(stackptr)
         swaptemp = wordindex(i)
         wordindex(i) = wordindex(j)
         wordindex(j) = swaptemp

         if ((i - lower(stackptr)) .lt. (upper(stackptr) - i)) then
            lower(stackptr + 1) = lower(stackptr)
            upper(stackptr + 1) = i - 1
            lower(stackptr)     = i + 1
         else
            lower(stackptr + 1) = i + 1
            upper(stackptr + 1) = upper(stackptr)
            upper(stackptr)     = i - 1
         end if                     !if ((i - lower(stackptr)) .lt. ...

         stackptr = stackptr + 1
      end do                        !do while (stackptr .gt. 0)

      return
      end                           !subroutine quicksort


C
C*************************************************************************
C subroutine usage
C
C print out a help message
C

      subroutine usage

      write (*, *)
     +      "Performs QuickSort on a file and sends results to a file."
      write (*, *)
     +      "Usage: QSORT <input> <output>"
      write (*, *)
     +      "Where <input> is the name of the text file to sort and " //
     +      "<output> is the"
      write (*, *)
     +      "name of the file to store " //
     +      "the sorted output."

      stop
      end                           !subroutine usage
