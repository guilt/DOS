
{ simplest pascal program }

program dccsmpl;
uses windows;
var
 memstat: MEMORYSTATUS;
begin
  memstat.dwLength := sizeof(MEMORYSTATUS);
  GlobalMemoryStatus(memstat);
  writeln('virtual memory (avail/total) = ',memstat.dwAvailVirtual, '/', memstat.dwTotalVirtual);
  writeln('pagefile (avail/total) = ',memstat.dwAvailPageFile, '/', memstat.dwTotalPageFile);
end.
