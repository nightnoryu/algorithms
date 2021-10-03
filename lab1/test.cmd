@echo off

set SUBJECT="%~1"

if %SUBJECT%=="" (
  echo usage: test.cmd ^<exe file name^>
  exit /b 1
)


rem Simple text is processed correctly
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" 70 2 > nul || goto error
fc "%TEMP%\output.txt" tests\lorem_output.txt > nul || goto error
echo Test 1 passed
echo.

rem Simple text with variable line width is processed correctly
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" 40 2 > nul || goto error
fc "%TEMP%\output.txt" tests\lorem40_output.txt > nul || goto error
echo Test 2 passed
echo.

rem Simple text with variable first line indent is processed correctly
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" 70 4 > nul || goto error
fc "%TEMP%\output.txt" tests\lorem4ind_output.txt > nul || goto error
echo Test 3 passed
echo.

rem Cyrillic text is processed correctly
%SUBJECT% tests\cyrillic.txt "%TEMP%\output.txt" 70 2 > nul || goto error
fc "%TEMP%\output.txt" tests\cyrillic_output.txt > nul || goto error
echo Test 4 passed
echo.

rem Heavy text is processed correctly
powershell (Measure-Command { ".\\%SUBJECT%" tests\heavy.txt "%TEMP%\output.txt" 70 2 }).ToString() || goto error
fc "%TEMP%\output.txt" tests\heavy_output.txt > nul || goto error
echo Test 5 passed
echo.

rem Strange line width is processed correctly
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" 5 2 > nul || goto error
fc "%TEMP%\output.txt" tests\lorem5_output.txt > nul || goto error
echo Test 6 passed
echo.

rem Non-existing input file yields an error
%SUBJECT% non-existing.txt "%TEMP%\output.txt" 70 2 1> nul 2> nul && goto error
echo Test 7 passed
echo.

rem Output file on non-existing drive yields an error
%SUBJECT% tests\lorem.txt "O:\output.txt" 70 2 1> nul 2> nul && goto error
echo Test 8 passed
echo.

rem Invalid width value yields an error
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" sneed 2 1> nul 2> nul && goto error
echo Test 9 passed
echo.

rem Invalid first line indent value yields an error
%SUBJECT% tests\lorem.txt "%TEMP%\output.txt" 70 sneed 1> nul 2> nul && goto error
echo Test 10 passed
echo.


rem All tests have passed
exit /b 0

rem There was an error
:error
echo Test failed
exit /b 1
