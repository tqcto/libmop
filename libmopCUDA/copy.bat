@echo off
f:
cd "F:/Visual Studio Librarys/Originals/libmop/libmop/libmopCUDA/include/"
@set DIR1="F:/Visual Studio Librarys/Originals/libmop/release/dynamic/include/"
for %%f in (*) do (
	copy %%f %DIR1%%f%
	echo filename = %%f
)