@echo off
echo '-- Clear Old Build --'
SET Build=%~f1

del /s /Q "%Build%"
