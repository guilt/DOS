@ECHO OFF
REM LANtastic  Version 8.0  installed 25/01/30 20:51:01
REM (for DOS)

C:
CD C:\LANTASTI
SET LAN_CFG=C:\LANTASTI


@ECHO ===== Begin LANtastic configuration =====

PATH %PATH%;C:\LANTASTI

LOADHIGH NEX000
LOADHIGH AILANBIO
REDIR

REM If CONNECT.BAT exists, run it to set up connections.
IF EXIST CONNECT.BAT GOTO :CONNECT

REM Otherwise set up connections specified during install.
GOTO :CONNECT_DONE

:CONNECT
@ECHO Setting up LANtastic connections from CONNECT.BAT
REM Modify CONNECT.BAT by running: NET CONNECTIONS/FORCE
REM   (or run the batch file SETNET.BAT)
CALL CONNECT.BAT

:CONNECT_DONE

@ECHO ===== End LANtastic configuration =====

:STARTNET_DONE
CD \
