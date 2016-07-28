REM a.exe
REM a.exe --help
REM a.exe sdfd sdfsfd
REM a.exe sdfd sdfsfd l
a.exe --collection test1 --find "{}"
a.exe --collection "test1" --find "{}" --projection "{name:1, rate:1}"
a.exe --collection "test1" --insert "{name: 'Gabriel', rate: '12', group: 'A1'}"
