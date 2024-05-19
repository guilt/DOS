      * MicroFocus Object Cobol sample
      $set mf case ans85 defaultbyte"00" noosvs nobound
      $set align"4"
      *
       identification division.
      *
       program-id. cobsmpl.
      *
       environment division.
       special-names.
         call-convention 74 is WINAPI.
      *
       data division.
       working-storage section.
         01 hConout   pic x(04) comp-5.
         01 text1     pic x(14) value "hello, world"&x'0d0a'.
         01 dwWritten pic x(04) comp-5.
         01 rc        pic x(04) comp-5.
      *
       procedure division.
      *   call WINAPI "DebugBreak"
          call WINAPI "GetStdHandle" using
				by value -11
                returning hConout
          call WINAPI "WriteConsoleA" using
				by value hConout
                by reference text1
                by value 14
                by reference dwWritten
                by value 0
                returning rc
          goback.
